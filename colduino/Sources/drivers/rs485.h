/*! \file RS485.h
 \brief Rotinas para transferir e receber dados via RS485/UART.
 */

#include "BRTOS.h"

#define UART1 	1
#define UART2 	2
#define UART_RS485   UART1

/*! \fn void rs485_init(INT8U uart, INT16U baudrate, INT16U buffersize, INT8U UartPins,
 INT8U mutex, INT8U priority)
 
 \brief Inicializa RS485/UART

 \param baudrate Taxa de transmicao
 \param UartPins Pinos da UART
 \param mutex Mutex para UART
 \param priority Prioridade da UART
 
 \fn void putchar_rs485(byte caracter)
 \brief  Armazena o caracter a ser transmitido no registrador de transmissao
 \param caracter Caractere a ser transmitido
 
 \fn void rx_rs485(void)
 \brief função para recepcao de dados 
 
 */

void rs485_init(INT16U baudrate, INT8U UartPins, INT8U mutex, INT8U priority);

// RS485/UART functions
void rs485_acquire(void);
void rs485_release(void);
void putchar_rs485(INT8U caracter);
void printf_rs485(CHAR8 *string);
void rx_rs485(CHAR8* caracter);
void tx_rs485(INT8U *data, INT16U len);


