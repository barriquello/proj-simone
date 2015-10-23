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
#ifndef _WIN32
#include "BRTOS.h"
#include "drivers.h"
#include "tasks.h"
#endif

#include "AppConfig.h"
#include "modbus.h" /* master lib */

static uint8_t ModbusMaster_state;

#define MB_RS485	1

#if MB_RS485
#include "rs485.h"
#define RS485_BAUDRATE			19200
#define MODBUSMASTER_PUTCHAR(x) rs485_putchar(x)
#define RS485_TIMEOUT_RX		10
#else
// Declares a queue structure for the Modbus Master Input
OS_QUEUE ModbusMaster_InBuffer;
BRTOS_Queue *qModbusMaster_In;
#define MODBUSMASTER_PUTCHAR(x)
#define RS485_TIMEOUT_RX		10
#endif

static uint8_t ModbusMasterRxData(uint8_t * _pData, uint16_t timeout) 
{
	 
#if MB_RS485	
	return rs485_rx((CHAR8*)_pData, timeout);
#else
	return (uint8_t)(OSQueuePend(qModbusMaster_In,_pData, timeout) != TIMEOUT);	
#endif
}


static void ModbusMasterTxData(const uint8_t * const _pData, const uint32_t _dataLen) 
{
	 
#if MB_RS485	
	rs485_tx(_pData,(uint16_t)_dataLen);	 
#else
	uint8_t k; 
	 for(k=0; k<_dataLen; k++) {
		 MODBUSMASTER_PUTCHAR(*(_pData+k));		        
	 }
#endif
}

static void ModbusMasterRxFlush(void)
{
	#if MB_RS485		
		rs485_rx_flush();
	#endif	
}

#define QUERY_BUFSIZE 	(8)
#define ANSWER_BUFSIZE (36*2 + 8)

uint8_t queryBuffer[QUERY_BUFSIZE];
uint8_t answerBuffer[ANSWER_BUFSIZE];

#include "modbus_slaves.h"
#include "modbus_slave_null.h"

//==============================================================================
// Task: Task_modbus_master_test()
//==============================================================================
void Task_modbus_master_test(void) 
{	

	static __MB_QUERY 	   master_query; // control block for master query			
	static __MB_QUERY_SEND cmd; 	// command = query  + answer
	
	CHAR ucByteRx;	
	sint32_t err;
	
	Modbus_init();
	
	DelayTask(2000);
	
    while (1) 
    {
    	    	    	    	
    	if (ModbusMaster_open(NULL_SLAVE_ADDRESS, FC_REPORT_SLAVE_ID, queryBuffer, &master_query) == MODBUS_OK)
    	{
    	
    		// set Master receive buffer 
    		err = Modbus_prepare_receiver(&(cmd.answ), answerBuffer);
    		
    		if (err == MODBUS_ERROR){ continue; } // error handling 
									
			// set query
			cmd.query.addr = 0;
			cmd.query.value = 1;
			cmd.query.pData = NULL;
						
			// Make query
			err = Modbus_make_query(&(cmd.query));
	
			if (err < 0) 
			{
				// error handling
				continue;
			}
			else 
			{
				// check if we have enough space for answer
				if (err <= ANSWER_BUFSIZE) 
				{
					
					// Send query
					ModbusMasterTxData(master_query.pQuery, master_query.queryLen);												
								
					/* wait 1 sec for the response */
					if(ModbusMasterRxData(&ucByteRx,RS485_TIMEOUT_RX))
					{
						do
						{							
							err = Modbus_receive(ucByteRx);

							if (err < 0) {
								break;
							}
							else if (err == 0) {
								err = Modbus_process_answ(NULL,0);
								break;
							}
		                    
						}while(ModbusMasterRxData(&ucByteRx,RS485_TIMEOUT_RX));
					}
				}
			}
			
			ModbusMaster_close();
    	}
    	DelayTask(1000);
    }
}



/* ----------------------- Modbus includes ----------------------------------*/
uint8_t Modbus_init(void) 
{

#if MB_RS485 
	rs485_init(RS485_BAUDRATE,FALSE,0);	
#else	
	if(qModbusMaster_In != NULL && qModbusMaster_In->OSEventAllocated == TRUE) return TRUE;
		
	if (OSQueueCreate(&ModbusMaster_InBuffer, MASTER_BUFSIZE, &qModbusMaster_In) != ALLOC_EVENT_OK)
	{
		return FALSE;
	}
#endif
	return TRUE;
	
}

/* function to read data for logging */
sint32_t Modbus_GetData(INT8U slave, INT8U func, INT8U *data_ptr, INT16U start_address, INT8U num_regs)
{

	static __MB_QUERY 	   master_query; 	// control block for master query			
	static __MB_QUERY_SEND cmd; 			// command = query  + answer
	CHAR  ucByteRx;							// received byte	
	
	sint32_t err = MODBUS_ERROR;
	
	// open Modbus Master
	if (ModbusMaster_open(slave, func, queryBuffer, &master_query) == MODBUS_ERROR)
	{
		goto exit;
	}
	
	// set Master receive buffer 
	if(Modbus_prepare_receiver(&(cmd.answ), answerBuffer) == MODBUS_ERROR)
	{
		goto exit;
	}
	
	// set query command 
	cmd.query.addr = start_address;
	cmd.query.value = num_regs;
	cmd.query.pData = NULL;
	
	err = Modbus_make_query(&(cmd.query));	
	if (err < 0 || err >=  ANSWER_BUFSIZE)
	{
		err = MODBUS_ERROR;
		goto exit;
	}
	
	// Send query
	ModbusMasterTxData(master_query.pQuery, master_query.queryLen);	
	   
	/* wait 1 sec for the response */
	DelayTask(10);	
	
	if(ModbusMasterRxData((uint8_t*)&ucByteRx,RS485_TIMEOUT_RX))
	{
		do
		{							
			err = Modbus_receive(ucByteRx);
			if (err < 0) {
				err = MODBUS_ERROR;
				goto exit;
			}
			else if (err == 0) {
				err = Modbus_process_answ(data_ptr,num_regs);
				if(err == MB_MASTER_ERR_OK)
				{
					err = MODBUS_OK;
				}else
				{
					err = MODBUS_ERROR;
				}
				break;		
			}			
		}while(ModbusMasterRxData((uint8_t*)&ucByteRx,RS485_TIMEOUT_RX));		
	}
	
	exit:
	ModbusMaster_close();
	ModbusMasterRxFlush();				
	return err;
}

