/*! \file RS485.h
 \brief Rotinas para transferir e receber dados via RS485/UART.
 */

#include "BRTOS.h"
#include "uart.h"

#define UART1 		1
#define UART2 		2
#define UART_RS485   UART1

/*! \fn void rs485_init(INT8U uart, INT16U baudrate, INT16U buffersize, INT8U mutex, INT8U priority)
 
 \brief Inicializa RS485/UART

 \param baudrate Taxa de transmissao
 \param mutex Mutex para UART
 \param priority Prioridade da UART
 
 \fn void putchar_rs485(byte caracter)
 \brief  Armazena o caracter a ser transmitido no registrador de transmissao
 \param caracter Caractere a ser transmitido
 
 \fn void rx_rs485(void)
 \brief função para recepcao de dados 
 
 */

void rs485_init(INT16U baudrate, INT8U mutex, INT8U priority);

// RS485/UART functions
void rs485_acquire(void);
void rs485_release(void);
void rs485_putchar(INT8U caracter);
void rs485_print(CHAR8 *string);
INT8U rs485_rx(CHAR8* caracter, INT16U timeout);
void rs485_tx(const INT8U *data, const INT16U len);
void rs485_rx_flush(void);


