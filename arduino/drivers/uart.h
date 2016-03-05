/** \addtogroup drivers  Drivers
 *  @{
 */
 
 /*! \defgroup UART
 * @{
 */

/*! \file UART.h
 \brief Rotinas para transferir e receber dados via UART.
 */

#include "BRTOS.h"
#include "AppConfig.h"

#define BAUD(x)		((configCPU_CLOCK_HZ/16/(x)) - 1)

// Enable/disable UARTs
#define ENABLE_UART0   TRUE
#define ENABLE_UART1   TRUE
#define ENABLE_UART2   TRUE

#define UART0 		0
#define UART1 		1
#define UART2 		2

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
#define UART0_MUTEX_PRIO 	9
#endif

#ifndef UART1_MUTEX_PRIO
#define UART1_MUTEX_PRIO 	10
#endif

#ifndef UART2_MUTEX_PRIO
#define UART2_MUTEX_PRIO 	11
#endif

/*! \def CR
 \brief ASCII code for carry return
 
 \def LF
 \brief  ASCII code for line feed
 
 \def TX_TIMEOUT
 \brief  timeout in miliseconds for characters transmission
 */

#define CR             13         //  ASCII code for carry return
#define LF             10         //  ASCII code for line feed
#define TX_TIMEOUT     5          // timeout in miliseconds for characters transmition


/*! \fn void uart_init(INT8U uart, INT16U baudrate, INT16U buffersize, INT8U UartPins,
 INT8U mutex, INT8U priority)
 
 \brief Inicializa UART
 
 \param uart UART0, UART1 ou UART2
 \param baudrate Taxa de transmissao
 \param buffersize Tamanho do buffer
 \param UartPins Pinos da UART
 \param mutex Mutex para UART
 \param priority Prioridade da UART
 
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

void SerialReset(INT8U Comm);

// UART1 functions
#if (ENABLE_UART0 == TRUE)
void uart0_acquire(void);
void uart0_release(void);
char putchar_uart0(char caracter);
INT8U getchar_uart0(char* caracter, INT16U timeout);
void printf_uart0(char *string);
void printP_uart0(char const *string);
void uart0_tx(void);
void uart0_rx(void);
void uart0_error(void);

void uart0_RxEnable(void);
void uart0_RxDisable(void);
void uart0_RxEnableISR(void);
void uart0_RxDisableISR(void);
void uart0_TxEnableISR(void);
void uart0_TxDisableISR(void);

#endif

// UART1 functions
#if (ENABLE_UART1 == TRUE)
void uart1_acquire(void);
void uart1_release(void);
char putchar_uart1(char caracter);
void printf_uart1(char *string);
void printP_uart1(char const *string);
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
void uart2_acquire(void);
void uart2_release(void);
char putchar_uart2(char caracter);
void printf_uart2(char *string);
void printP_uart2(char const *string);
void uart2_tx(void);
void uart2_rx(void);
void uart2_error(void);

void uart2_RxEnableISR(void);
void uart2_RxDisableISR(void);
void uart2_TxEnableISR(void);
void uart2_TxDisableISR(void);

#endif

/** @} */
/** @} */