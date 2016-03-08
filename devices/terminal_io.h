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
 * terminal_io.h
 *
 *  Created on: Jul 22, 2015
 *      Author: UFSM
 */
 
 
/** \addtogroup devices
 *  @{
 */
 
 /*! \defgroup terminal Terminal I/O
 * @{
 Interface para ler/escrever dados no terminal selecionável para UART ou USB.
 */
 
 
/*! \file terminal_io.h
 \brief Interface para ler/escrever dados no terminal.
 
 Funcoes de leitura e escrita sao feitas por UART ou USB.
 */

 
#ifndef TERMINAL_IO_H_
#define TERMINAL_IO_H_

#include "BRTOS.h"

#define USE_USB		0
#define USE_UART0   0
#define USE_UART1	1
#define USE_UART2	2

typedef CHAR8 (*term_input)(CHAR8 *);
typedef CHAR8 (*term_output)(CHAR8);	

void terminal_set_input (term_input _input);
void terminal_set_output (term_output _output);

void terminal_input (CHAR8 *c);
void terminal_output (CHAR8 c);

void printSer(INT8U SerialPort, const CHAR8 *string);
void putcharSer(INT8U SerialPort, CHAR8 caracter);

#ifdef __AVR__
void printSer_P(INT8U SerialPort, const CHAR8 *string);
void putcharSer_P(INT8U SerialPort, CHAR8 caracter);
#endif

#endif /* TERMINAL_IO_H_ */
/** @}*/
/** @}*/
