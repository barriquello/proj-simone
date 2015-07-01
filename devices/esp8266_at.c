/*
 * esp8266_at.c
 *
 *  Created on: Mar 17, 2015
 *      Author: Carlos H. Barriquello
 */


#include "esp8266_at.h"
#include "BRTOS.h"
#include "utils.h"
#include "usb_terminal_commands.h"

static esp_state_t esp_state = INIT;

CHAR8 at_esp_getchar(void)
{
	INT8U caracter;
	if(OSQueuePend(ESP_QUEUE, &caracter, ESP_UART_TIMEOUT) == TIMEOUT)
	{
		return (CHAR8) (-1);
	}	
	return (CHAR8)caracter;
}

static void at_esp_print_reply(void)
{
	INT8U c;
	DelayTask(1000);
	while((c=at_esp_getchar()) != (CHAR8)-1){
		putchar_usb(c);
	}
}

esp_ret_t at_esp_init(void)
{
	
	if(esp_state != INIT)
	{
		return ESP_STATE_ERR;
	}
	
	/* init ESP_UART */
	uart_init(ESP_UART,ESP_BAUD,ESP_UART_BUFSIZE,ESP_UART_PINS,ESP_MUTEX,ESP_MUTEX_PRIO);
	
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

#define SEND_STRING "AT+CIPSENDI=0,\"GET /input/post.json?json={p:3}&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1\\r\\nHost: emon-gpsnetcms.rhcloud.com\\r\\n\\r\\n\\r\\n\""

#define SEND_STRING1 "AT+CIPSENDI=0,\"GET /input/post.json?json={"
//#define SEND_STRING2 ("}&" API_KEY " HTTP/1.1\r\nHost: " ESP_TCP_SERVER_NAME "\r\n\r\n\r\n")
#define SEND_STRING2 "}&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1\\r\\nHost: emon-gpsnetcms.rhcloud.com\\r\\n\\r\\n\\r\\n\""

esp_ret_t at_esp_send(INT8U num, CHAR8* field, CHAR8* val)
{
	INT8U idx;
	
	if(esp_state != OPEN)
	{
		return ESP_STATE_ERR;
	}
	
	/* sending */	
	esp_acquire();
#if 0	
	esp_print(SEND_STRING);
	esp_print("\r\n");
	
#else	
	esp_print(SEND_STRING1);
	for (idx = 0; idx<num; idx++)
	{
		//esp_print(field[idx]);
		esp_print(field);
		esp_putchar(':');
		//esp_print(val[idx]);		
		esp_print(val);
	}
	esp_print(SEND_STRING2);
#endif	
	
	esp_print("\r\n");
	at_esp_print_reply();
	printSer(USE_USB,"\r\n");
	
	esp_release();	
	
	return ESP_OK;
}

esp_ret_t at_esp_receive(CHAR8* buff, INT8U* len)
{
	//INT8U max_len = *len;
	
	if(esp_state != OPEN)
	{
		return ESP_STATE_ERR;
	}
	
	esp_acquire();	
	esp_print("AT+CIPRD=0\r\n");	
	at_esp_print_reply();
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


