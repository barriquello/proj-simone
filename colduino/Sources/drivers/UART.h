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
/*! \file UART.h
 \brief Rotinas para transferir e receber dados via UART.
 */

#include "AppConfig.h"
#include "BRTOS.h"

#ifndef UART_H
#define UART_H

#define UART0 		0
#define UART1 		1
#define UART2 		2

// Enable/disable UARTs       

#define ENABLE_UART1   TRUE
#define ENABLE_UART2   TRUE


// Enable/disable mutex for UARTs
#ifndef UART0_MUTEX
#define UART0_MUTEX 	1
#endif
#ifndef UART1_MUTEX
#define UART1_MUTEX 	0
#endif
#ifndef UART2_MUTEX
#define UART2_MUTEX 	0
#endif

// Config mutex priorities for UARTs

#ifndef UART0_MUTEX_PRIO
#define UART0_MUTEX_PRIO 	19
#endif

#ifndef UART1_MUTEX_PRIO
#define UART1_MUTEX_PRIO 	20
#endif

#ifndef UART2_MUTEX_PRIO
#define UART2_MUTEX_PRIO 	21
#endif


/*! \def CR
 \brief ASCII code for carry return
 
 \def LF
 \brief  ASCII code for line feed
 
 \def TX_TIMEOUT
 \brief  timeout in miliseconds for characters transmition
 */

#define CR             13         //  ASCII code for carry return
#define LF             10         //  ASCII code for line feed
#define TX_TIMEOUT     5          // timeout in miliseconds for characters transmition
#define UART1_PTA1_PTA2 0
#define UART1_PTD6_PTD7 1
#define UART2_PTE5_PTE6 2
#define UART2_PTF1_PTF2 3


//#define CONF_UART1_PINS		UART1_PTA1_PTA2
#define CONF_UART1_PINS     UART1_PTD6_PTD7
#define CONF_UART2_PINS		UART2_PTE5_PTE6

typedef enum
{
	NONE,
	EVEN,
	ODD,
}uart_parity_t;

/*! \fn void uart_init(INT8U uart, INT16U baudrate, INT16U buffersize, INT8U UartPins,
 INT8U mutex, INT8U priority)
 
 \brief Inicializa UART
 
 \param uart UART1 ou UART2
 \param baudrate Taxa de transmissao
 \param buffersize Tamanho do buffer
 \param UartPins Pinos da UART
 \param mutex Mutex para UART
 \param priority Prioridade da UART
 
 
 \fn void uart_set(INT8U uart, INT16U baudrate, uart_parity_t parity)
 
 \brief Configura UART
 
 \param uart UART1 ou UART2
 \param baudrate Taxa de transmissao
 \param parity paridade; nenhuma, par ou impar
 
 \fn void putchar_uart1(byte caracter)
 \brief  Armazena o caracter a ser transmitido no registrador de transmissao
 \param caracter Caractere a ser transmitido
 
 \fn void uart1_tx(void)
 \brief ISR para transmissao de dados
 
 \fn void uart1_rx(void)
 \brief ISR para recepcao de dados 
 
 \fn void putchar_uart2(byte caracter)
 \brief  Armazena o caracter a ser transmitido no registrador de transmissao
 \param caracter Caractere a ser transmitido
 
 \fn void uart2_tx(void)
 \brief ISR para transmissao de dados
 
 \fn void uart2_rx(void)
 \brief ISR para recepcao de dados 
 */

void uart_init(INT8U uart, INT16U baudrate, INT16U buffersize, INT8U mutex, INT8U priority);
INT8U uart_set(INT8U uart, INT16U baudrate, uart_parity_t parity);

void SerialReset(INT8U Comm);

// UART1 functions
#if (ENABLE_UART1 == TRUE)
extern BRTOS_Queue *Serial1;
void uart1_acquire(void);
void uart1_release(void);
INT8U putchar_uart1(INT8U caracter);
void printf_uart1(CHAR8 *string);
void uart1_tx(void);
void uart1_rx(void);
void uart1_error(void);

void uart1_RxEnable(void);
void uart1_RxDisable(void);
void uart1_RxEnableISR(void);
void uart1_RxDisableISR(void);
void uart1_TxEnableISR(void);
void uart1_TxDisableISR(void);

#endif

// UART2 functions
#if (ENABLE_UART2 == TRUE)
extern BRTOS_Queue *Serial2;
void uart2_acquire(void);
void uart2_release(void);
INT8U putchar_uart2(INT8U caracter);
void printf_uart2(CHAR8 *string);
void uart2_tx(void);
void uart2_rx(void);
void uart2_error(void);

void uart2_RxEnableISR(void);
void uart2_RxDisableISR(void);
void uart2_TxEnableISR(void);
void uart2_TxDisableISR(void);

#endif

#endif

