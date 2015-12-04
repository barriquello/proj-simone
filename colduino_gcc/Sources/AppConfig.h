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
///////////////////////////////////////////////////////////////
/////                                                     /////
/////                   User App Defines                  /////
/////                                                     /////
/////             !User App configuration defines!        /////
/////                                                     /////
///////////////////////////////////////////////////////////////
#include "user_config.h"


#define SD_PRESENTE         1
#define RTC_PRESENTE  		0
#define MODEM_PRESENTE  	1
#define PM200_PRESENTE   	0
#define TS_PRESENTE   		0
#define NULL_PRESENTE   	1

#if RTC_PRESENTE
#include "Timer_RTC_DS1307.h"
#endif

#if SD_PRESENTE
#include "SD_API.h"
#define SDCARD_MUTEX_PRIORITY 	29
#endif

#define USB_DEVICE_ENABLED	  1
#define COMPARATOR_ENABLED	  0

#if USB_DEVICE_ENABLED == 1
#define ENABLE_USB 			  1
#endif

#define TESTE_MODBUS    	  0
#define TESTE_MODBUS_SLAVE    0
#define TESTE_MODBUS_MASTER   0
#define TESTE_RS485			  0

#define DATALOGGER_DELAY_TIME (3000)

//#define WIN32    		0
#define COLDUINO 	1
//#define ARDUINO 	2

#define PLATAFORMA  COLDUINO

#ifndef CONST
#define CONST const
#endif

#if __GNUC__
#define COLDUINO_GCC 	1
#endif

#if COLDUINO
#define PGM_P				const char *
#define PGM_READ_WORD(x)    (x)
#define PGM_READ_BYTE(x)    (x)
#define PROGMEM
#define strcmp_P		strcmp
#elif ARDUINO
#define PGM_READ_BYTE(x)    pgm_read_byte(&(x))
#define PGM_READ_WORD(x)    pgm_read_word(&(x))
#endif

#ifndef PROGMEM
#define PROGMEM
#endif

#ifndef PGM_P

#endif

#if COLDUINO
#define MODEM_UART			2
#define UART0_MUTEX 		1
#define UART1_MUTEX 		0
#define UART2_MUTEX 		0
#define UART0_MUTEX_PRIO 	9
#define UART1_MUTEX_PRIO 	10
#define UART2_MUTEX_PRIO 	11
#elif ARDUINO
#define MODEM_UART			1
#define UART0_MUTEX 		1
#define UART1_MUTEX 		0
#define UART2_MUTEX 		0
#define UART0_MUTEX_PRIO 	4
#define UART1_MUTEX_PRIO 	5
#define UART2_MUTEX_PRIO 	6
#endif

#if COLDUINO
#define TASK_STACKSIZE_SYSTEM_TIME		(256+64)
#define TASK_STACKSIZE_MONITORS			(1024*2+512)
#define TASK_STACKSIZE_TERMINAL			(1024+256)

#define TASK_PRIORITY_SYSTEM_TIME		15
#define TASK_PRIORITY_MONITORS			8
#define TASK_PRIORITY_TERMINAL			5

#elif ARDUINO
#define TASK_STACKSIZE_SYSTEM_TIME		(64)
#define TASK_STACKSIZE_MONITORS			(1024)
#define TASK_STACKSIZE_TERMINAL			(512)

#define TASK_PRIORITY_SYSTEM_TIME		7
#define TASK_PRIORITY_MONITORS			3
#define TASK_PRIORITY_TERMINAL			2
#endif






