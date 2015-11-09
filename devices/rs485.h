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
/*! \file RS485.h
 \brief Rotinas para transferir e receber dados via RS485/UART.
 */

#include "BRTOS.h"
#include "uart.h"
#include "AppConfig.h"

#if COLDUINO
#define UART_RS485   UART1
#elif ARDUINO
#define UART_RS485   UART0
#endif


/*! 
  \fn void rs485_init(void)
  \brief Inicializa RS485/UART
 
 \fn void putchar_rs485(byte caracter)
 \brief  Armazena o caracter a ser transmitido no registrador de transmissao
 \param caracter Caractere a ser transmitido
 
 \fn void rx_rs485(void)
 \brief função para recepcao de dados 
 
 */

void rs485_init(void);

// RS485/UART functions
void rs485_acquire(void);
void rs485_release(void);
void rs485_putchar(INT8U caracter);
void rs485_print(CHAR8 *string);
INT8U rs485_rx(CHAR8* caracter, INT16U timeout);
void rs485_tx(const INT8U *data, const INT16U len);
void rs485_rx_flush(void);


