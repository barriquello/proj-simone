/*
 * terminal_io.h
 *
 *  Created on: Jul 22, 2015
 *      Author: Universidade Federal
 */

#ifndef TERMINAL_IO_H_
#define TERMINAL_IO_H_

#include "BRTOS.h"

#define USE_USB		0
#define USE_UART1	1
#define USE_UART2	2

typedef INT8U (*term_input)(CHAR8 *);
typedef INT8U (*term_output)(CHAR8);	

void terminal_set_input (term_input _input);
void terminal_set_output (term_output _output);

void terminal_input (CHAR8 *c);
void terminal_output (CHAR8 c);

void printSer(INT8U SerialPort, CHAR8 *string);
void putcharSer(INT8U SerialPort, CHAR8 caracter);

#endif /* TERMINAL_IO_H_ */
