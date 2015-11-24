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
 * gc864_modem.c
 *
 *  Created on: Aug 7, 2015
 *      Author: UFSM
 */

#include "AppConfig.h"
#include "BRTOS.h"
#include "gc864_modem.h"
#include "printf_lib.h"
#include "utils.h"
#include "terminal.h"
#include "terminal_commands.h"
#include "string.h"

#include "at_commands.h"

#include "simon-api.h"

#ifdef _WIN32
#include <stdio.h>
#endif


static state_t modem_state = SETUP;
static char ip[16];
static char *hostname = NULL;
static INT8U modem_RxBuffer[32];
static INT8U modem_TxBuffer[32];

#define DEBUG_PRINT 1

#if DEBUG_PRINT
#define PRINT_P(...)      printf_terminal_P(__VA_ARGS__);
#define PRINT(...) 		  printf_terminal(__VA_ARGS__);
#define PRINT_BUF(...)    printf_terminal(__VA_ARGS__);
#define PRINT_REPLY(...)  printf_terminal(__VA_ARGS__);
#else
#define PRINT_P(...)      
#define PRINT(...)
#define PRINT_BUF(...)
#define PRINT_REPLY(...)  
#endif

#define UNUSED(x)   (void)x;

#define DEBUG_PUTCHAR	0

#if DEBUG_PUTCHAR
#define DPUTCHAR(x)		putchar_terminal(x);
#else
#define DPUTCHAR(x)		
#endif

#define CONST const

/* return modem reply */
uint8_t modem_getchar(void)
{
	uint8_t caracter;
	if(OSQueuePend(MODEM_QUEUE, &caracter, MODEM_UART_TIMEOUT) == TIMEOUT)
	{
		return (uint8_t) (-1);
	}
	return (uint8_t)caracter;
}

static INT8U modem_get_reply(INT8U *buf, INT16U max_len)
{
	uint8_t c;
	uint8_t len = 0;
	memset(buf,0x00,max_len); // clear buffer
	while((c=modem_getchar()) != (uint8_t)-1)
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

static void wait_modem_get_reply(uint16_t time)
{
	DelayTask(time);
	modem_get_reply(modem_RxBuffer,(INT16U)sizeof(modem_RxBuffer)-1);
}

static void modem_get_reply_print(void)
{
	wait_modem_get_reply(100);
	PRINT_BUF(modem_RxBuffer);
}

#define MODEM_GET_REPLY(b)		modem_get_reply((b), sizeof(b)-1);
#define MODEM_GET_REPLY_PRINT()	modem_get_reply_print();

INT8U is_modem_ok(void)
{
	INT8U ok = FALSE;
	modem_acquire();
	modem_printP(modem_init_cmd[AT]);
	DelayTask(50);
	MODEM_GET_REPLY(modem_RxBuffer);
	if(strstr(modem_RxBuffer, "OK"))
	{
		ok = TRUE;
	}
	modem_release();
	return ok;
}

uint8_t is_modem_ok_retry(uint8_t retries)
{
	while(is_modem_ok() == FALSE)
	{
		if(--retries == 0)
		{
			return FALSE;
		}
		DelayTask(100);
	}
	return TRUE;
}

uint8_t gc864_modem_init(void)
{
	
	PRINT_P(PSTR("Modem Init \r\n"));
	
	if(modem_state == SETUP)
	{
		/* init MODEM_UART */
		uart_init(MODEM_UART,BAUD(MODEM_BAUD),MODEM_UART_BUFSIZE,MODEM_MUTEX,MODEM_MUTEX_PRIO);
	
		/* setup */
		modem_acquire();
			modem_printP(modem_init_cmd[CREG]);
			MODEM_GET_REPLY_PRINT();
		modem_release();
	}

	if(!is_modem_ok_retry(2))
	{
		return FALSE;
	}

	modem_acquire();

	modem_printP(modem_init_cmd[CGDCONT]);
	MODEM_GET_REPLY_PRINT();

	modem_printP(modem_init_cmd[GPRS1]);
	MODEM_GET_REPLY_PRINT();

	modem_release();

	modem_state = INIT;

	return TRUE;
}
	
uint8_t gc864_modem_set_hostname(char *host)
{
	hostname = host;
	return TRUE;
}

char* gc864_modem_get_hostname(void)
{
	return hostname;	
}

uint8_t gc864_modem_host_ip(void)
{
	if(hostname == NULL)
	{
		return FALSE;
	}
	return TRUE;	
}

char* gc864_modem_get_ip(void)
{
	return (char*)ip;
}

uint8_t gc864_modem_set_ip(char* _ip)
{
	if(_ip == NULL)
	{
		return FALSE;
	}
	strcpy(ip,_ip);	
	return TRUE;
}

uint8_t gc864_modem_send(uint8_t * dados, uint16_t tam)
{
	
	if(dados == NULL) return FALSE;	
	*(dados+tam) = '\0'; // null terminate
	ip[15] ='\0';

	PRINT_P(PSTR("Modem Send: \r\n"));
	PRINT(dados);
	
	if(hostname == NULL) return FALSE;

    SNPRINTF_P(modem_TxBuffer,sizeof(modem_TxBuffer)-1,PSTR("AT#SKTD=0,80,%s,0,0\r\n"), hostname);
	PRINT(modem_TxBuffer);
    modem_printR(modem_TxBuffer);

	wait_modem_get_reply(100); // wait 100ms;
	PRINT_BUF(modem_RxBuffer);

	if(strstr((char *)modem_RxBuffer,"CONNECT"))
	{
		memcpy(modem_TxBuffer,dados,SIZEARRAY(modem_TxBuffer));	
		modem_printR(modem_TxBuffer);		
		wait_modem_get_reply(1000);
		PRINT_BUF(modem_RxBuffer);
		return TRUE;
	}
	return FALSE;
}


uint8_t gc864_modem_receive(uint8_t* buff, uint16_t* len)
{

	uint8_t ret = FALSE;
	uint16_t size =(uint16_t) MIN(*len,SIZEARRAY(modem_RxBuffer));
	
	*len = 0;

	if(size)
	{				
		    if(modem_RxBuffer[0] !='\0')
		    {		
		    	ret = TRUE;
				memcpy(buff,modem_RxBuffer,size);
				if(size < SIZEARRAY(modem_RxBuffer))
				{
					memcpy(modem_RxBuffer,&modem_RxBuffer[size],SIZEARRAY(modem_RxBuffer)-size);				
				}
			
				* len = size;
		    }	    
			
	}
	
	return (uint8_t)ret;
}


uint8_t gc864_modem_check_connection(void)
{
	return TRUE;
}

const modem_driver_t gc864_modem_driver  =
{
		gc864_modem_init,
		gc864_modem_receive,
		gc864_modem_send,
		gc864_modem_set_hostname,
		gc864_modem_set_ip,
		gc864_modem_check_connection
};



/* at commands */

modem_ret_t at_modem_init(void)
{	
	uint8_t res;
	res = gc864_modem_init();
	return (res == TRUE ? MODEM_OK:MODEM_ERR);
}
modem_ret_t at_modem_open(INT8U host, INT8U* dados)
{
	uint8_t res;
	if(host)
	{	
		res = gc864_modem_set_hostname(dados);
		PRINT("Host: ");
		PRINT(dados);
	}else
	{
		res = gc864_modem_set_ip(dados);
		PRINT("IP: ");
		PRINT(dados);
	}
	
	return (res == TRUE ? MODEM_OK:MODEM_ERR);
}
modem_ret_t at_modem_send(INT8U* dados)
{
	strcpy(modem_TxBuffer,dados);
	if(gc864_modem_send(modem_TxBuffer, sizeof(modem_TxBuffer)-1) == FALSE)
	{
		return MODEM_ERR;
	}
	return MODEM_OK;
}
modem_ret_t at_modem_receive(CHAR8* buff, INT8U len)
{
	uint16_t size = len;
	if(buff == NULL)	return MODEM_ERR;
	
	/* try to receive */
	if((size = gc864_modem_receive(buff,&size)) > 0)
	{
		*(buff+(size)) = '\0'; // null terminate
		PRINT_BUF(buff);
	}
	
	PRINT("\r\n");	
	
	return MODEM_OK;
	
}
modem_ret_t at_modem_close(void)
{
	PRINT("Close \r\n");
	
	if(modem_state != CLOSE)
	{
		modem_state = CLOSE;
	}
	
	return MODEM_OK;
	
}

modem_ret_t at_modem_server(void);
modem_ret_t at_modem_dns(char* param);
modem_ret_t at_modem_time(void);



