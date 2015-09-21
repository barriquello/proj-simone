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
#include "BRTOS.h"
#include "drivers.h"
#include "tasks.h"
#include "AppConfig.h"

#if (defined TESTE_MODBUS && TESTE_MODBUS == 1)

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- Defines ------------------------------------------*/
#define SLAVE_PORT 		(0) 	// serial port is disabled
#define SLAVE_ID   		(250)   // ID byte PM210
#define SLAVE_ADDRESS   (0xAA)

#if (defined TESTE_MODBUS_SLAVE && TESTE_MODBUS_SLAVE == 1)

// slave addr, fn code, data address, num of regs, crc
//CHAR frame_test[] = {SLAVE_ADDRESS, MB_FUNC_READ_INPUT_REGISTER, 0x00,0x00,0x00,0x01,0x00,0x00};
CHAR frame_test[] = {SLAVE_ADDRESS, MB_FUNC_OTHER_REPORT_SLAVEID, 0x00,0x00};

#include "crc16.h"
#endif


void Task_modbus_slave_test(void)
{
	
#if (defined TESTE_MODBUS_SLAVE && TESTE_MODBUS_SLAVE == 1)	
	#define LEN (sizeof(frame_test))
	static char count = 0;
	static INT16U crc; 
	crc = ModbusCrc16(frame_test,LEN-2);
	frame_test[LEN-1] = (INT8U)((crc >> 8) & 0xFF);
	frame_test[LEN-2] = (INT8U)(crc & 0xFF);
		
#endif
	
	DelayTask(2000); // wait Modbus stack init
	
	for(;;)
	{

#if (defined TESTE_MODBUS_SLAVE && TESTE_MODBUS_SLAVE == 1)		
		while(1)
		{
			extern OS_QUEUE ModbusSlave_InBuffer;
			
			OSWQueue(&ModbusSlave_InBuffer, frame_test[count]);	 			
			pxMBFrameCBByteReceived();
			
			if (++count == LEN) 
			{
				count = 0;
				break;
			}
		}
		
		DelayTask(100);

#endif
		
		extern BRTOS_Sem *ModbusSlave_SerialTXEnable;

		OSSemPend(ModbusSlave_SerialTXEnable,0);
		
		while(1)
		{
			extern OS_QUEUE ModbusSlave_OutBuffer;
			extern BRTOS_Queue *qModbusSlave_Out;
			
			CHAR ucByteTx;
			
			pxMBFrameCBTransmitterEmpty();
			if(OSQueuePend(qModbusSlave_Out,&ucByteTx, 10) == TIMEOUT)
			{
				break; // frame sent
			}else
			{
				#if (defined TESTE_MODBUS_SLAVE && TESTE_MODBUS_SLAVE == 0)
					extern BRTOS_Queue * qModbusMaster_In;
					
					if(OSQueuePost(qModbusMaster_In, ucByteTx) != WRITE_BUFFER_OK)
					{
						// error handling
					}
				#endif	
			}			
		}	
#if (defined TESTE_MODBUS_SLAVE && TESTE_MODBUS_SLAVE == 1)		
		DelayTask(1000); // 1 frame every 1 sec
#endif
		
	}

}

void Task_modbus_slave(void)
{
	xMBPortTimersInit(20);
	vMBPortTimersEnable( );

	const UCHAR ucSlaveID[] = {SLAVE_ID};
	
	eMBErrorCode eStatus;
	eStatus = eMBInit(MB_RTU, SLAVE_ADDRESS, SLAVE_PORT, 38400, MB_PAR_EVEN);

	extern const UCHAR PM210_ID_string[];
	extern const USHORT SIZEOF_ID_STRING;
	eStatus = eMBSetSlaveID((UCHAR)SLAVE_ID, (BOOL) TRUE, PM210_ID_string, SIZEOF_ID_STRING);

	/* Enable the Modbus Protocol Stack. */
	eStatus = eMBEnable();

	for (;;)
	{	
		(void) eMBPoll();

		/* Here we simply count the number of poll cycles. */
		//usRegInputBuf[0]++;
	}
}

#endif
