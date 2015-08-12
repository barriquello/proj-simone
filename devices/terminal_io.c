/*
 * terminal_io.c
 *
 *  Created on: Jul 22, 2015
 *      Author: Universidade Federal
 */

#include "terminal_io.h"
#include "uart.h"
#include "virtual_com.h"

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


void printSer(INT8U SerialPort, CHAR8 *string)
{
	switch(SerialPort)
	{
	  case USE_UART1:
	    #if (ENABLE_UART1 == TRUE)
	    printf_uart1(string);
	    #endif
	    break;
	  case USE_UART2:
	    #if (ENABLE_UART2 == TRUE)
	    printf_uart2(string);
	    #endif	  
	    break;
	  case USE_USB:
	    printf_usb(string);
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
	    putchar_usb(caracter);
	    break;	    	    
	  default:
	    break;
	}	
}
