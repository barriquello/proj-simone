/*
 * m590_at.h
 *
 *  Created on: Aug 7, 2015
 *      Author: Gisele
 */

#ifndef M590_AT_H_
#define M590_AT_H_

#include "OS_types.h"
#include "UART.h"

// configuration 
#define M590_BAUD 			9600
#define M590_UART 			1
#define M590_TCP_SERVER_NAME "emon-gpsnetcms.rhcloud.com"
#define M590_TCP_SERVER_IP 	"54.160.189.224"
#define M590_TCP_PORT		80
#define M590_TCP_LOCAL_PORT	10201
#define M590_TCP_CTX_NUM	0
#define M590_TCP_CTX_SIZE	2048
#define API_KEY 			"apikey=90a004390f3530d0ba10199ac2b1ac3d"

#define M590_APN		 "tim.br"
#define M590_PWD		 "tim"

#define M590_UART_BUFSIZE	256
#define M590_UART_TIMEOUT	10

/* define esp uart functions*/
#if M590_UART == 1 
	#if ENABLE_UART1 == FALSE
		#error "UART 1 is disabled"
	#endif
	#define	M590_UART_PINS 		UART1_PTD6_PTD7
	#define M590_UART_MUTEX		UART1_MUTEX
	#define m590_print(x)		printSer(USE_UART1,x);
	#define m590_putchar(x)		putcharSer(USE_UART1,x)
	extern BRTOS_Queue 			*Serial1;
	#define M590_QUEUE			Serial1
	#if M590_UART_MUTEX
		#define M590_MUTEX		TRUE
		#define M590_MUTEX_PRIO	UART1_MUTEX_PRIO
		#define m590_acquire()	uart1_acquire()
		#define m590_release()	uart1_release()		
	#else
		#define M590_MUTEX			FALSE
		#define M590_MUTEX_PRIO		0
		#define m590_acquire()		
		#define m590_release()	
	#endif
#elif M590_UART == 2
	#if ENABLE_UART2 == FALSE
		#error "UART 2 is disabled"
	#endif	
	#define M590_UART_MUTEX		UART2_MUTEX
	#define m590_print(x)		printSer(USE_UART2,x)
	#define m590_putchar(x)		putcharSer(USE_UART2,x)
	extern BRTOS_Queue 			*Serial2;
	#define M590_QUEUE			Serial2
	#if M590_UART_MUTEX
		#define M590_MUTEX		TRUE
		#define M590_MUTEX_PRIO	UART2_MUTEX_PRIO
		#define m590_acquire()	uart2_acquire()
		#define m590_release()	uart2_release()
	#else
		#define M590_MUTEX			FALSE
		#define M590_MUTEX_PRIO		0
		#define m590_acquire()		
		#define m590_release()	
	#endif
#else
	#error "UART port is not specified"
#endif


typedef enum 
{
	M590_INIT,
	M590_OPEN,
	M590_CLOSE
}m590_state_t;

typedef enum 
{
	M590_OK,
	M590_STATE_ERR,
	M590_APCONN_ERR,
	M590_TCPCONN_ERR
}m590_ret_t;

/* example
 * AT+CREG?	// Verifica rede
 * AT+XISP=0 // seleciona stack tcp/ip interna
 * AT+XGAUTH=1,1,"tim","tim"
 * AT+CGDCONT=1,"IP","tim.br"
 * AT+XIIC=1
 * AT+XIIC?
 * AT+DNSSERVER?
 * AT+TCPSETUP=0,54.160.189.224,80
 * AT+IPSTATUS=0
 * AT+TCPSEND=1,50
 * > GET /input/post.json?json={power:150}&API_KEY HTTP/1.1\r\nHost: emon-gpsnetcms.rhcloud.com\r\n\r\n\r
 * AT+TCPCLOSE=0 
 *  
 */

m590_ret_t at_m590_init(void);
m590_ret_t at_m590_open(void);
m590_ret_t at_m590_send(INT8U num, CHAR8* field, CHAR8* val);
m590_ret_t at_m590_receive(CHAR8* buff, INT8U* len);
m590_ret_t at_m590_close(void);
m590_ret_t at_m590_server(void);
CHAR8 at_m590_getchar(void);


INT8U m590_set_hostname(CHAR8 *host);
INT8U m590_set_ip(void);


#endif /* M590_AT_H_ */
