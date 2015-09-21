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
 * esp8266_at.c
 *
 *  Created on: Mar 17, 2015
 *      Author: Carlos H. Barriquello
 */


#include "esp8266_at.h"
#include "BRTOS.h"
#include "terminal_io.h"
#include "terminal_commands.h"
#include "virtual_com.h"
#include "utils.h"

static esp_state_t esp_state = INIT;
static char ip[16];
static char* hostname = NULL;

static void at_esp_print_reply(void)
{
	INT8U c;
	DelayTask(1000);
	while((c=at_esp_getchar()) != (CHAR8)-1){
		putcharSer(USE_USB,c);
	}
}

static INT8U at_esp_get_reply(INT8U *buf, INT8U max_len)
{
	INT8U c;
	INT8U len = 0;
	DelayTask(1000);
	while((c=at_esp_getchar()) != (CHAR8)-1){
		*buf = c;
		buf++;
		len++;
		max_len--;
		if(max_len == 0) return len;
	}
	return len;
}

INT8U esp_set_hostname(CHAR8 *host)
{
	hostname = host;
	return OK;
}

INT8U esp_get_ip(void)
{
	if(hostname == NULL)
	{
		return !OK;
	}
	
	esp_acquire();	
	esp_print("AT+CIPRESOLVE=\"");
	esp_print(hostname);
	esp_print("\"\r\n");
	at_esp_get_reply(ip,16);
	//at_esp_print_reply();
	esp_release();		
	
	
}

CHAR8 at_esp_getchar(void)
{
	INT8U caracter;
	if(OSQueuePend(ESP_QUEUE, &caracter, ESP_UART_TIMEOUT) == TIMEOUT)
	{
		return (CHAR8) (-1);
	}	
	return (CHAR8)caracter;
}

esp_ret_t at_esp_init(void)
{
	
	if(esp_state != INIT)
	{
		return ESP_STATE_ERR;
	}
	
	/* init ESP_UART */
	uart_init(ESP_UART,ESP_BAUD,ESP_UART_BUFSIZE,ESP_MUTEX,ESP_MUTEX_PRIO);
	
	/* check init */
	esp_acquire();	
	esp_print("AT\r\n");	
	at_esp_print_reply();
	esp_release();
	printSer(USE_USB,"\r\n");
	
	esp_acquire();	
	esp_print("AT+CWMODE=3\r\n");
	at_esp_print_reply();
	esp_release();	
	printSer(USE_USB,"\r\n");	
	
	esp_acquire();
	esp_print(("AT+CWJAP=\"" ESP_AP "\",\"" ESP_PWD "\"\r\n"));
	at_esp_print_reply();
	esp_release();	
	printSer(USE_USB,"\r\n");
	
	esp_state = CLOSE;
	return ESP_OK;
	
}
esp_ret_t at_esp_open(void)
{
	if(esp_state != CLOSE)
	{
		return ESP_STATE_ERR;
	}
	
	esp_acquire();	
	esp_print("AT+CIPSTA?\r\n");
	at_esp_print_reply();
	esp_release();		
	printSer(USE_USB,"\r\n");
	
	esp_acquire();	
	esp_print("AT+CIPRESOLVE=\"emon-gpsnetcms.rhcloud.com\"\r\n");
	at_esp_print_reply();
	esp_release();		
	printSer(USE_USB,"\r\n");
	
	esp_acquire();	
	esp_print("AT+CIPCREATE=\"TCP\",10201,2048\r\n");	
	at_esp_getchar();
	esp_release();		
	printSer(USE_USB,"\r\n");
	
	
	esp_acquire();	
	esp_print("AT+CIPCONNECT=0,\"54.160.189.224\",80\r\n");	
	at_esp_print_reply();
	esp_release();			
	printSer(USE_USB,"\r\n");
	
	esp_state = OPEN;
	
	return ESP_OK;
}

esp_ret_t at_esp_send(INT8U* dados)
{
		
	if(esp_state != OPEN)
	{
		return ESP_STATE_ERR;
	}
	
	/* sending */	
	esp_acquire();
	
#if 0	
	#define SEND_STRING "AT+CIPSENDI=0,\"GET /input/post.json?json={p:3}&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1\\r\\nHost: emon-gpsnetcms.rhcloud.com\\r\\n\\r\\n\\r\\n\""
	esp_print(SEND_STRING);
	esp_print("\r\n");	
#else	
	if(dados != NULL)
	{
		esp_print(dados);	
	}
#endif	
	
	esp_print("\r\n");
	at_esp_print_reply();
	printSer(USE_USB,"\r\n");
	
	esp_release();	
	
	return ESP_OK;
}

esp_ret_t at_esp_receive(CHAR8* buff, INT8U* len)
{

	if(esp_state != OPEN)
	{
		return ESP_STATE_ERR;
	}
	
	esp_acquire();	
	esp_print("AT+CIPRD=0\r\n");	
	*len = at_esp_get_reply(buff,*len);
	//at_esp_print_reply();
	esp_release();		
	printSer(USE_USB,"\r\n");
		
	/* try to receive */	
	return ESP_OK;
}

esp_ret_t at_esp_close(void)
{
	if(esp_state != OPEN)
	{
		return ESP_STATE_ERR;
	}
	
	esp_acquire();	
		esp_print("AT+CIPCLOSE=0\r\n");	
		at_esp_print_reply();
		esp_print("AT+CIPCLOSE=1\r\n");	
		at_esp_print_reply();
	esp_release();		
	printSer(USE_USB,"\r\n");
		
	esp_state = CLOSE;
	return ESP_OK;
}


