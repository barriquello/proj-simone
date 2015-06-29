#include "BRTOS.h"
#include "drivers.h"
#include "tasks.h"
#include "AppConfig.h"

#include "modbus.h" /* master lib */

#if TESTE_MODBUS

// Declares a queue structure for the Modbus Master Input
OS_QUEUE ModbusMaster_InBuffer;
BRTOS_Queue *qModbusMaster_In;
static uint8_t ModbusMaster_state;


#if (defined ENABLE_MASTER_UART && ENABLE_MASTER_UART==1)
#define MODBUSMASTER_PUTCHAR(x) putchar_uart2(x)
#else
#include "mb.h"
#include "mbport.h"
extern OS_QUEUE ModbusSlave_InBuffer;
#define MODBUSMASTER_PUTCHAR(x) OSWQueue(&ModbusSlave_InBuffer,(x)); pxMBFrameCBByteReceived();
#endif

static void ModbusMasterTxData(const uint8_t * const _pData, const uint32_t _dataLen) 
{
	 uint8_t k; 
	 for(k=0; k<_dataLen; k++) {
		 MODBUSMASTER_PUTCHAR(*(_pData+k));		        
	 }
}

#define QUERY_BUFSIZE 	(8)
#define ANSWER_BUFSIZE (36*2 + 8)

uint8_t queryBuffer[QUERY_BUFSIZE];
uint8_t answerBuffer[ANSWER_BUFSIZE];

#include "modbus_pm210.h"

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
    	    	    	    	
    	if (ModbusMaster_open(PM210_SLAVE_ADDRESS, FC_REPORT_SLAVE_ID, queryBuffer, &master_query) == MODBUS_OK)
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
					if(OSQueuePend(qModbusMaster_In,&ucByteRx, 1000) != TIMEOUT)
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
		                    
						}while(OSQueuePend(qModbusMaster_In,&ucByteRx, 10) != TIMEOUT);
					}
				}
			}
			
			ModbusMaster_close();
    	}
    	DelayTask(1000);
    }
}



/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"


uint8_t Modbus_init(void) 
{

	if(qModbusMaster_In != NULL && qModbusMaster_In->OSEventAllocated == TRUE) return TRUE;
	
	if (OSQueueCreate(&ModbusMaster_InBuffer, MASTER_BUFSIZE, &qModbusMaster_In) != ALLOC_EVENT_OK)
	{
		return FALSE;
	}
	
	return TRUE;
}

/* function to read data for logging */
sint32_t Modbus_GetData(INT8U slave, INT8U func, INT8U *data_ptr, INT16U start_address, INT8U num_regs)
{

	static __MB_QUERY 	   master_query; 	// control block for master query			
	static __MB_QUERY_SEND cmd; 			// command = query  + answer
	CHAR  ucByteRx;							// received byte	
	
	sint32_t err = MODBUS_OK;
	
	// open Modbus Master
	if (ModbusMaster_open(slave, func, queryBuffer, &master_query) == MODBUS_ERROR)
	{
		goto error_exit;
	}
	
	// set Master receive buffer 
	if(Modbus_prepare_receiver(&(cmd.answ), answerBuffer) == MODBUS_ERROR)
	{
		goto error_exit;
	}
	
	// set query command 
	cmd.query.addr = start_address;
	cmd.query.value = num_regs;
	cmd.query.pData = NULL;
	
	err = Modbus_make_query(&(cmd.query));	
	if (err < 0 || err >=  ANSWER_BUFSIZE)
	{
		goto error_exit;
	}
	
	// Send query
	ModbusMasterTxData(master_query.pQuery, master_query.queryLen);	
	    	
	/* wait 1 sec for the response */
	if(OSQueuePend(qModbusMaster_In,&ucByteRx, 1000) != TIMEOUT)
	{
		do
		{							
			err = Modbus_receive(ucByteRx);
			if (err < 0) {
				goto error_exit;
			}
			else if (err == 0) {
				err = Modbus_process_answ(data_ptr,num_regs);
				if (err != MB_MASTER_ERR_OK)
				{
					goto error_exit;
				}
				goto success_exit;				
			}
			
		}while(OSQueuePend(qModbusMaster_In,&ucByteRx, 10) != TIMEOUT);		
	}
	
	error_exit:	
		ModbusMaster_close();
		return MODBUS_ERROR;
		
	success_exit:
		ModbusMaster_close();
		return MODBUS_OK;
	
}

void Modbus_SlaveSelect(eMBSlaves slave_option)
{
	ModbusSetSlave(slave_option);
}

#endif
