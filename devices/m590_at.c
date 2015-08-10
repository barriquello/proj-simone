/*
 * m590_at.c
 *
 *  Created on: Aug 7, 2015
 *      Author: Gisele
 */



#include "m590_at.h"
#include "BRTOS.h"
#include "utils.h"
#include "usb_terminal_commands.h"
#include "string.h"
#include "stdio.h"

INT8U CreatePPP(void);
INT8U CreateTCPLink(char *linkStr);
INT8U CreateSingleTCPLink(unsigned char iLinkNum,char *strServerIP,char *strPort);
INT8U TCPIP_SendData(INT8U * dados);

static m590_state_t m590_state = M590_INIT;
static char ip[16];
static char* hostname = NULL;

static INT8U gSendBuffer[32];
static INT8U gReceiveBuffer[256];

#define UNUSED(x)   (void)x;

static void at_m590_print_reply(void)
{
	INT8U c;
	DelayTask(1000);
	while((c=at_m590_getchar()) != (CHAR8)-1){
		putchar_usb(c);
	}
}

static INT8U at_m590_get_reply(INT8U *buf, INT16U max_len)
{
	INT8U c;
	INT8U len = 0;
	DelayTask(1000);
	while((c=at_m590_getchar()) != (CHAR8)-1){
		*buf = c;
		buf++;
		len++;
		max_len--;
		if(max_len == 0) return len;
	}
	return len;
}

INT8U m590_set_hostname(CHAR8 *host)
{
	hostname = host;
	return OK;
}

INT8U m590_set_ip(void)
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
	//at_m590_print_reply();
	m590_release();		
}

CHAR8 at_m590_getchar(void)
{
	INT8U caracter;
	if(OSQueuePend(M590_QUEUE, &caracter, M590_UART_TIMEOUT) == TIMEOUT)
	{
		return (CHAR8) (-1);
	}	
	return (CHAR8)caracter;
}

#define GET_REPLY_PRINT()			DelayTask(200);   \
									memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer)); \
									at_m590_get_reply(gReceiveBuffer,(INT16U)sizeof(gReceiveBuffer)); \
									printSer(USE_USB,gReceiveBuffer); \
									

/****************************************************************************************
* CreatePPP
*****************************************************************************************/ 
INT8U CreatePPP(void)
{
    int timeout;  

	timeout = 0;
	do
	{  
		timeout++;		
		m590_print("at+xiic=1\r");
    	DelayTask(200);                  // 200ms

		memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));
		at_m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer));
		printSer(USE_USB,gReceiveBuffer);
		
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
*CreateTCPLink
*****************************************************************************************/ 
INT8U CreateTCPLink(char *linkStr)
{
    int timeout;	
	
	timeout = 0;

	m590_print(linkStr);
		
	DelayTask(1000);   // 1000ms;
		
	memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));
	at_m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer));
	printSer(USE_USB,gReceiveBuffer);	
	
	if( strstr((char *)gReceiveBuffer,"+TCPSETUP:0,OK"))
	{
		printSer(USE_USB, "TCP established!\r\n");
		return TRUE;
	}
	return FALSE;
}
/****************************************************************************************
* TCPIP_SendData
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
		printSer(USE_USB,gReceiveBuffer);
				
#if 0		
		if( strstr((char *)gReceiveBuffer,"+IPSTATUS:0,DISCONNECT") )
		{
			return FALSE;
		}
#endif		
		
		if( strstr((char *)gReceiveBuffer,"+IPSTATUS:0,CONNECT,TCP") )
		{
			len = length;
			send = dados;			
			snprintf(gSendBuffer,sizeof(gSendBuffer)-1, "at+tcpsend=0,%d\r",len);
			m590_print(gSendBuffer);			
			DelayTask(10);
			
			timeout = 0;
			
			retry:
			while((c=at_m590_getchar()) != (CHAR8)-1)
			{			
				putcharSer(USE_USB,c);
				if(c == '>')
				{					
					
					//putcharSer(USE_USB,c);
					
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
					
					memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));
					at_m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer));
					printSer(USE_USB,gReceiveBuffer);		
					
					if( strstr((char *)gReceiveBuffer,"+TCPSEND:0"))
					{
						printSer(USE_USB,"\r\nsend ok\r\n");
						
						m590_print("at+ipstatus=0\r");
						DelayTask(10);
						do
						{
							memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));
							len = at_m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer));
							printSer(USE_USB,gReceiveBuffer);
						}while(len);
																		
						return TRUE;
					}
					else if( strstr((char *)gReceiveBuffer,"+TCPSEND:Error"))
					{
						printSer(USE_USB,"\r\nsend error\r\n");
						return FALSE;
					}
					else if( strstr((char *)gReceiveBuffer,"+TCPSEND:Buffer not enough"))
					{
						printSer(USE_USB,"\r\nsend error: Buffer not enough \r\n");
						return FALSE;
					}else
					{
						memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));
						at_m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer));
						printSer(USE_USB,gReceiveBuffer);
					}
				}
			}
			
			if(++timeout > 50)
			{
				goto retry;
			}
		}
		
		out:
			printSer(USE_USB,"\r\nsend error, tcp connection failed \r\n");
			return FALSE;
	}
}

/****************************************************************************************
* CreateSingleTCPLink
*****************************************************************************************/
INT8U CreateSingleTCPLink(unsigned char iLinkNum,char *strServerIP,char *strPort)
{
	INT16U length;
	char buffer[50];
	
	memset(buffer,0x00,sizeof(buffer));
	sprintf(buffer,"AT+TCPSETUP=%d,%s,%s\r",iLinkNum,strServerIP,strPort);
	length = (INT16U)strlen((char *)buffer);
	if( !CreateTCPLink(buffer))  
	{
		return FALSE;
	}
	return TRUE;
}
									
m590_ret_t at_m590_init(void)
{
	
#if 0	
	if(m590_state != M590_INIT)
	{
		printSer(USE_USB,"Init fail \r\n");
		return M590_STATE_ERR;
	}
#endif	
	
	printSer(USE_USB,"Init \r\n");
	
	/* init M590_UART */
	uart_init(M590_UART,M590_BAUD,M590_UART_BUFSIZE,M590_MUTEX,M590_MUTEX_PRIO);
	
	/* check init */
	m590_acquire();	
	m590_print("AT\r\n");	
	GET_REPLY_PRINT();
	m590_release();
	printSer(USE_USB,"\r\n");
	
	m590_acquire();	
	m590_print("AT+CREG?\r\n");
	GET_REPLY_PRINT();
	m590_release();	
	printSer(USE_USB,"\r\n");	
	
	m590_acquire();	
	m590_print("AT+XISP=0\r\n");
	GET_REPLY_PRINT();
	m590_release();	
	printSer(USE_USB,"\r\n");	
	
	m590_acquire();
	m590_print(("AT+CGDCONT=1,\"IP\",\"" M590_APN "\"\r\n"));
	GET_REPLY_PRINT();
	m590_release();	
	printSer(USE_USB,"\r\n");
	
	m590_acquire();
	m590_print(("AT+XGAUTH=1,1,\"" M590_PWD "\",\"" M590_PWD "\"\r\n"));
	GET_REPLY_PRINT();
	m590_release();	
	printSer(USE_USB,"\r\n");	
	
	m590_acquire();
	m590_print("AT+XIIC=1\r\n");
	GET_REPLY_PRINT();
	m590_release();	
	printSer(USE_USB,"\r\n");	
	
	m590_acquire();
	m590_print("AT+XIIC?\r\n");
	GET_REPLY_PRINT();
	m590_release();	
	printSer(USE_USB,"\r\n");
	
	m590_state = M590_CLOSE;
	return M590_OK;
	
}

m590_ret_t at_m590_open(void)
{
	
	INT8U result_ok=FALSE;
	INT8U value;
	
	if(m590_state != M590_CLOSE)
	{
		printSer(USE_USB,"Open fail \r\n");
		return M590_STATE_ERR;		
	}
	
	printSer(USE_USB,"Open \r\n");
	
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
				printSer(USE_USB, "PPP established!\r\n");
				break;
			}else
			{
				CreatePPP();
			}
			
		}while(value<3);			
	
	m590_release();	
	
	printSer(USE_USB,"\r\n");	

	m590_state = M590_OPEN;
	
	return M590_OK;
}

#define SEND_STRING "AT+CIPSENDI=0,\"GET /input/post.json?json={p:3}&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1\\r\\nHost: emon-gpsnetcms.rhcloud.com\\r\\n\\r\\n\\r\\n\""

#define SEND_STRING1 "AT+CIPSENDI=0,\"GET /input/post.json?json={"
//#define SEND_STRING2 ("}&" API_KEY " HTTP/1.1\r\nHost: " ESP_TCP_SERVER_NAME "\r\n\r\n\r\n")
#define SEND_STRING2 "}&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1\\r\\nHost: emon-gpsnetcms.rhcloud.com\\r\\n\\r\\n\\r\\n\""

m590_ret_t at_m590_send(INT8U num, CHAR8* field, CHAR8* val)
{
	INT8U idx;
	UNUSED(num); UNUSED(field); UNUSED(val);
	if(m590_state != M590_OPEN)
	{
		return M590_STATE_ERR;
	}
	
	/* sending */	
	m590_acquire();
	
#if 1		
	//CreateSingleTCPLink(0,"200.132.39.117","80");
	if(CreateTCPLink("AT+TCPSETUP=0,200.132.39.117,80\r\n") == TRUE)
	{
		//TCPIP_SendData("get / HTTP/1.1\\r\\nHost: www.ufsm.br\\r\\n\\r\\n\\r\\n\r");
		TCPIP_SendData("GET / HTTP/1.1\r\nHost: www.ufsm.br\r\n\r\n\r\n");
		//TCPIP_SendData("GET / HTTP/1.0   \\r\\n\\r\\n\\r\\n\r");
		//TCPIP_SendData("0123456789abcdefghijklmnopqrstuvxyz\r");
	}
	else
	{
		printSer(USE_USB, "TCP connection fail\r\n");
	}
	
#else	
	m590_print(SEND_STRING1);
	for (idx = 0; idx<num; idx++)
	{
		//m590_print(field[idx]);
		m590_print(field);
		m590_putchar(':');
		//m590_print(val[idx]);		
		m590_print(val);
	}
	m590_print(SEND_STRING2);
	
	//m590_print("\r\n");
	//at_m590_print_reply();
	printSer(USE_USB,"\r\n");
#endif	
	
	m590_release();	
	
	return M590_OK;
}

m590_ret_t at_m590_receive(CHAR8* buff, INT8U* len)
{

	if(m590_state != M590_OPEN)
	{
		return M590_STATE_ERR;
	}
	
	m590_acquire();	
	//m590_print("AT+CIPRD=0\r\n");	
	*len = at_m590_get_reply(buff,*len);
	//at_m590_print_reply();
	m590_release();		
	printSer(USE_USB,"\r\n");
		
	/* try to receive */
	
	return M590_OK;
}

m590_ret_t at_m590_close(void)
{

	printSer(USE_USB,"Close \r\n");
	
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

m590_ret_t at_m590_server(void)
{
	
	int timeout = 0;
	INT8U c,idx;
	
	if(m590_state != M590_OPEN)
	{
		return M590_STATE_ERR;
	}
	
	/* listening */	
	m590_acquire();
		
		m590_print("AT+TCPLISTEN=80\r");
		//DelayTask(1000);
		
		while(1)
		{
			
#if 1
			idx = 0;
			while((c=at_m590_getchar()) != (CHAR8)-1)
			{			
				putcharSer(USE_USB,c); 			
			}	
#if 0				
				gReceiveBuffer[idx++] = c;	
				if(idx >= sizeof(gReceiveBuffer))
				{
					idx = 0;
				}
#endif				
				
			
#if 0
			if (idx > 0)
			{
				printSer(USE_USB,gReceiveBuffer);
				if( strstr((char *)gReceiveBuffer,"+TCPRECV(S)"))
				{
					printSer(USE_USB,"\r\nrecebido ok\r\n");
					
				}				
				memset(gReceiveBuffer,0x00,sizeof(gReceiveBuffer));	
				idx = 0;
			}
#endif			

#else
			while(at_m590_get_reply(gReceiveBuffer,sizeof(gReceiveBuffer)))
			{
				printSer(USE_USB,gReceiveBuffer);
				if( strstr((char *)gReceiveBuffer,"+TCPRECV(S)"))
				{
					printSer(USE_USB,"\r\nrecebido ok\r\n");
					
				}
			}
#endif
			if(++timeout > 10000)
			{
				timeout = 0;
				break;
			}
		}	
		
	//m590_print("AT+CLOSECLIENT\r\n");
	m590_print("AT+CLOSELISTEN\r\n");
	
	m590_release();		
	return M590_OK;
}


