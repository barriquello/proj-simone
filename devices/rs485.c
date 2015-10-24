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
/**
 * \file rs485.c
 * \brief RS485 functions
 *
 * This file implements the rs485/uart driver.
 *
 **/

#include "AppConfig.h"
#include "hardware.h"
#include "uart.h"
#include "rs485.h"

#define RS485_BUFSIZE		(36) /* enough to read up to 2 regs of 16 bits each */
#define RS485_TX_STATE 		1
#define RS485_RX_STATE 		0

#if COLDUINO
	#if !__GNUC__
	#pragma warn_implicitconv off
	#define RS485_TXRX_PIN 		PTFD_PTFD2
	#define RS485_TXRX_PINDIR 	PTFDD_PTFDD2
	#define RS485_TXRX_ENABLE() (RS485_TXRX_PINDIR = 1)
	#define RS485_RX() 			RS485_TXRX_PIN = RS485_RX_STATE
	#define RS485_TX() 			RS485_TXRX_PIN = RS485_TX_STATE
	#else
	#include "utils.h"
	#define RS485_TXRX_PIN 		PTFD
	#define RS485_TXRX_PINDIR 	PTFDD
	#define RS485_TXRX_ENABLE() BITSET(RS485_TXRX_PINDIR,2)
	#define RS485_RX() 			BITCLEAR(RS485_TXRX_PIN,2)
	#define RS485_TX() 			BITSET(RS485_TXRX_PIN,2)
	#endif
#elif ARDUINO
/* arduino mega2560 - shield rs485 - pth3 */
#define RS485_TXRX_PORT_DATA	PORTH
#define RS485_TXRX_PORT_DIR		DDRH
#define RS485_TXRX_PIN			3
#define RS485_TXRX_ENABLE()		BITSET(RS485_TXRX_PORT_DIR,RS485_TXRX_PIN)
#define RS485_RX()				BITCLEAR(RS485_TXRX_PORT_DATA,RS485_TXRX_PIN)
#define RS485_TX()				BITSET(RS485_TXRX_PORT_DATA,RS485_TXRX_PIN)
#else
#define RS485_TXRX_PORT_DATA
#define RS485_TXRX_PORT_DIR
#define RS485_TXRX_PIN
#define RS485_TXRX_ENABLE()		
#define RS485_RX()		
#define RS485_TX()		

#endif

#if COLDUINO || ARDUINO
#if UART_RS485 == UART0
#define RS485_PUTCHAR(x) 	putchar_uart0(x)
#define RS485_PRINTF(x)		printf_uart0(x)
#define RS485_RX_ENABLE()	uart0_RxEnable();uart0_RxEnableISR();
#define RS485_RX_DISABLE()	uart0_RxDisable();uart0_RxDisableISR();
extern BRTOS_Queue 			*Serial0;
#define RS485_QUEUE 		Serial0
#elif UART_RS485 == UART1
#define RS485_PUTCHAR(x) 	putchar_uart1(x)
#define RS485_PRINTF(x)		printf_uart1(x)
#define RS485_RX_ENABLE()	uart1_RxEnable();uart1_RxEnableISR();
#define RS485_RX_DISABLE()	uart1_RxDisable();uart1_RxDisableISR();
extern BRTOS_Queue 			*Serial1;
#define RS485_QUEUE 		Serial1
#elif UART_RS485 == UART2
#define RS485_PUTCHAR(x) 	putchar_uart2(x)
#define RS485_PRINTF(x)		printf_uart2(x)
#define RS485_RX_ENABLE()	uart2_RxEnableISR()
#define RS485_RX_DISABLE()	uart2_RxDisableISR()
extern BRTOS_Queue 			*Serial2;
#define RS485_QUEUE 		Serial2
#endif


void rs485_init(INT16U baudrate, INT8U mutex, INT8U priority)
{
	
	RS485_RX();
	RS485_TXRX_ENABLE();
	
#if UART_RS485 == UART0
	uart_init(0,baudrate,RS485_BUFSIZE,mutex,priority);	
#elif UART_RS485 == UART1
	uart_init(1,baudrate,RS485_BUFSIZE,mutex,priority);
#elif UART_RS485 == UART2	
	uart_init(2,baudrate,RS485_BUFSIZE,mutex,priority);
#endif	
}

void rs485_putchar(uint8_t caracter)
{
	RS485_TX();
	RS485_RX_DISABLE();
	RS485_PUTCHAR(caracter);
	RS485_RX_ENABLE();
	RS485_RX();
}

void rs485_print(CHAR8 *string)
{
	RS485_TX();
	RS485_RX_DISABLE();
	RS485_PRINTF(string);
	RS485_RX_ENABLE();
	RS485_RX();
}

void rs485_tx(const INT8U *data, const INT16U _len)
{
	RS485_TX();
	RS485_RX_DISABLE();
	INT16U len = _len;
	while(len > 0)
	{
		RS485_PUTCHAR((*data));
		data++;		
		len--;
	}
	RS485_RX();
	RS485_RX_ENABLE();
}

INT8U rs485_rx(CHAR8* caracter, INT16U timeout)
{	
	INT8U ret;
	ret = OSQueuePend(RS485_QUEUE, (INT8U*)caracter, timeout);
	return (ret != TIMEOUT) ? TRUE:FALSE;
}

void rs485_rx_flush(void)
{
	OSCleanQueue(RS485_QUEUE);
}

#endif
