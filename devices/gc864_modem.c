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
#include "modem.h"

#ifdef _WIN32
#include <stdio.h>
#endif


static state_t modem_state = SETUP;
static char ip[16];
static char *hostname = NULL;
static char modem_BufferTxRx[64];

extern uint8_t mon_verbosity;

#define DEBUG_PRINT 1

#if DEBUG_PRINT
#define PRINT_P(...)      printf_terminal_P(__VA_ARGS__);
#define PRINT(s) 		  printf_terminal((char*)(s));
#define PRINT_BUF(s)      printf_terminal((char*)(s));
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

#define CONST 		const
#define MAX_RETRIES  (3)

uint8_t Check_Connect_PPP(uint8_t retries);

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

static INT8U modem_get_reply(char *buf, uint16_t max_len)
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
	modem_get_reply(modem_BufferTxRx,(INT16U)sizeof(modem_BufferTxRx)-1);
}

static void modem_get_reply_print(void)
{
	wait_modem_get_reply(100);
	if(mon_verbosity > 1) PRINT_BUF(modem_BufferTxRx);
}

#define MODEM_GET_REPLY(b)		modem_get_reply((b), sizeof(b)-1);
#define MODEM_GET_REPLY_PRINT()	modem_get_reply_print();

INT8U is_modem_ok(void)
{
	INT8U ok = FALSE;
	modem_acquire();
	modem_printP(modem_init_cmd[AT]);
	DelayTask(100);
	MODEM_GET_REPLY(modem_BufferTxRx);
	if(strstr(modem_BufferTxRx, "OK"))
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
		#if COLDUINO
		#define BAUD(x)			(x)
		#endif
		uart_init(MODEM_UART,BAUD(MODEM_BAUD),MODEM_UART_BUFSIZE,MODEM_MUTEX,MODEM_MUTEX_PRIO);
	}

	if(is_modem_ok_retry(MAX_RETRIES) == FALSE)
	{
		return MODEM_ERR;
	}

    PRINT_P(PSTR("Modem setup\r\n"));
	
	modem_acquire();
	
    /* setup */
	modem_printP(modem_init_cmd[CREG]);
	MODEM_GET_REPLY_PRINT();
	
	modem_printP(modem_init_cmd[CGDCONT]);
	MODEM_GET_REPLY_PRINT();

	modem_printP(modem_init_cmd[GPRS]);
	MODEM_GET_REPLY_PRINT();

	modem_release();

	modem_state = INIT;

	return MODEM_OK;
}
	
uint8_t gc864_modem_set_hostname(char *host)
{
	hostname = host;
	return MODEM_OK;
}

char* gc864_modem_get_hostname(void)
{
	return hostname;	
}

uint8_t gc864_modem_host_ip(void)
{
	if(hostname == NULL)
	{
		return MODEM_ERR;
	}
	return MODEM_OK;
}

char* gc864_modem_get_ip(void)
{
	return (char*)ip;
}

uint8_t gc864_modem_set_ip(char* _ip)
{
	if(_ip == NULL)
	{
		return MODEM_ERR;
	}
	strcpy(ip,_ip);	
	return MODEM_OK;
}

uint8_t gc864_modem_send(char * dados, uint16_t tam)
{
	uint16_t timeout = 0;
	uint8_t  retries = 0;
	
	if(dados == NULL) goto exit;
	if(hostname == NULL) goto exit;

	*(dados+tam-1) = '\0'; // null terminate

	if(mon_verbosity > 2) PRINT_P(PSTR("Modem Send: \r\n"));

	/* Flush queue first */
	OSCleanQueue(MODEM_QUEUE);

	/* check modem setup */
	if(modem_state == SETUP)
	{
		if(gc864_modem_init() == MODEM_ERR)
		{
			if(mon_verbosity > 2) PRINT_P(PSTR("Modem Init fail \r\n"));
			goto exit;
		}
	}

	/* check modem init */
	if(modem_state == INIT)
	{
		if(Check_Connect_PPP(MAX_RETRIES) == FALSE)
		{
			if(mon_verbosity > 2) PRINT_P(PSTR("Modem GPRS connection fail \r\n"));
			goto exit;
		}
	}

	try_again:

    SNPRINTF_P(modem_BufferTxRx,sizeof(modem_BufferTxRx)-1,PSTR("AT#SKTD=0,80,%s,0,0\r\n"), hostname);

    if(mon_verbosity > 3) PRINT(modem_BufferTxRx);

    modem_printR(modem_BufferTxRx);

    timeout = 0;
    retries = 0;
    do{
    	wait_modem_get_reply(10); // wait 10ms;
    	if(mon_verbosity > 3) PRINT_BUF(modem_BufferTxRx);
    	if(strstr((char *)modem_BufferTxRx,"CONNECT"))
    	{
    		goto send;
    	}
    	if(strstr((char *)modem_BufferTxRx,"NO CARRIER"))
		{
    		if(++retries < MAX_RETRIES)
    		{
    			goto try_again;
    		}
    		break;
		}
    }while(++timeout < 200);
    if(mon_verbosity > 2) PRINT_P(PSTR("\r\nConnect fail\r\n"));

    goto exit;

    send:
		if(mon_verbosity > 3) PRINT(dados);
		modem_printR(dados);

		timeout = 0;
		do
		{
			wait_modem_get_reply(10);
			if(mon_verbosity > 3) PRINT_BUF(modem_BufferTxRx);
			if(strstr((char *)modem_BufferTxRx,"OK"))
			{
				if(mon_verbosity > 2) PRINT("send ok\r\n");
				return MODEM_OK;
			}
		}while(++timeout < 200); /* espera ate 2 segundos */

		if(mon_verbosity > 2) PRINT_P(PSTR("\r\nSend fail\r\n"));

	exit:
	return MODEM_ERR;


}


uint8_t gc864_modem_receive(char* buff, uint16_t* len)
{

	uint8_t ret = MODEM_ERR;
	uint16_t size =(uint16_t) MIN(*len,SIZEARRAY(modem_BufferTxRx));
	
	*len = 0;

	if(size)
	{				
		    modem_acquire();
		    if(modem_BufferTxRx[0] !='\0')
		    {		
		    	ret = MODEM_OK;
				memcpy(buff,modem_BufferTxRx,size);
				if(size < SIZEARRAY(modem_BufferTxRx))
				{
					memcpy(modem_BufferTxRx,&modem_BufferTxRx[size],SIZEARRAY(modem_BufferTxRx)-size);
				}
				modem_get_reply(&modem_BufferTxRx[SIZEARRAY(modem_BufferTxRx)-size],size);
				* len = size;
		    }    
			modem_release();			
	}
	
	return (uint8_t)ret;
}


uint8_t gc864_modem_check_connection(void)
{
	if(!is_modem_ok_retry(MAX_RETRIES))
	{
		return MODEM_ERR;
	}
	return MODEM_OK;
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


uint8_t Check_Connect_PPP(uint8_t retries)
{

	OSCleanQueue(MODEM_QUEUE);

	do
	{
		/* check GPRS connection */
		modem_printP(modem_init_cmd[GPRS]);
		wait_modem_get_reply(200); // wait 200ms;
		if(mon_verbosity > 2) PRINT_BUF(modem_BufferTxRx);

		if(strstr((char *)modem_BufferTxRx,"#GPRS: 1") != NULL)
		{
			/* connected */
			return TRUE;
		}
		else if(strstr((char *)modem_BufferTxRx,"#GPRS: 0") != NULL)
		{
			/* not connected */
			if(--retries == 0) return FALSE;

			modem_printP(modem_init_cmd[GPRS1]);
			wait_modem_get_reply(500); // wait 500ms;
			if(mon_verbosity > 2)  PRINT_BUF(modem_BufferTxRx);
		}else
		{
			/* no reply, buffer may be full */
			if(--retries == 0) return FALSE;
			OSCleanQueue(MODEM_QUEUE);
		}
	}while(TRUE);

	return FALSE;
}

/* at commands */

modem_ret_t at_modem_init(void)
{	

	return  gc864_modem_init();

}
modem_ret_t at_modem_open(INT8U host, char* dados)
{
	uint8_t res;

	if(host)
	{	
		res = gc864_modem_set_hostname(dados);
		if(mon_verbosity > 2)
		{
			PRINT("Host: ");
			PRINT(dados);
		}

	}else
	{
		res = gc864_modem_set_ip((char*)dados);
		if(mon_verbosity > 2)
		{
			PRINT("IP: ");
			PRINT(dados);
		}
	}

	res = Check_Connect_PPP(MAX_RETRIES);

	return (res == TRUE ? MODEM_OK:MODEM_ERR);
}
modem_ret_t at_modem_send(char* dados)
{
	return gc864_modem_send(dados, (uint16_t)strlen(dados));
}
modem_ret_t at_modem_receive(char* buff, uint16_t len)
{
	uint16_t size = len;
	if(buff == NULL)	return MODEM_ERR;
	
	/* try to receive */
	if(gc864_modem_receive(buff,&size) == MODEM_OK)
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

modem_ret_t at_modem_server(void)
{
	PRINT_P(PSTR("NOT IMPLEMENTED \r\n"));
	return MODEM_OK;
}
modem_ret_t at_modem_dns(char* param)
{
	PRINT_P(PSTR("NOT IMPLEMENTED \r\n"));
	return MODEM_OK;
}
modem_ret_t at_modem_time(void)
{
	PRINT_P(PSTR("NOT IMPLEMENTED \r\n"));
	return MODEM_OK;
}



