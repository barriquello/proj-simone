/*
 * FreeModbus Libary: CFV1 Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 * Copyright (C) 2008 Trond Melen
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: portserial.c,v 1.1 2008/03/28 15:59:07 wolti Exp $
 */

#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "UART.h"

#pragma warn_unusedarg off

#define UART_RXBUFSIZE     (64)

// Declares a queue structure for the Modbus Slave Input
OS_QUEUE ModbusSlave_InBuffer;
BRTOS_Queue *qModbusSlave_In;

OS_QUEUE ModbusSlave_OutBuffer;
BRTOS_Queue *qModbusSlave_Out;

BRTOS_Sem *ModbusSlave_SerialTXEnable;


/* ----------------------- static variables ---------------------------------*/
static CHAR ucByteRxed = 0;

/* ----------------------- Start implementation -----------------------------*/
void vMBPortSerialEnable(BOOL xRxEnable, BOOL xTxEnable)
{
	/* If xRXEnable enable serial receive interrupts. If xTxENable enable
	 * transmitter empty interrupts.
	 */
#if (defined TESTE_MODBUS && TESTE_MODBUS == 1)
	if (xTxEnable == TRUE)
	{
		OSSemPost(ModbusSlave_SerialTXEnable);		
	}
#else	
	if(xRxEnable == TRUE)
	{
		uart1_RxEnableISR();
	}else
	{
		uart1_RxDisableISR();
	}
#endif
}

BOOL xMBPortSerialInit(UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits,
		eMBParity eParity)
{

	if (OSSemCreate(0, &ModbusSlave_SerialTXEnable) != ALLOC_EVENT_OK)
	{
		while (1){};
	};

	
	if (OSQueueCreate(&ModbusSlave_InBuffer, 64, &qModbusSlave_In) != ALLOC_EVENT_OK)
	{
		while (1){};
	};
	
	if (OSQueueCreate(&ModbusSlave_OutBuffer, 64, &qModbusSlave_Out) != ALLOC_EVENT_OK)
	{
		while (1){};
	};
		
	
#if (defined TESTE_MODBUS && TESTE_MODBUS == 1)
	return TRUE;
#else	
	if (ucPORT == 1 || ucPORT == 2)
	{
		
		(void)ucDataBits;
		uart_init(ucPORT, (INT16U)ulBaudRate, UART_RXBUFSIZE, UART1_PTA1_PTA2, FALSE, 0);		
		
		return TRUE;
	}
	return FALSE;
#endif	
}

BOOL xMBPortSerialPutByte(CHAR ucByte)
{
	/* Put a byte in the UARTs transmit buffer. This function is called
	 * by the protocol stack if pxMBFrameCBTransmitterEmpty( ) has been
	 * called. */

	OSQueuePost(qModbusSlave_Out,ucByte);		
	return TRUE;
}
BOOL xMBPortSerialGetByte(CHAR * pucByte)
{
	/* Return the byte in the UARTs receive buffer. This function is called
	 * by the protocol stack after pxMBFrameCBByteReceived( ) has been called.
	 */
		
	if(OSRQueue(&ModbusSlave_InBuffer, &ucByteRxed) != READ_BUFFER_OK){
		while(1){};
	}
		
	*pucByte = ucByteRxed;
	
	return TRUE;
}

