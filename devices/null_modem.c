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
 * null_modem_at.c
 *
 *  Created on: Aug 7, 2015
 *      Author: UFSM
 */

#include "AppConfig.h"
#include "BRTOS.h"
#include "null_modem.h"
#include "printf_lib.h"
#include "utils.h"
#include "terminal.h"
#include "terminal_commands.h"
#include "string.h"

#include "simon-api.h"

#ifdef _WIN32
#include <stdio.h>
#endif


static state_t null_modem_state = SETUP;
static char ip[16];
static char *hostname = NULL;
static INT8U null_modem_RxBuffer[32];
static INT8U null_modem_TxBuffer[32];

#define DEBUG_PRINT 0

#if DEBUG_PRINT
#define PRINT_P(...)      printf_terminal_P(__VA_ARGS__);
#define PRINT(...) 		  printf_terminal(__VA_ARGS__);
#define PRINT_BUF(...)    //printf_terminal(__VA_ARGS__);
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
	

uint8_t null_modem_init(void)
{
	
	PRINT_P(PSTR("Modem Init \r\n"));
	null_modem_state = INIT;
	
	return TRUE;
	
}
	
uint8_t null_modem_set_hostname(char *host)
{
	hostname = host;
	return MODEM_OK;
}

char* null_modem_get_hostname(void)
{
	return hostname;	
}

uint8_t null_modem_host_ip(void)
{
	if(hostname == NULL)
	{
		return MODEM_ERR;
	}
	return MODEM_OK;	
}

char* null_modem_get_ip(void)
{
	return (char*)ip;
}

uint8_t null_modem_set_ip(char* _ip)
{
	if(hostname == NULL || _ip == NULL)
	{
		return MODEM_ERR;
	}
	strcpy(ip,_ip);	
	return MODEM_OK;
}

uint8_t null_modem_send(uint8_t * dados, uint16_t tam)
{
	

	if(dados == NULL) return MODEM_ERR;	
	*(dados+tam) = '\0'; // null terminate
	ip[15] ='\0';

	PRINT_P(PSTR("Modem Send: \r\n"));
	PRINT(dados);
	memcpy(null_modem_TxBuffer,dados,SIZEARRAY(null_modem_TxBuffer));				
	if(null_modem_state == INIT)
	{				
		return TRUE;		
	}else
	{
		return FALSE;
	}	
	
}


uint8_t null_modem_receive(uint8_t* buff, uint16_t* len)
{

	uint8_t ret = MODEM_ERR;
	uint16_t size =(uint16_t) MIN(*len,SIZEARRAY(null_modem_RxBuffer));
	
	*len = 0;

	if(size)
	{				
		    if(null_modem_RxBuffer[0] !='\0')
		    {		
		    	ret = MODEM_OK;
				memcpy(buff,null_modem_RxBuffer,size);
				if(size < SIZEARRAY(null_modem_RxBuffer))
				{
					memcpy(null_modem_RxBuffer,&null_modem_RxBuffer[size],SIZEARRAY(null_modem_RxBuffer)-size);				
				}
			
				* len = size;
		    }	    
			
	}
	
	return (uint8_t)ret;
}


uint8_t null_modem_check_connection(void)
{
	return TRUE;
}

const modem_driver_t null_modem_driver  =
{
		null_modem_init,
		null_modem_receive,
		null_modem_send,
		null_modem_set_hostname,
		null_modem_set_ip,
		null_modem_check_connection
};





