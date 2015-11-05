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
 * null_modem_at.h
 *
 *  Created on: Aug 7, 2015
 *      Author: UFSM
 */

#ifndef NULL_MODEM_H_
#define NULL_MODEM_H_

#include "OS_types.h"
#include "UART.h"
#include "terminal_io.h"
#include "stdint.h"
#include "AppConfig.h"

// configuration 
#define NULL_MODEM_UART_BUFSIZE		32
#define NULL_MODEM_UART_TIMEOUT		10
#define NULL_MODEM_MUTEX			FALSE
#define NULL_MODEM_MUTEX_PRIO		0
#define null_modem_acquire()
#define null_modem_release()
		
typedef enum
{
	SETUP,
	INIT,
	OPEN
} state_t;


typedef enum 
{
	MODEM_OK,
	MODEM_ERR,
	MODEM_STATE_ERR
}null_modem_ret_t;

null_modem_ret_t at_null_modem_init(void);
null_modem_ret_t at_null_modem_open(void);
null_modem_ret_t at_null_modem_send(INT8U* dados);
null_modem_ret_t at_null_modem_receive(CHAR8* buff, INT8U len);
null_modem_ret_t at_null_modem_close(void);
null_modem_ret_t at_null_modem_server(void);
null_modem_ret_t at_null_modem_dns(char* param);
null_modem_ret_t at_null_modem_time(void);


CHAR8 null_modem_getchar(void);
uint8_t null_modem_init(void);
uint8_t null_modem_open(void);
uint8_t null_modem_close(void);

uint8_t null_modem_get_time(void);
uint8_t null_modem_receive(uint8_t* buff, uint16_t* len);
uint8_t null_modem_send(uint8_t * dados, uint16_t tam);
uint8_t null_modem_set_ip(char* _ip);
char* null_modem_get_ip(void);
uint8_t null_modem_set_hostname(char *host);
char* null_modem_get_hostname(void);
uint8_t null_modem_host_ip(void);
uint8_t null_modem_check_connection(void);


#endif /* NULL_MODEM_AT_H_ */