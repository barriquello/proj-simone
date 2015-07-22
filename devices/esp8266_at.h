/*
 * esp8266_at.h
 *
 *  Created on: Mar 17, 2015
 *      Author: Carlos H. Barriquello
 */

#ifndef ESP8266_AT_H_
#define ESP8266_AT_H_

#include "OS_types.h"
#include "UART.h"

// configuration 
#define ESP_BAUD 9600
#define ESP_UART 2
#define ESP_TCP_SERVER_NAME "emon-gpsnetcms.rhcloud.com"
#define ESP_TCP_SERVER_IP 	"54.160.189.224"
#define ESP_TCP_PORT		80
#define ESP_TCP_LOCAL_PORT	10201
#define ESP_TCP_CTX_NUM		0
#define ESP_TCP_CTX_SIZE	2048
#define API_KEY 			"apikey=90a004390f3530d0ba10199ac2b1ac3d"
//#define ESP_AP				"1209B"
//#define ESP_PWD				"eletronica"

#define ESP_AP				"GISELE_e_CARLOS"
#define ESP_PWD				"01122007"

#define ESP_UART_BUFSIZE	64
#define ESP_UART_TIMEOUT	2000

/* define esp uart functions*/
#if ESP_UART == 1 
	#if ENABLE_UART1 == FALSE
		#error "UART 1 is disabled"
	#endif
	#define	ESP_UART_PINS 		UART1_PTA1_PTA2
	#define ESP_UART_MUTEX		UART1_MUTEX
	#define esp_print(x)		printSer(USE_UART1,x);
	#define esp_putchar(x)		putcharSer(USE_UART1,x)
	extern BRTOS_Queue 			*Serial1;
	#define ESP_QUEUE			Serial1
	#if ESP_UART_MUTEX
		#define ESP_MUTEX		TRUE
		#define ESP_MUTEX_PRIO	UART1_MUTEX_PRIO
		#define esp_acquire()	uart1_acquire()
		#define esp_release()	uart1_release()		
	#else
		#define ESP_MUTEX			FALSE
		#define ESP_MUTEX_PRIO		0
		#define esp_acquire()		
		#define esp_release()	
	#endif
#elif ESP_UART == 2
	#if ENABLE_UART2 == FALSE
		#error "UART 2 is disabled"
	#endif	
	#define ESP_UART_MUTEX		UART2_MUTEX
	#define esp_print(x)		printSer(USE_UART2,x)
	#define esp_putchar(x)		putcharSer(USE_UART2,x)
	extern BRTOS_Queue 			*Serial2;
	#define ESP_QUEUE			Serial2
	#if ESP_UART_MUTEX
		#define ESP_MUTEX		TRUE
		#define ESP_MUTEX_PRIO	UART2_MUTEX_PRIO
		#define esp_acquire()	uart2_acquire()
		#define esp_release()	uart2_release()
	#else
		#define ESP_MUTEX			FALSE
		#define ESP_MUTEX_PRIO		0
		#define esp_acquire()		
		#define esp_release()	
	#endif
#else
	#error "UART port is not specified"
#endif


typedef enum 
{
	INIT,
	OPEN,
	CLOSE
}esp_state_t;

typedef enum 
{
	ESP_OK,
	ESP_STATE_ERR,
	ESP_APCONN_ERR,
	ESP_TCPCONN_ERR
}esp_ret_t;

/* example
 * AT+CWLAP
 * AT+CWJAP="1209B","eletronica"
 * AT+CIPSTA?
 * AT+CIPSTAMAC?
 * AT+CIPCREATE="TCP",10201,2048
 * AT+CIPCONNECT=0,"54.160.189.224",80
 * AT+CIPSENDI=0,"GET /input/post.json?json={power:150}&API_KEY HTTP/1.1\r\nHost: emon-gpsnetcms.rhcloud.com\r\n\r\n"
 * AT+CIPRD=0
 * AT+CIPCLOSE=0
 *  
 */

esp_ret_t at_esp_init(void);
esp_ret_t at_esp_open(void);
esp_ret_t at_esp_send(INT8U num, CHAR8* field, CHAR8* val);
esp_ret_t at_esp_receive(CHAR8* buff, INT8U* len);
esp_ret_t at_esp_close(void);
CHAR8 at_esp_getchar(void);


INT8U esp_set_hostname(CHAR8 *host);
INT8U esp_set_ip(void);


#endif /* ESP8266_AT_H_ */
