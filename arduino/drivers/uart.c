

/**
 * \file uart.c
 * \brief Driver for uart
 *
 * This file contains the uart microcontroller drivers.
 *
 **/

#include "BRTOS.h"
#include "hardware.h"
#include "uart.h"
#include "utils.h"
#include "terminal_io.h"
#include "mbport.h"

#if (ENABLE_UART0 == TRUE)
INT8U receive_byte0;
BRTOS_Mutex *SerialResource0;
BRTOS_Sem *SerialTX0;
OS_QUEUE SerialPortBuffer0;
BRTOS_Queue *Serial0;
#endif

#if (ENABLE_UART1 == TRUE)
INT8U receive_byte1 = 0;
BRTOS_Mutex *SerialResource1;
BRTOS_Sem *SerialTX1;
OS_QUEUE SerialPortBuffer1;
BRTOS_Queue *Serial1;
#endif

#if (ENABLE_UART2 == TRUE)
INT8U receive_byte2 = 0;
BRTOS_Mutex *SerialResource2;
BRTOS_Sem *SerialTX2;
OS_QUEUE SerialPortBuffer2;
BRTOS_Queue *Serial2;
#endif


void uart0_init(unsigned int baudrate);

void uart0_init(unsigned int baudrate)
{
	/*Set baud rate */
	UBRR0H = (INT8U)(baudrate>>8);
	UBRR0L = (INT8U)baudrate;

	/*Enable receiver and transmitter. Enable RX interrupt */
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1 << RXCIE0);
	/* Set frame format: 8 bit data, 1 stop bit */
	UCSR0C = (3<<UCSZ00); 								
}


void _putchar_uart0(CHAR8 data)
{
   /* Wait for empty transmit buffer */
	while (!(UCSR0A & 0x20)){}
    UCSR0A = 0x20;
	// Put data into buffer, sends the data */
    UDR0 = data;
}


void _print_uart0(char *string)
{
  while(*string)
  { 
	putchar_uart0(*string);
    string++;
  }
}

void _printP_uart0(char const *string)
{
	char c;
	while((c=pgm_read_byte(*string)) != 0)
	{
		putchar_uart0(c);
		string++;
	}
}

void uart_init(INT8U uart, INT16U baudrate, INT16U buffersize, INT8U mutex, INT8U priority)
{
#if (ENABLE_UART0 == TRUE)		
	/* check if UART 0 is already init */
	if(uart == 0 && Serial0 != NULL)
	{
		if(Serial0->OSEventAllocated == TRUE)
		{
			return;
		}
	}
#endif	

#if (ENABLE_UART1 == TRUE)	
	/* check if UART 1 is already init */
	if(uart == 1 && Serial1 != NULL)
	{
		if(Serial1->OSEventAllocated == TRUE)
		{
			return;
		}
	}
#endif	
	
#if (ENABLE_UART1 == TRUE)		
	/* check if UART 2 is already init */
	if(uart == 2 && Serial2 != NULL)
	{
		if(Serial2->OSEventAllocated == TRUE)
		{
			return;
		}
	}
#endif	

		// Configure UART 0
		#if (ENABLE_UART0 == TRUE)
		if (uart == 0)
		{
			
			uart0_init(baudrate);
			
			// Cria um mutex com contador = 1, informando que o recurso está disponível
			// após a inicialização
			// Prioridade máxima a acessar o recurso = priority
			
			if (mutex == TRUE)
			{
				if (OSMutexCreate(&SerialResource0, priority) != ALLOC_EVENT_OK)
				{
					while (1){};
				}
			}

			if (OSSemCreate(0, &SerialTX0) != ALLOC_EVENT_OK)
			{
				while (1){};
			}

			if (OSQueueCreate(&SerialPortBuffer0, buffersize,
			&Serial0) != ALLOC_EVENT_OK)
			{
				while (1){};
			}
		}
		#endif
			
		// Configure UART 1
#if (ENABLE_UART1 == TRUE)
		if (uart == 1)
		{
			
			uart1_init(baudrate);
			
			// Cria um mutex com contador = 1, informando que o recurso está disponível
			// após a inicialização
			// Prioridade máxima a acessar o recurso = priority
		
			if (mutex == TRUE)
			{
				if (OSMutexCreate(&SerialResource1, priority) != ALLOC_EVENT_OK)
				{
					while (1){};
				}
			}

			if (OSSemCreate(0, &SerialTX1) != ALLOC_EVENT_OK)
			{
				while (1){};
			}

			if (OSQueueCreate(&SerialPortBuffer1, buffersize,
					&Serial1) != ALLOC_EVENT_OK)
			{
				while (1){};
			}
		}		
#endif

		// Configure UART 2
#if (ENABLE_UART2 == TRUE)
		if (uart == 2)
		{
			
			uart2_init(baudrate);
			
			// Cria um mutex com contador = 1, informando que o recurso está disponível
			// após a inicialização
			// Prioridade máxima a acessar o recurso = priority
			if (mutex == TRUE)
			{
				if (OSMutexCreate(&SerialResource2, priority) != ALLOC_EVENT_OK)
				{
					while (1){};
				}
			}

			if (OSSemCreate(0, &SerialTX2) != ALLOC_EVENT_OK)
			{
				while (1){};
			}

			if (OSQueueCreate(&SerialPortBuffer2, buffersize,
					&Serial2) != ALLOC_EVENT_OK)
			{
				while (1){};
			}
		}
#endif

}

// UART0 functions
#if (ENABLE_UART0 == TRUE)

void uart0_tx(void)
{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_INT_ENTER();
	

	#if (NESTING_INT == 1)
	OS_ENABLE_NESTING();
	#endif


	(void) OSSemPost(SerialTX0);

	// ************************
	// Interrupt Exit
	// ************************
	OS_INT_EXIT();
	// ************************
}

//Função para adquirir direito exclusivo a porta serial
// Assim que possível colocar recurso de timeout
void uart0_acquire(void)
{
	// Aloca o recurso da porta serial
	OSMutexAcquire(SerialResource0);
}

//Função para liberar a porta serial
void uart0_release(void)
{
	// Libera o recurso da porta serial
	OSMutexRelease(SerialResource0);
}

void uart0_RxEnableISR(void)
{
	
}

void uart0_RxDisableISR(void)
{
	
}


void uart0_TxEnableISR(void)
{
	
}

void uart0_TxDisableISR(void)
{
	
}


INT8U putchar_uart0(INT8U caracter)
{
	_putchar_uart0(caracter);
	
#if 0	
	if(OSSemPend(SerialTX2, TX_TIMEOUT) == TIMEOUT)
	{
		return caracter++;
	}
#endif	
	
	return caracter;
}

void printf_uart0(CHAR8 *string)
{

	while (*string)
	{
		putchar_uart0(*string);
		string++;
	}
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
//__attribute__ ((section (".lowtext")))
ISR(USART0_RX_vect, __attribute__ ( ( naked ) ))
#else
ISR(USART_RX_vect, __attribute__ ( ( naked ) ))
#endif
{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_SAVE_ISR();
	OS_INT_ENTER();

	INT8U caracter = 0;
	caracter = UDR0;

	#if (NESTING_INT == 1)
	OS_ENABLE_NESTING();
	#endif

	if (OSQueuePost(Serial0,caracter) == BUFFER_UNDERRUN)
	{
		// Problema: Estouro de buffer
		(void)OSCleanQueue(Serial0);
	}

	// ************************
	// Interrupt Exit
	// ************************
	OS_INT_EXIT();
	OS_RESTORE_ISR();
	// ************************
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


void uart0_error(void)
{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_INT_ENTER();

	#if (NESTING_INT == 1)
	OS_ENABLE_NESTING();
	#endif

	// ************************
	// Interrupt Exit
	// ************************
	OS_INT_EXIT();
	// ************************
}

#endif

// UART1 functions
#if (ENABLE_UART1 == TRUE)

void uart1_tx(void)
{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_INT_ENTER();



#if (NESTING_INT == 1)
	OS_ENABLE_NESTING();
#endif  
	
	(void) OSSemPost(SerialTX1);

	// ************************
	// Interrupt Exit
	// ************************
	OS_INT_EXIT();
	// ************************
}

//Função para adquirir direito exclusivo a porta serial
// Assim que possível colocar recurso de timeout
void uart1_acquire(void)
{
	// Aloca o recurso da porta serial
	OSMutexAcquire(SerialResource1);
}

//Função para liberar a porta serial
void uart1_release(void)
{
	// Libera o recurso da porta serial
	OSMutexRelease(SerialResource1);
}

void uart1_RxEnable(void)
{
	
}

void uart1_RxDisable(void)
{
	
}


void uart1_RxEnableISR(void)
{
	
}

void uart1_RxDisableISR(void)
{
	
}


void uart1_TxEnableISR(void)
{

}

void uart1_TxDisableISR(void)
{
	
}

INT8U putchar_uart1(INT8U caracter)
{
	

	if(OSSemPend(SerialTX1, TX_TIMEOUT) == TIMEOUT)
	{
		return caracter++;
	}
	
	return caracter;
}

void printf_uart1(CHAR8 *string)
{

	while (*string)
	{
		putchar_uart1(*string);
		string++;
	}

}


void uart1_rx(void)

{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_INT_ENTER();


#if (NESTING_INT == 1)
	OS_ENABLE_NESTING();
#endif  


	if (OSQueuePost(Serial1, receive_byte1) == BUFFER_UNDERRUN)
	{
		// Problema: Estouro de buffer
		OSCleanQueue(Serial1);
	}

	// ************************
	// Interrupt Exit
	// ************************
	OS_INT_EXIT();
	// ************************
}


void uart1_error(void)
{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_INT_ENTER();

	

#if (NESTING_INT == 1)
	OS_ENABLE_NESTING();
#endif  

	// ************************
	// Interrupt Exit
	// ************************
	OS_INT_EXIT();
	// ************************
}

#endif

// UART2 functions
#if (ENABLE_UART2 == TRUE)

void uart2_tx(void)
{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_INT_ENTER();

	

#if (NESTING_INT == 1)
	OS_ENABLE_NESTING();
#endif  


	(void) OSSemPost(SerialTX2);

	// ************************
	// Interrupt Exit
	// ************************
	OS_INT_EXIT();
	// ************************
}

//Função para adquirir direito exclusivo a porta serial
// Assim que possível colocar recurso de timeout
void uart2_acquire(void)
{
	// Aloca o recurso da porta serial
	OSMutexAcquire(SerialResource2);
}

//Função para liberar a porta serial
void uart2_release(void)
{
	// Libera o recurso da porta serial
	OSMutexRelease(SerialResource2);
}

void uart2_RxEnableISR(void)
{
	
}

void uart2_RxDisableISR(void)
{
	
}


void uart2_TxEnableISR(void)
{
	
}

void uart2_TxDisableISR(void)
{
	
}


INT8U putchar_uart2(INT8U caracter)
{
	
	if(OSSemPend(SerialTX2, TX_TIMEOUT) == TIMEOUT)
	{
		return caracter++;
	}
	
	return caracter;
}

void printf_uart2(CHAR8 *string)
{

	while (*string)
	{
		putchar_uart2(*string);
		string++;	
	}
}


void uart2_rx(void)
{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_INT_ENTER();
	

#if (NESTING_INT == 1)
	OS_ENABLE_NESTING();
#endif  

	if (OSQueuePost(Serial2, receive_byte2) == BUFFER_UNDERRUN)
	{
		// Problema: Estouro de buffer
		OSCleanQueue(Serial2);
	}

	// ************************
	// Interrupt Exit
	// ************************
	OS_INT_EXIT();
	// ************************
}


void uart2_error(void)
{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_INT_ENTER();

#if (NESTING_INT == 1)
	OS_ENABLE_NESTING();
#endif  

	// ************************
	// Interrupt Exit
	// ************************
	OS_INT_EXIT();
	// ************************
}

#endif

void SerialReset(INT8U Comm)
{
	
}
