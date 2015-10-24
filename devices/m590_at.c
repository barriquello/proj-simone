/* The License
 * 
 * Copyright (c) 2015 Universidade Federal de Santa Maria
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.

*/
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

static m590_state_t m590_state = M590_SETUP;
static char ip[16];
static char *hostname = NULL;
static INT8U gReceiveBuffer[256];

#define DEBUG_PRINT 1

#if DEBUG_PRINT
#define PRINT(...) 		printSer(USE_USB,__VA_ARGS__);
#define PRINT_BUF(...)  //printSer(USE_USB,__VA_ARGS__);
#define PRINT_REPLY(...)  printSer(USE_USB,__VA_ARGS__);
#else
#define PRINT(...)
#define PRINT_BUF(...)
#define PRINT_REPLY(...)  
#endif

#define UNUSED(x)   (void)x;
#define MAX_RETRIES		2

#define DEBUG_PUTCHAR	0

#if DEBUG_PUTCHAR
#define DPUTCHAR(x)		putcharSer(USE_USB,x);
#else
#define DPUTCHAR(x)		
#endif

typedef enum
{
	AT = 0,
	CREG,
	XISP,
	XIIC1,
	XIIC,
	IPSTAT,
	CLK,
	CLOSE0,
	CLOSE1,
}m590_enum_cmd;

#define AT_def		"AT\r\n"
#define	CREG_def	"AT+CREG?\r\n"
#define	XISP_def	"AT+XISP=0\r\n"
#define XIIC1_def	"AT+XIIC=1\r\n"
#define	XIIC_def	"AT+XIIC?\r\n"
#define IPSTAT_def  "AT+IPSTATUS=0\r"
#define	CLK_def		"AT+CCLK?\r\n"
#define	CLOSE0_def	"AT+TCPCLOSE=0\r\n"
#define	CLOSE1_def  "AT+TCPCLOSE=1\r\n"
	
#define CONST const	
		
#if ARDUINO
CONST char AT_str[]    PROGMEM = AT_def;
CONST char CREG_str[]  PROGMEM = CREG_def;
CONST char XISP_str[]	PROGMEM = XISP_def;
CONST char XIIC1_str[]	PROGMEM = XIIC1_def;
CONST char XIIC_str[]	PROGMEM = XIIC_def;
CONST char IPSTAT_str[] PROGMEM = IPSTAT_def;
CONST char CLK_str[]	PROGMEM = CLK_def;
CONST char CLOSE0_str[] PROGMEM = CLOSE0_def;
CONST char CLOSE1_str[] PROGMEM = CLOSE1_def;

CONST char * const m590_init_cmd[] PROGMEM =
{
	AT_str,
	CREG_str,
	XISP_str,
	XIIC1_str,
	XIIC_str,
	IPSTAT_str,
	CLK_str,
	CLOSE0_str,
	CLOSE1_str
};

#elif COLDUINO
#define PROGMEM
CONST char *m590_init_cmd[] = 
{
	AT_def,
	CREG_def,
	XISP_def,
	XIIC1_def,
	XIIC_def,
	IPSTAT_def,
	CLK_def,
	CLOSE0_def,
	CLOSE1_def
};

#endif

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
	while((c=m590_getchar()) != (CHAR8)-1)
	{
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
		DelayTask(100);
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
	wait_m590_get_reply(100);
	PRINT_BUF(gReceiveBuffer); 
	//PRINT("\r\n");
}


	
#define GET_REPLY_PRINT()	m590_get_reply_print()
#define GET_REPLY()			m590_get_reply()
									

/****************************************************************************************
* Create PPP link
*****************************************************************************************/ 
INT8U CreatePPP(void)
{
    int timeout;  
	timeout = MAX_RETRIES;
	
	m590_acquire();
	do
	{  	
		m590_print(m590_init_cmd[XIIC1]);
		wait_m590_get_reply(100);   // wait 100ms // era 200ms
				
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
    uint8_t retries = MAX_RETRIES;
    
	m590_print(linkStr);
		
	try_again:
	
	wait_m590_get_reply(500); // wait 100ms; // era 1s 
	PRINT_BUF(gReceiveBuffer);	
	
	if( strstr((char *)gReceiveBuffer,"+TCPSETUP:0,OK"))
	{		
		PRINT("TCP ok!\r\n");
		return TRUE;
	}
	if(--retries > 0) goto try_again;
	return FALSE;
}

/****************************************************************************************
* Create Single TCP Link
*****************************************************************************************/
uint8_t CreateSingleTCPLink(uint8_t iLinkNum,char *strServerIP,char *strPort)
{
	
	if(iLinkNum == 0)
	{
		m590_print(m590_init_cmd[CLOSE0]);
	}else
	{
		m590_print(m590_init_cmd[CLOSE1]);
	}	
	GET_REPLY_PRINT();
	
	memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));	
	SNPRINTF(gReceiveBuffer,sizeof(gReceiveBuffer)-1,"AT+TCPSETUP=%d,%s,%s\r",iLinkNum,strServerIP,strPort);
	
	if(CreateTCPLink(gReceiveBuffer) == FALSE)  
	{
		PRINT("tcp create fail\r\n");		
		return FALSE;
	}
	return TRUE;
}
/****************************************************************************************
* TCP IP Send Data
*****************************************************************************************/
uint8_t TCPIP_SendData(uint8_t *dados, uint16_t tam)
{
	uint16_t timeout=0;
	uint16_t retries=0;
	
	uint8_t  c;
	uint16_t  length, len;	
	uint8_t *send;

	length = (uint16_t) tam;		
	m590_print(m590_init_cmd[IPSTAT]);
	wait_m590_get_reply(100); // wait 100ms;
	PRINT_BUF(gReceiveBuffer);
	
	if( strstr((char *)gReceiveBuffer,"+IPSTATUS:0,CONNECT") )
	{
		len = length;
		send = dados;			
		SNPRINTF(gReceiveBuffer,sizeof(gReceiveBuffer)-1, "at+tcpsend=0,%d\r",len);
		m590_print(gReceiveBuffer);			
		DelayTask(10); /* espera 10 ms */	
		
		retries = MAX_RETRIES;
		
		do{						
			while((c=m590_getchar()) != (CHAR8)-1)
			{			
				DPUTCHAR(c);
				if(c == '>')
				{					

					len = length;
					send = dados;					
					while(len > 0)
					{
						c=*send;
						m590_putchar(c);
						DPUTCHAR(c);
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
								PRINT("reply ok\r\n");
								return TRUE;
							}
							DelayTask(100);
						}while(++timeout < 20); /* espera ate 2 segundos */
						
						return FALSE;
						
					}
					else if( strstr((char *)gReceiveBuffer,"+TCPSEND:Error"))
					{
						PRINT("send error\r\n");
						return FALSE;
					}
					else if( strstr((char *)gReceiveBuffer,"+TCPSEND:Buffer not enough"))
					{
						PRINT("buffer error\r\n");
						return FALSE;
					}else
					{
						m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer));
						PRINT_BUF(gReceiveBuffer);
					}
				}
			}
		}while(retries-- > 0);
	}
	
	out:
		PRINT("tcp conn failed\r\n");
		return FALSE;
}


uint8_t m590_init(void)
{
	
	if(m590_state == M590_SETUP)
	{
		/* init M590_UART */
		uart_init(M590_UART,M590_BAUD,M590_UART_BUFSIZE,M590_MUTEX,M590_MUTEX_PRIO);
		
		/* setup */
		m590_acquire();			
			m590_print(m590_init_cmd[CREG]);
			GET_REPLY_PRINT();	
		m590_release();	
	}
	
	if(!is_m590_ok_retry(2))
	{
		return FALSE;
	}

	m590_acquire();	

	m590_print(m590_init_cmd[XISP]);
	GET_REPLY_PRINT();
	
	m590_print(("AT+CGDCONT=1,\"IP\",\"" M590_APN "\"\r\n"));
	GET_REPLY_PRINT();

	m590_print(("AT+XGAUTH=1,1,\"" M590_PWD "\",\"" M590_PWD "\"\r\n"));
	GET_REPLY_PRINT();

	m590_print(m590_init_cmd[XIIC1]);
	GET_REPLY_PRINT();
	
#if 0	
	m590_print(m590_init_cmd[XIIC]);
	GET_REPLY_PRINT();
#endif	
	
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
		
	value = MAX_RETRIES;	
	m590_acquire();	
	do
	{   	
		m590_print(m590_init_cmd[XIIC]);  	
		wait_m590_get_reply(100);	// 100ms	// era 500ms
		PRINT_REPLY(gReceiveBuffer);

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
	
	timeout = MAX_RETRIES;
	do{
		uint8_t retries = MAX_RETRIES;
		if(CheckPPP()==TRUE)
		{
			result_ok = TRUE;
			break;
		}
		while(CreatePPP() == FALSE)
		{			
			if(--retries==0)
			{
				return FALSE;
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
		PRINT("PPP ok!\r\n");
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
		PRINT("TCP conn fail\r\n");
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
		m590_print(m590_init_cmd[CLOSE0]);	
		GET_REPLY_PRINT();
		//m590_print("AT+TCPCLOSE=1\r\n");	
		//GET_REPLY_PRINT();
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
		
		if(result_ok == TRUE) 
		{
			return MODEM_OK;
		}else
		{
			m590_state = M590_CLOSE;
		}
	}
	
	while(retries < MAX_RETRIES)
	{
		++retries;
		if(m590_state == M590_CLOSE)
		{
			if(m590_init() == FALSE)
			{
				m590_state = M590_CLOSE;
				//PRINT("modem init fail\r\n");
				return MODEM_ERR; 
			}
		}	
	
		if(m590_state == M590_INIT)
		{
			if(m590_open() == FALSE)
			{
				continue;
			}
		}
	
		//DelayTask(500);
		
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
			m590_state = M590_INIT;
		}
		
		m590_release();			
	}
	
	if(retries == MAX_RETRIES) m590_state = M590_CLOSE;
	
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
	return is_m590_ok_retry(MAX_RETRIES);
}

const modem_driver_t m590_driver  =
{
		m590_init,
		m590_receive,
		m590_send,
		m590_set_hostname,
		m590_set_ip,
		m590_check_connection
};





