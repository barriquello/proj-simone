/*
 * m590_at.c
 *
 *  Created on: Aug 7, 2015
 *      Author: UFSM
 */

#include "m590_at.h"
#include "BRTOS.h"
#include "printf_lib.h"
#include "utils.h"
#include "terminal_commands.h"
#include "string.h"

#ifdef _WIN32
#include <stdio.h>
#endif


INT8U CreatePPP(void);
INT8U CreateTCPLink(char *linkStr);
INT8U CreateSingleTCPLink(unsigned char iLinkNum,char *strServerIP,char *strPort);
INT8U TCPIP_SendData(INT8U * dados);
INT8U is_m590_ok(void);

static m590_state_t m590_state = M590_INIT;
static char ip[16];
static char *hostname = NULL;
static INT8U gReceiveBuffer[256];

#define DEBUG_PRINT 0

#if DEBUG_PRINT
#define PRINT(...) 		printSer(USE_USB,__VA_ARGS__);
#define PRINT_BUF(...)  printSer(USE_USB,__VA_ARGS__);
#else
#define PRINT(...)
#define PRINT_BUF(...)
#endif

#define UNUSED(x)   (void)x;

static void at_m590_print_reply(void)
{
	INT8U c;
	DelayTask(1000);
	while((c=at_m590_getchar()) != (CHAR8)-1){
		putcharSer(USE_USB,c);
	}
}

static INT8U at_m590_get_reply(INT8U *buf, INT16U max_len)
{
	INT8U c;
	INT8U len = 0;
	while((c=at_m590_getchar()) != (CHAR8)-1){
		*buf = c;
		buf++;
		len++;
		max_len--;
		if(max_len <= 1) 
		{
			buf[len] = '\0';
			return len;
		}
	}
	buf[len] = '\0';
	return len;
}

INT8U is_m590_ok(void)
{
	INT8U ok = FALSE;
	m590_acquire();	
		m590_print("AT\r\n");
		memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer)); 
		at_m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer));	
		if(strstr(gReceiveBuffer, "OK"))
		{
			ok = TRUE;
		}	
	m590_release();	
	return ok;
}

#define IS_M590_OK()	while(is_m590_ok() == FALSE){DelayTask(1000);} DelayTask(1000);

CHAR8 at_m590_getchar(void)
{
	INT8U caracter;
	if(OSQueuePend(M590_QUEUE, &caracter, M590_UART_TIMEOUT) == TIMEOUT)
	{
		return (CHAR8) (-1);
	}	
	return (CHAR8)caracter;
}

static void m590_get_reply_print(void)
{
	DelayTask(200);
	memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));
	at_m590_get_reply(gReceiveBuffer,(INT16U)sizeof(gReceiveBuffer)); 
	PRINT_BUF(gReceiveBuffer); 
	printSer(USE_USB,"\r\n");
}

static void m590_get_reply(void)
{
	DelayTask(200);
	memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));
	at_m590_get_reply(gReceiveBuffer,(INT16U)sizeof(gReceiveBuffer));
}
	
#define GET_REPLY_PRINT()	m590_get_reply_print()
#define GET_REPLY()			m590_get_reply()
									

/****************************************************************************************
* Create PPP link
*****************************************************************************************/ 
INT8U CreatePPP(void)
{
    int timeout;  

	timeout = 0;
	do
	{  
		timeout++;		
		m590_print("at+xiic=1\r");
    	DelayTask(200);   // wait 200ms

		memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));
		at_m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer));
		PRINT_BUF(gReceiveBuffer);
		
		if(strstr((char *)gReceiveBuffer,(char *)"OK"))
		{
			break;
		}
	}while(timeout<3);	  
	
    if( timeout>=3)
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
		
	DelayTask(1000);   // wait 1000ms;
		
	memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));
	at_m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer));
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
INT8U TCPIP_SendData(INT8U * dados)
{
	int timeout=0;
	INT8U  c;
	INT8U  length, len;	
	INT8U *send;
	
	length = (INT8U) strlen(dados);
	
    while(1)
	{
		
		m590_print("at+ipstatus=0\r");
		DelayTask(100);

		memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));
		at_m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer));
		PRINT_BUF(gReceiveBuffer);
		
		if( strstr((char *)gReceiveBuffer,"+IPSTATUS:0,CONNECT,TCP") )
		{
			len = length;
			send = dados;			
			SNPRINTF(gReceiveBuffer,sizeof(gReceiveBuffer)-1, "at+tcpsend=0,%d\r",len);
			m590_print(gReceiveBuffer);			
			DelayTask(10);
			
			timeout = 0;
			
			retry:
			while((c=at_m590_getchar()) != (CHAR8)-1)
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
					
					DelayTask(100);
					
					memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));
					at_m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer));
					PRINT_BUF(gReceiveBuffer);		
					
					if( strstr((char *)gReceiveBuffer,"+TCPSEND:0"))
					{
						PRINT("\r\nsend ok\r\n");
						
						m590_print("at+ipstatus=0\r");
						DelayTask(10);
						timeout = 0;
						do
						{
							memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));
							len = at_m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer));
							PRINT_BUF(gReceiveBuffer);							
							if( strstr((char *)gReceiveBuffer,"+TCPRECV:0"))
							{
								do{
									memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));
									len = at_m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer));
									PRINT_BUF(gReceiveBuffer);	
								}while(len > 0);								
								return TRUE;
							}
							DelayTask(100);
						}while(++timeout < 1000);
						
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
						memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));
						at_m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer));
						PRINT_BUF(gReceiveBuffer);
					}
				}
			}
			
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
INT8U CreateSingleTCPLink(unsigned char iLinkNum,char *strServerIP,char *strPort)
{
	memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));
	SNPRINTF(gReceiveBuffer,sizeof(gReceiveBuffer)-1,"AT+TCPSETUP=%d,%s,%s\r",iLinkNum,strServerIP,strPort);
	if(!CreateTCPLink(gReceiveBuffer))  
	{
		return FALSE;
	}
	return TRUE;
}
	
#define CONST 
CONST char m590_init_cmd[][11] = 
{
		"AT+CREG?\r\n ",
		"AT+XISP=0\r\n",
		"AT+XISP=0\r\n",
		"AT+XIIC=1\r\n",
		"AT+XIIC?\r\n "
};
m590_ret_t at_m590_init(void)
{
		
	printSer(USE_USB,"Init \r\n");
	
	/* init M590_UART */
	uart_init(M590_UART,M590_BAUD,M590_UART_BUFSIZE,M590_MUTEX,M590_MUTEX_PRIO);
	
	IS_M590_OK();
	
	/* check init */
	m590_acquire();	
	
	//m590_print("AT+CREG?\r\n");
	m590_print(m590_init_cmd[0]);
	GET_REPLY_PRINT();		
	
	//m590_print("AT+XISP=0\r\n");
	m590_print(m590_init_cmd[1]);
	GET_REPLY_PRINT();

	m590_print(("AT+CGDCONT=1,\"IP\",\"" M590_APN "\"\r\n"));
	GET_REPLY_PRINT();

	m590_print(("AT+XGAUTH=1,1,\"" M590_PWD "\",\"" M590_PWD "\"\r\n"));
	GET_REPLY_PRINT();

	//m590_print("AT+XIIC=1\r\n");
	m590_print(m590_init_cmd[2]);
	GET_REPLY_PRINT();
	
	//m590_print("AT+XIIC?\r\n");
	m590_print(m590_init_cmd[3]);
	GET_REPLY_PRINT();
	
	m590_release();		
	
	m590_state = M590_CLOSE;
	return M590_OK;
	
}

m590_ret_t at_m590_open(void)
{
	
	INT8U result_ok=FALSE;
	INT8U value;
	
	if(m590_state != M590_CLOSE)
	{
		PRINT("Open fail \r\n");
		return M590_STATE_ERR;		
	}
	
	printSer(USE_USB,"Open \r\n");
	
	IS_M590_OK();
	
	m590_acquire();	
		
		value = 0;
		do
		{   
			value++;			
			m590_print("AT+XIIC?\r\n");	    	
	    	DelayTask(500);   // 500ms	

			GET_REPLY_PRINT();		
			
			if(strstr((char *)gReceiveBuffer,"+XIIC:    1"))
			{
				result_ok = TRUE;
				PRINT("PPP established!\r\n");
				break;
			}else
			{
				CreatePPP();
			}
			
		}while(value<3);			
	
	m590_release();	
	
	printSer(USE_USB,"\r\n");	

	if(result_ok == TRUE)
	{
		m590_state = M590_OPEN;
		return M590_OK;
	}else
	{
		return M590_APCONN_ERR;
	}	
	
}

#define M590_TESTE 1
#if M590_TESTE		
#define CONST 
CONST char M590_SEND_STRING[] = "GET /input/post.json?json={p:3}&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1\r\nHost: emon-gpsnetcms.rhcloud.com\r\n\r\n\r\n";
CONST char M590_SEND_STRING2[] = "GET /monitor/set.json?monitorid=10&data=20,20,20,20&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1\r\nHost: emon-gpsnetcms.rhcloud.com\r\n\r\n\r\n";
#endif

m590_ret_t at_m590_send(INT8U* dados)
{
	INT8U idx;
	INT8U result_ok=FALSE;
	
	if(m590_state != M590_OPEN)
	{
		return M590_STATE_ERR;
	}
	
	IS_M590_OK();
	
	/* sending */	
	m590_acquire();
	
	//if(CreateTCPLink("AT+TCPSETUP=0,54.173.137.93,80\r\n") == TRUE)
	if(CreateSingleTCPLink(0,"54.173.137.93","80") == TRUE)		
	{
		result_ok = TRUE;
		
#if M590_TESTE						
		TCPIP_SendData(M590_SEND_STRING);		
#else	
		if(dados != NULL)
		{
			TCPIP_SendData(dados);
		}
#endif
	}
	else
	{
		PRINT("TCP connection fail\r\n");
	}	
	
	m590_release();		
	
	if(result_ok == TRUE)
	{		
		return M590_OK;
	}else
	{
		return M590_TCPCONN_ERR;
	}
}

m590_ret_t at_m590_receive(CHAR8* buff, INT8U* len)
{
	
	m590_acquire();	
		*len = at_m590_get_reply(buff,*len);
	m590_release();	
	
	printSer(USE_USB,"\r\n");
		
	/* try to receive */	
	return M590_OK;
}

m590_ret_t at_m590_close(void)
{

	printSer(USE_USB,"Close \r\n");
	
	IS_M590_OK();
	
	if(m590_state == M590_OPEN)
	{		
		m590_acquire();	
			m590_print("AT+TCPCLOSE=0\r\n");	
			GET_REPLY_PRINT();
			m590_print("AT+TCPCLOSE=1\r\n");	
			GET_REPLY_PRINT();
		m590_release();		
		printSer(USE_USB,"\r\n");
	}
		
	m590_state = M590_CLOSE;
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
			while((c=at_m590_getchar()) != (CHAR8)-1)
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


INT8U m590_set_hostname(CHAR8 *host)
{
	hostname = host;
	return OK;
}

INT8U m590_get_ip(void)
{
	if(hostname == NULL)
	{
		return !OK;
	}
	
	m590_acquire();	
	m590_print("AT+DNS=\"");
	m590_print(hostname);
	m590_print("\"\r\n");
	at_m590_get_reply(ip,16);
	m590_release();		
}

INT8U m590_set_ip(char* _ip)
{
	if(hostname == NULL || _ip == NULL)
	{
		return !OK;
	}
	strcpy(ip,_ip);	
	return OK;
}

