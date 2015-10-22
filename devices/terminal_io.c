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
 * terminal_io.c
 *
 *  Created on: Jul 22, 2015
 *      Author: UFSM
 */

#include "AppConfig.h"
#include "terminal_io.h"
#include "uart.h"

#if COLDUINO
#include "virtual_com.h"
#endif

static term_input input = NULL;
static term_output output = NULL;

void terminal_set_input (term_input _input)
{
	input = _input;
}
void terminal_set_output (term_output _output)
{
	output = _output;
}

void terminal_input (CHAR8 *c)
{
	if(input == NULL)
	{
		*c = 0;
	}else
	{
		input(c);
	}
}
void terminal_output (CHAR8 c)
{
	if(output == NULL)
	{
		(void)c;
	}else
	{
		output(c);
	}
}


void printSer(INT8U SerialPort, const CHAR8 *string)
{
	switch(SerialPort)
	{
	  case USE_UART1:
	    #if (ENABLE_UART1 == TRUE)
	    printf_uart1((CHAR8 *)string);
	    #endif
	    break;
	  case USE_UART2:
	    #if (ENABLE_UART2 == TRUE)
	    printf_uart2((CHAR8 *)string);
	    #endif	  
	    break;
	  case USE_USB:
		#if (ENABLE_USB)
	    printf_usb((CHAR8 *)string);
		#endif
		#if (ENABLE_UART0 == TRUE)
		printf_uart0((CHAR8 *)string);
		#endif
	    break;	    	    
	  default:
	    break;
	}
}


void putcharSer(INT8U SerialPort, CHAR8 caracter)
{
	switch(SerialPort) 
	{
	  case USE_UART1:
	    #if (ENABLE_UART1 == TRUE)
	    putchar_uart1(caracter);
	    #endif
	    break;
	  case USE_UART2:
	    #if (ENABLE_UART2 == TRUE)
	    putchar_uart2(caracter);
	    #endif	  
	    break;
	  case USE_USB:
		#if (ENABLE_USB)
	    putchar_usb(caracter);
		#endif
		#if (ENABLE_UART0 == TRUE)
		putchar_uart0(caracter);
		#endif		
	    break;	    	    
	  default:
	    break;
	}	
}

#if ARDUINO
void printSer_P(INT8U SerialPort, const CHAR8 *string)
{
	switch(SerialPort)
	{
		case USE_UART0:
		#if (ENABLE_UART0 == TRUE)
		printP_uart0((CHAR8 *)string);
		#endif
		case USE_UART1:
		#if (ENABLE_UART1 == TRUE)
		printP_uart1((CHAR8 *)string);
		#endif
		break;
		case USE_UART2:
		#if (ENABLE_UART2 == TRUE)
		printP_uart2((CHAR8 *)string);
		#endif
		break;		
		default:
		break;
	}
}

void putcharSer_P(INT8U SerialPort, CHAR8 caracter)
{
	switch(SerialPort)
	{
		case USE_UART1:
		#if (ENABLE_UART1 == TRUE)
		putchar_uart1(pgm_read_byte(&caracter));
		#endif
		break;
		case USE_UART2:
		#if (ENABLE_UART2 == TRUE)
		putchar_uart2(pgm_read_byte(&caracter));
		#endif
		break;
		case USE_USB:
		#if (ENABLE_USB)
		putchar_usb(caracter);
		#endif
		#if (ENABLE_UART0 == TRUE)
		putchar_uart0(pgm_read_byte(&caracter));
		#endif
		break;
		default:
		break;
	}
}

#endif

