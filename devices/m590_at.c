/*
 * m590_at.c
 *
 *  Created on: Aug 7, 2015
 *      Author: UFSM
 */

#include "AppConfig.h"
#include "m590_at.h"
#include "BRTOS.h"
#include "printf_lib.h"
#include "utils.h"
#include "terminal_commands.h"
#include "string.h"

#include "simon-api.h"

#ifdef _WIN32
#include <stdio.h>
#endif


uint8_t CheckPPP(void);
uint8_t CreatePPP(void);
uint8_t CreateTCPLink(char *linkStr);
uint8_t CreateSingleTCPLink(unsigned char iLinkNum,char *strServerIP,char *strPort);
uint8_t TCPIP_SendData(uint8_t * dados, uint16_t tam);
uint8_t is_m590_ok(void);
uint8_t is_m590_ok_retry(uint8_t retries);

static m590_state_t m590_state = M590_CLOSE;
static char ip[16];
static char *hostname = NULL;
static INT8U gReceiveBuffer[256];

#define DEBUG_PRINT 1

#if DEBUG_PRINT
#define PRINT(...) 		printSer(USE_USB,__VA_ARGS__);
#define PRINT_BUF(...)  printSer(USE_USB,__VA_ARGS__);
#else
#define PRINT(...)
#define PRINT_BUF(...)
#endif

#define UNUSED(x)   (void)x;

typedef enum
{
	AT = 0,
	CREG,
	XISP,
	XIIC1,
	XIIC,
	IPSTAT,
	CLK
}m590_enum_cmd;

#define CONST const
CONST char *m590_init_cmd[]= 
{
		"AT\r\n",
		"AT+CREG?\r\n",
		"AT+XISP=0\r\n",
		"AT+XIIC=1\r\n",
		"AT+XIIC?\r\n",
		"AT+IPSTATUS=0\r",
		"AT+CCLK?\r\n"
};

static void at_m590_print_reply(void)
{
	INT8U c;
	DelayTask(1000);
	while((c=m590_getchar()) != (CHAR8)-1){
		putcharSer(USE_USB,c);
	}
}

static INT8U m590_get_reply(INT8U *buf, INT16U max_len)
{
	INT8U c;
	INT8U len = 0;
	memset(buf,0x00,max_len); // clear buffer
	while((c=m590_getchar()) != (CHAR8)-1){
		*buf = c;
		buf++;
		len++;
		if(--max_len <= 1) 
		{
			break;
		}
	}
	return len;
}

INT8U is_m590_ok(void)
{
	INT8U ok = FALSE;
	m590_acquire();	
		m590_print(m590_init_cmd[AT]);
		DelayTask(50);
		m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer));	
		if(strstr(gReceiveBuffer, "OK"))
		{
			ok = TRUE;
		}	
	m590_release();	
	return ok;
}

#define IS_M590_OK()	while(is_m590_ok() == FALSE){DelayTask(1000);} DelayTask(1000);


uint8_t is_m590_ok_retry(uint8_t retries)
{
	while(is_m590_ok() == FALSE)
	{
		if(--retries == 0)
		{
			return FALSE;
		}
		DelayTask(1000);
	}
	return TRUE;
}

CHAR8 m590_getchar(void)
{
	INT8U caracter;
	if(OSQueuePend(M590_QUEUE, &caracter, M590_UART_TIMEOUT) == TIMEOUT)
	{
		return (CHAR8) (-1);
	}	
	return (CHAR8)caracter;
}

static void wait_m590_get_reply(uint16_t time)
{
	DelayTask(time);	
	m590_get_reply(gReceiveBuffer,(INT16U)sizeof(gReceiveBuffer));
}

static void m590_get_reply_print(void)
{
	wait_m590_get_reply(200);
	PRINT_BUF(gReceiveBuffer); 
	PRINT("\r\n");
}


	
#define GET_REPLY_PRINT()	m590_get_reply_print()
#define GET_REPLY()			m590_get_reply()
									

/****************************************************************************************
* Create PPP link
*****************************************************************************************/ 
INT8U CreatePPP(void)
{
    int timeout;  
	timeout = 3;
	
	m590_acquire();
	do
	{  	
		m590_print(m590_init_cmd[XIIC1]);
		wait_m590_get_reply(200);   // wait 200ms
		PRINT_BUF(gReceiveBuffer);
		
		if(strstr((char *)gReceiveBuffer,(char *)"OK"))
		{
			break;
		}
	}while(--timeout>0);	  
	
	m590_release();
	
    if(timeout==0)
	{
		return FALSE;
	}
	return TRUE;
}

/****************************************************************************************
* Create TCP Link
*****************************************************************************************/ 
INT8U CreateTCPLink(char *linkStr)
{
    int timeout;	
	
	timeout = 0;

	m590_print(linkStr);
		
	wait_m590_get_reply(1000); // wait 1000ms;
	PRINT_BUF(gReceiveBuffer);	
	
	if( strstr((char *)gReceiveBuffer,"+TCPSETUP:0,OK"))
	{
		PRINT("TCP established!\r\n");
		return TRUE;
	}
	return FALSE;
}
/****************************************************************************************
* TCP IP Send Data
*****************************************************************************************/
uint8_t TCPIP_SendData(uint8_t *dados, uint16_t tam)
{
	int timeout=0;
	uint8_t  c;
	uint16_t  length, len;	
	uint8_t *send;

	length = (uint16_t) tam;
	
    while(1)
	{
		
		m590_print(m590_init_cmd[IPSTAT]);
		wait_m590_get_reply(100); // wait 100ms;
		PRINT_BUF(gReceiveBuffer);
		
		if( strstr((char *)gReceiveBuffer,"+IPSTATUS:0,CONNECT,TCP") )
		{
			len = length;
			send = dados;			
			SNPRINTF(gReceiveBuffer,sizeof(gReceiveBuffer)-1, "at+tcpsend=0,%d\r",len);
			m590_print(gReceiveBuffer);			
			DelayTask(10); /* espera 10 ms */
			
			timeout = 0;
			
			retry:
			while((c=m590_getchar()) != (CHAR8)-1)
			{			
				putcharSer(USE_USB,c);
				if(c == '>')
				{					

					len = length;
					send = dados;					
					while(len > 0)
					{
						c=*send;
						m590_putchar(c);
						putcharSer(USE_USB,c);
						len--;
						send++;
					}	
					m590_putchar('\r');
					
					wait_m590_get_reply(100); // wait 100ms;
					PRINT_BUF(gReceiveBuffer);		
					
					if( strstr((char *)gReceiveBuffer,"+TCPSEND:0"))
					{
						PRINT("\r\nsend ok\r\n");
						
						m590_print(m590_init_cmd[IPSTAT]);
				
						timeout = 0;
						do
						{							
							wait_m590_get_reply(10);
							PRINT_BUF(gReceiveBuffer);							
							if( strstr((char *)gReceiveBuffer,"+TCPRECV:0"))
							{
#if 0
								do{
									len = m590_get_reply();
									PRINT_BUF(gReceiveBuffer);	
								}while(len > 0);	
#endif								
								return TRUE;
							}
							DelayTask(100);
						}while(++timeout < 20); /* espera ate 2 segundos */
						
						return TRUE;
						
					}
					else if( strstr((char *)gReceiveBuffer,"+TCPSEND:Error"))
					{
						PRINT("\r\nsend error\r\n");
						return FALSE;
					}
					else if( strstr((char *)gReceiveBuffer,"+TCPSEND:Buffer not enough"))
					{
						PRINT("\r\nsend error: Buffer not enough \r\n");
						return FALSE;
					}else
					{
						m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer));
						PRINT_BUF(gReceiveBuffer);
					}
				}
			}
			/* tempo do espera do modem para enviar dados (>) */
			if(++timeout > 50)
			{
				goto retry;
			}
		}
		
		out:
			PRINT("\r\nsend error, tcp connection failed \r\n");
			return FALSE;
	}
}

/****************************************************************************************
* Create Single TCP Link
*****************************************************************************************/
uint8_t CreateSingleTCPLink(uint8_t iLinkNum,char *strServerIP,char *strPort)
{
	memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));
	SNPRINTF(gReceiveBuffer,sizeof(gReceiveBuffer)-1,"AT+TCPSETUP=%d,%s,%s\r",iLinkNum,strServerIP,strPort);
	if(!CreateTCPLink(gReceiveBuffer))  
	{
		return FALSE;
	}
	return TRUE;
}

uint8_t m590_init(void)
{
	/* init M590_UART */
	uart_init(M590_UART,M590_BAUD,M590_UART_BUFSIZE,M590_MUTEX,M590_MUTEX_PRIO);
	
	if(!is_m590_ok_retry(5))
	{
		return FALSE;
	}
	
	/* check init */
	m590_acquire();	
	
	m590_print(m590_init_cmd[CREG]);
	GET_REPLY_PRINT();		
	
	m590_print(m590_init_cmd[XISP]);
	GET_REPLY_PRINT();

	m590_print(("AT+CGDCONT=1,\"IP\",\"" M590_APN "\"\r\n"));
	GET_REPLY_PRINT();

	m590_print(("AT+XGAUTH=1,1,\"" M590_PWD "\",\"" M590_PWD "\"\r\n"));
	GET_REPLY_PRINT();

	m590_print(m590_init_cmd[XIIC1]);
	GET_REPLY_PRINT();
	
	m590_print(m590_init_cmd[XIIC]);
	GET_REPLY_PRINT();
	
	m590_release();	
	
	m590_state = M590_INIT;
	
	return TRUE;
	
}
	
m590_ret_t at_m590_init(void)
{
		
	PRINT("Init \r\n");
		
	if(m590_init())
	{
		return M590_OK;	
	}
	
	return M590_ERR;	
	
}

uint8_t CheckPPP(void)
{
	uint8_t value;
		
	value = 3;	
	m590_acquire();	
	do
	{   	
		m590_print(m590_init_cmd[XIIC]);  	
		wait_m590_get_reply(500);	// 500ms	
		
		if(strstr((char *)gReceiveBuffer,"+XIIC:    1"))
		{
			m590_release();
			return TRUE;			
		}				
	}while(--value>0);			
		
	m590_release();	
	
	return FALSE;
}

uint8_t m590_open(void)
{
	uint8_t result_ok=FALSE;
	uint8_t timeout;
	
	timeout = 3;
	do{
		uint8_t retries = 3;
		if(CheckPPP()==TRUE)
		{
			result_ok = TRUE;
			break;
		}
		while(CreatePPP() == FALSE)
		{			
			if(--retries==0)
			{
				return 0;
			}
		}
	}while(--timeout>0);
	
	if(result_ok == TRUE)
	{
		m590_state = M590_OPEN;
		return TRUE;
	}else
	{
		return FALSE;
	}	

}

m590_ret_t at_m590_open(void)
{
	
	if(m590_state == M590_CLOSE)
	{
		PRINT("Init \r\n");
		if(!m590_init())
		{
			return M590_ERR;
		}
	}
	
	PRINT("Open \r\n");		
	if(m590_open())
	{
		PRINT("PPP established!\r\n");
		return M590_OK;
	}else
	{
		return M590_APCONN_ERR;
	}		
}

#define M590_TESTE 0
#if M590_TESTE		
#define CONST const
CONST char M590_SEND_STRING[] = "GET /input/post.json?json={p:3}&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1\r\nHost: emon-gpsnetcms.rhcloud.com\r\n\r\n\r\n";
CONST char M590_SEND_STRING2[] = "GET /monitor/set.json?monitorid=10&data=20,20,20,20&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1\r\nHost: emon-gpsnetcms.rhcloud.com\r\n\r\n\r\n";
#endif

m590_ret_t at_m590_send(INT8U* dados)
{
	INT8U result_ok=FALSE;
	
	if(dados == NULL) return M590_ERR;
	
#if 1	
	if(m590_state != M590_OPEN)
	{
		return M590_STATE_ERR;
	}
	
	IS_M590_OK();
	
	/* sending */	
	m590_acquire();
		
	if(CreateSingleTCPLink(0,"54.173.137.93","80") == TRUE)		
	{
	
		
#if M590_TESTE						
		result_ok = TCPIP_SendData(M590_SEND_STRING);		
#else				
		result_ok = TCPIP_SendData(dados,(uint8_t)strlen(dados));
	
#endif
	}
	else
	{
		PRINT("TCP connection fail\r\n");
	}	
	
	m590_release();
#else
	
	if(m590_get_hostname() == NULL)
	{
		m590_set_hostname("emon-gpsnetcms.rhcloud.com");
	}else
	{
		if(*m590_get_ip() == '\0')
		{
			m590_set_ip("54.173.137.93");
		}
	}
	
	if(m590_send(M590_SEND_STRING,SIZEARRAY(M590_SEND_STRING)))
	{
		result_ok =  TRUE;
	}else
	{
		PRINT("TCP send fail\r\n");
	}
	
#endif	
	
	if(result_ok == TRUE)
	{		
		return M590_OK;
	}else
	{
		return M590_TCPCONN_ERR;
	}
}

m590_ret_t at_m590_receive(CHAR8* buff, INT8U len)
{
	uint16_t size = len;
	if(buff == NULL)	return M590_ERR;
	
	/* try to receive */
	if((size = m590_receive(buff,&size)) > 0)
	{
		*(buff+(size)) = '\0'; // null terminate
		PRINT_BUF(buff);
	}		
	
	PRINT("\r\n");
		
		
	return M590_OK;
}

uint8_t m590_close(void)
{
	m590_acquire();	
		m590_print("AT+TCPCLOSE=0\r\n");	
		GET_REPLY_PRINT();
		m590_print("AT+TCPCLOSE=1\r\n");	
		GET_REPLY_PRINT();
	m590_release();		
	
	m590_state = M590_CLOSE;
	
	return TRUE;
}


m590_ret_t at_m590_close(void)
{

	PRINT("Close \r\n");
	
	IS_M590_OK();
	
	if(m590_state != M590_OPEN)
	{		
		m590_state = M590_CLOSE;		
	}else
	{
		m590_close();		
	}
		
	return M590_OK;	
}

m590_ret_t at_m590_dns(char* param)
{
	IS_M590_OK();
	
	m590_acquire();	
		
	m590_print("AT+DNSSERVER?\r");	
	GET_REPLY_PRINT();
	if(strstr(gReceiveBuffer,"+DNSSERVER:"))
	{
		if(param[2] != 0)
		{
			m590_print("AT+DNS=");
			m590_print((&param[2]));
			m590_print("\r\n");
		}		
	}
	
	m590_release();		
	return M590_OK;
}


m590_ret_t at_m590_server(void)
{
	
	int timeout = 0;
	INT8U c,idx;
	
	if(m590_state != M590_OPEN)
	{
		return M590_STATE_ERR;
	}
	
	
	IS_M590_OK();
	
	/* listening */	
	m590_acquire();
		
		m590_print("AT+TCPLISTEN=80\r");
		DelayTask(1000);
		
		while(1)
		{			
			idx = 0;
			while((c=m590_getchar()) != (CHAR8)-1)
			{			
				putcharSer(USE_USB,c); 			
			}	

			if(++timeout > 10000)
			{
				timeout = 0;
				break;
			}
		}	
		
	m590_print("AT+CLOSELISTEN\r\n");
	
	m590_release();		
	return M590_OK;
}

uint8_t m590_get_time(void)
{
	IS_M590_OK();
	
	m590_acquire();	
		m590_print(m590_init_cmd[CLK]);	
		GET_REPLY_PRINT();
	m590_release();		
	
	return TRUE;
}

m590_ret_t at_m590_time(void)
{
	m590_get_time();
	
	return M590_OK;
}

uint8_t m590_set_hostname(char *host)
{
	hostname = host;
	return MODEM_OK;
}

char* m590_get_hostname(void)
{
	return hostname;	
}

uint8_t m590_host_ip(void)
{
	if(hostname == NULL)
	{
		return MODEM_ERR;
	}
	
	m590_acquire();	
	m590_print("AT+DNS=\"");
	m590_print(hostname);
	m590_print("\"\r\n");
	m590_get_reply(ip,16);
	m590_release();		
}

char* m590_get_ip(void)
{
	return (char*)ip;
}

uint8_t m590_set_ip(char* _ip)
{
	if(hostname == NULL || _ip == NULL)
	{
		return MODEM_ERR;
	}
	strcpy(ip,_ip);	
	return MODEM_OK;
}

uint8_t m590_send(uint8_t * dados, uint16_t tam)
{
	
	uint8_t retries = 0;
	uint8_t result_ok = FALSE;
	
	if(dados == NULL) return MODEM_ERR;	
	*(dados+tam) = '\0'; // null terminate
	ip[15] ='\0';
	
	/** testar isso */
	if(m590_state == M590_OPEN)
	{
		/* sending */	
		m590_acquire();					
		result_ok = TCPIP_SendData(dados, tam);				
		m590_release();			
		if(result_ok == TRUE) return MODEM_OK;
	}
	
	if(!is_m590_ok_retry(5))
	{		
		return MODEM_ERR; 
	}
	
	while(retries < 3)
	{
		++retries;
		if(m590_state == M590_CLOSE)
		{
			if(!m590_init())
			{
				return MODEM_ERR; 
			}
		}	
	
		if(m590_state == M590_INIT)
		{
			if(!m590_open())
			{
				m590_state = M590_CLOSE;
				return MODEM_ERR; // error
			}
		}
	
		DelayTask(500);
		
		/* sending */	
		m590_acquire();		
		
		if(CreateSingleTCPLink(0,ip,"80") == TRUE)		
		{						
			result_ok = TCPIP_SendData(dados, tam);
			break;
		}		
		else
		{
			m590_close();	
		}
		
		m590_release();	
	}
	
	return (result_ok==TRUE?MODEM_OK:MODEM_ERR);	
	
}


uint8_t m590_receive(uint8_t* buff, uint16_t* len)
{

	uint8_t ret = MODEM_ERR;
	uint16_t size =(uint16_t) MIN(*len,SIZEARRAY(gReceiveBuffer));
	
	*len = 0;

	if(size)
	{
		m590_acquire();	
		
		    if(gReceiveBuffer[0] !='\0')
		    {		
		    	ret = MODEM_OK;
				memcpy(buff,gReceiveBuffer,size);
				if(size < SIZEARRAY(gReceiveBuffer))
				{
					memcpy(gReceiveBuffer,&gReceiveBuffer[size],SIZEARRAY(gReceiveBuffer)-size);				
				}
			
				m590_get_reply(&gReceiveBuffer[SIZEARRAY(gReceiveBuffer)-size],size);
				* len = size;
		    }
		    
		m590_release();	
	}
	
	return (uint8_t)ret;
}


uint8_t m590_check_connection(void)
{
	is_m590_ok_retry(5);
}

const modem_driver_t m590_driver  =
{
		m590_receive,
		m590_send,
		m590_set_hostname,
		m590_set_ip,
		m590_check_connection
};





