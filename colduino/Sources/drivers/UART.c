/**
 * \file uart.c
 * \brief Driver for uart
 *
 * This file contains the uart microcontroller drivers.
 *
 **/

#include "hardware.h"
#include "uart.h"
#include "utils.h"
#include "mbport.h"

#pragma warn_implicitconv off

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

void uart_init(INT8U uart, INT16U baudrate, INT16U buffersize, INT8U UartPins,
		INT8U mutex, INT8U priority)
{
	
	/* check if UART 1 is already init */
	if(uart == 1 && Serial1 != NULL)
	{
		if(Serial1->OSEventAllocated == TRUE)
		{
			return;
		}
	}
	
	/* check if UART 2 is already init */
	if(uart == 2 && Serial2 != NULL)
	{
		if(Serial2->OSEventAllocated == TRUE)
		{
			return;
		}
	}
	
	if ((uart == 1) || (uart == 2))
	{
					
		switch (UartPins)
		{
			case UART1_PTA1_PTA2:
				SOPT3 = SOPT3 & 0xBF;
				break;
			case UART1_PTD6_PTD7:
				SOPT3 = SOPT3 | 0x40;
				break;
			case UART2_PTE5_PTE6:
				SOPT3 = SOPT3 & 0x7F;
				break;
			case UART2_PTF1_PTF2:
				SOPT3 = SOPT3 | 0x80;
				break;
			default:
				break;
		}
		// Configure UART 1
#if (ENABLE_UART1 == TRUE)
		if (uart == 1)
		{
			SCGC1 |= SCGC1_SCI1_MASK; /* Enables sci1 clock */
			//SCI1C1 = 0x12; /* Configure the SCI */
			SCI1C1 = 0x00; /* Configure the SCI */
			/* SCI1C3: R8=0,T8=0,TXDIR=0,TXINV=0,ORIE=0,NEIE=0,FEIE=0,PEIE=0 */
			SCI1C3 = 0x00; /* Disable error interrupts */
			/* SCI1S2: ??=0,??=0,??=0,??=0,??=0,BRK13=0,??=0,RAF=0 */
			SCI1S2 = 0x00;
			/* SCI1C2: TIE=0,TCIE=0,RIE=0,ILIE=0,TE=0,RE=0,RWU=0,SBK=0 */
			SCI1C2 = 0x00; /* Disable all interrupts */

			// 0x270 = 2400  bauds at 24Mhz     // 0x138 = 4800  bauds at 24Mhz
			// 0x9C  = 9600  bauds at 24Mhz     // 0x4E  = 19200 bauds at 24Mhz
			// 0x20  = 38400 bauds at 24Mhz     // 0x16  = 57600 bauds at 24Mhz
			switch (baudrate)
			{
			case 2400:
				SCI1BD = 0x270;
				break;
			case 4800:
				SCI1BD = 0x138;
				break;
			case 9600:
				SCI1BD = 0x9C;
				break;
			case 19200:
				SCI1BD = 0x4E;
				break;
			case 38400:
				SCI1BD = 0x20;
				break;
			case 57600:
				SCI1BD = 0x16;
				break;
			default:
				break;
			}

			/* SCI1C3: ORIE=1,NEIE=1,FEIE=1,PEIE=1 */
			//SCI1C3 |= 0x0F; /* Enable error interrupts */
			SCI1C3 = 0x00; /* Enable error interrupts */
			//SCI1C2 |= ( SCI1C2_TE_MASK | SCI1C2_RE_MASK | SCI1C2_RIE_MASK); /*  Enable transmitter, Enable receiver, Enable receiver interrupt */
			SCI1C2 = 0x2C;

			(void) SCI1S1; /* Leitura do registrador SCI1S1 para analisar o estado da transmissão */
			(void) SCI1S2; /* Leitura do registrador SCI1S1 para analisar o estado da transmissão */
			(void) SCI1C3; /* Leitura do registrador SCI1C3 para limpar o bit de paridade */

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
			SCGC1 |= SCGC1_SCI2_MASK; /* Enables sci2 clock */
			SCI2C1 = 0x00; /* Configure the SCI */
			/* SCI1C3: R8=0,T8=0,TXDIR=0,TXINV=0,ORIE=0,NEIE=0,FEIE=0,PEIE=0 */
			SCI2C3 = 0x00; /* Disable error interrupts */
			/* SCI1S2: ??=0,??=0,??=0,??=0,??=0,BRK13=0,??=0,RAF=0 */
			SCI2S2 = 0x00;
			/* SCI1C2: TIE=0,TCIE=0,RIE=0,ILIE=0,TE=0,RE=0,RWU=0,SBK=0 */
			SCI2C2 = 0x00; /* Disable all interrupts */

			// 0x270 = 2400  bauds at 24Mhz     // 0x138 = 4800  bauds at 24Mhz
			// 0x9C  = 9600  bauds at 24Mhz     // 0x4E  = 19200 bauds at 24Mhz
			// 0x20  = 38400 bauds at 24Mhz     // 0x16  = 57600 bauds at 24Mhz
			switch (baudrate)
			{
			case 2400:
				SCI2BD = 0x270;
				break;
			case 4800:
				SCI2BD = 0x138;
				break;
			case 9600:
				SCI2BD = 0x9C;
				break;
			case 19200:
				SCI2BD = 0x4E;
				break;
			case 38400:
				SCI2BD = 0x20;
				break;
			case 57600:
				SCI2BD = 0x16;
				break;
			default:
				break;
			}

			/* SCI1C3: ORIE=1,NEIE=1,FEIE=1,PEIE=1 */
			SCI2C3 |= 0x0F; /* Enable error interrupts */
			//SCI1C2 |= ( SCI1C2_TE_MASK | SCI1C2_RE_MASK | SCI1C2_RIE_MASK); /*  Enable transmitter, Enable receiver, Enable receiver interrupt */
			SCI2C2 = 0x2C;

			(void) SCI2S1; /* Leitura do registrador SCI1S1 para analisar o estado da transmissão */
			(void) SCI2S2; /* Leitura do registrador SCI1S1 para analisar o estado da transmissão */
			(void) SCI2C3; /* Leitura do registrador SCI1C3 para limpar o bit de paridade */

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
}

// UART1 functions
#if (ENABLE_UART1 == TRUE)

#if (NESTING_INT == 1)
#pragma TRAP_PROC
void uart1_tx(void)
#else
interrupt void uart1_tx(void)
#endif
{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_INT_ENTER();

	// Tratamento da interrupção  
	SCI1C2_TCIE = 0;
	(void) SCI1S1; /* Leitura do registrador SCIxS1 para analisar o estado da transmissão */
	(void) SCI1C3; /* Leitura do registrador SCIxC3 para limpar o bit de paridade */

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
	SCI1C2_RE = 1;
}

void uart1_RxDisable(void)
{
	SCI1C2_RE = 0;
}


void uart1_RxEnableISR(void)
{
	SCI1C2_RIE = 1;
}

void uart1_RxDisableISR(void)
{
	SCI1C2_RIE = 0;
}


void uart1_TxEnableISR(void)
{
	SCI1C2_TIE = 1;
}

void uart1_TxDisableISR(void)
{
	SCI1C2_TIE = 1;
}

void putchar_uart1(byte caracter)
{
	
	SCI1D = caracter; /* Armazena o caracter a ser transmitido no registrador de transmissão */
	SCI1C2_TCIE = 1;

	(void) OSSemPend(SerialTX1, TX_TIMEOUT);
}

void printf_uart1(CHAR8 *string)
{

	while (*string)
	{
		SCI1D = *string; /* Armazena o caracter a ser transmitido no registrador de transmissão */
		SCI1C2_TCIE = 1;
		(void) OSSemPend(SerialTX1, TX_TIMEOUT);
		string++;
	}

}

#if (NESTING_INT == 1)
#pragma TRAP_PROC
void uart1_rx(void)
#else
interrupt void uart1_rx(void)
#endif
{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_INT_ENTER();

	// Tratamento da interrupção
	(void) SCI1S1; /* Leitura do registrador SCIxS1 para analisar o estado da transmissão */
	(void) SCI1C3; /* Leitura do registrador SCIxC3 para limpar o bit de paridade */
	receive_byte1 = SCI1D; /* Leitura dos dados recebidos */

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

#if (NESTING_INT == 1)
#pragma TRAP_PROC
void uart1_error(void)
#else
interrupt void uart1_error(void)
#endif
{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_INT_ENTER();

	// Tratamento da interrupção
	(void) SCI1S1; /* Leitura do registrador SCIxS1 para analisar o estado da transmissão */
	(void) SCI1C3; /* Leitura do registrador SCIxC3 para limpar o bit de paridade */

	// A próxima ação depende do tipo de erro
	// Devemos analisar o erro ocorrido e tomar uma das atitudes abaixo
	(void) SCI1D; // Leitura do registrador SCIxD para limpar os indicativos de erro.
	SCI1D = 0; // Escrita no registrador SCIxD para limpar os indicativos de erro. 

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

#if (NESTING_INT == 1)
#pragma TRAP_PROC
void uart2_tx(void)
#else
interrupt void uart2_tx(void)
#endif
{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_INT_ENTER();

	// Tratamento da interrupção  
	SCI2C2_TCIE = 0;
	(void) SCI2S1; /* Leitura do registrador SCIxS1 para analisar o estado da transmissão */
	(void) SCI2C3; /* Leitura do registrador SCIxC3 para limpar o bit de paridade */

#if (NESTING_INT == 1)
	OS_ENABLE_NESTING();
#endif  

	//pxMBFrameCBTransmitterEmpty();

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
	SCI2C2_RIE = 1;
}

void uart2_RxDisableISR(void)
{
	SCI2C2_RIE = 0;
}


void uart2_TxEnableISR(void)
{
	SCI2C2_TIE = 1;
}

void uart2_TxDisableISR(void)
{
	SCI2C2_TIE = 1;
}


void putchar_uart2(byte caracter)
{

	SCI2D = caracter; /* Armazena o caracter a ser transmitido no registrador de transmissão */
	SCI2C2_TCIE = 1;
	
	(void) OSSemPend(SerialTX2, TX_TIMEOUT);	
}

void printf_uart2(CHAR8 *string)
{

	while (*string)
	{
		SCI2D = *string; /* Armazena o caracter a ser transmitido no registrador de transmissão */
		SCI2C2_TCIE = 1;
		(void) OSSemPend(SerialTX2, TX_TIMEOUT);
		string++;
	}
}

#if (NESTING_INT == 1)
#pragma TRAP_PROC
void uart2_rx(void)
#else
interrupt void uart2_rx(void)
#endif
{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_INT_ENTER();

	// Tratamento da interrupção
	(void) SCI2S1; /* Leitura do registrador SCIxS1 para analisar o estado da transmissão */
	(void) SCI2C3; /* Leitura do registrador SCIxC3 para limpar o bit de paridade */
	receive_byte2 = SCI2D; /* Leitura dos dados recebidos */

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

#if (NESTING_INT == 1)
#pragma TRAP_PROC
void uart2_error(void)
#else
interrupt void uart2_error(void)
#endif
{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_INT_ENTER();

	// Tratamento da interrupção
	(void) SCI2S1; /* Leitura do registrador SCIxS1 para analisar o estado da transmissão */
	(void) SCI2C3; /* Leitura do registrador SCIxC3 para limpar o bit de paridade */

	// A próxima ação depende do tipo de erro
	// Devemos analisar o erro ocorrido e tomar uma das atitudes abaixo
	(void) SCI2D; // Leitura do registrador SCIxD para limpar os indicativos de erro.
	SCI2D = 0; // Escrita no registrador SCIxD para limpar os indicativos de erro. 

#if (NESTING_INT == 1)
	OS_ENABLE_NESTING();
#endif  

	// ************************
	// Interrupt Exit
	// ************************
	OS_INT_EXIT()
	;
	// ************************
}

#endif

void SerialReset(INT8U Comm)
{
	INT8U reset1 = 0;
	INT8U reset2 = 0;

	reset1 = SRS / 100;
	putcharSer(Comm, reset1 + '0');

	reset2 = ((SRS - reset1 * 100) / 10);
	putcharSer(Comm, reset2 + '0');

	reset1 = ((SRS - reset1 * 100 - reset2 * 10) % 10);
	putcharSer(Comm, reset1 + '0');
	putcharSer(Comm, LF);
	putcharSer(Comm, CR);
	__RESET_WATCHDOG();
}
