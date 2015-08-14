/*
 * modbus_slave_null.c
 *
 *  Created on: Aug 14, 2015
 *      Author: Universidade Federal
 */


#include "modbus.h"
#include "modbus_slaves.h"
#include "modbus_slave_null.h" /* NULL device */
#include "time_lib.h"

#include "AppConfig.h"

static CONST INT16U usRegInputBuf[NULL_REGLIST_INPUT_NREGS] = 
{ 		
	0xaaaa,0xbbbb,0xcccc,0xdddd,0xeeee,0xffff,0x0001
};

static modbus_null_input_register_list NULL_IRList;

uint8_t slave_null_read_data(uint8_t* buf, uint8_t max_len);

uint8_t slave_null_read_data(uint8_t* buf, uint8_t max_len)
{
			OSTime timestamp;
			
			ModbusSetSlave(MODBUS_NULL);	/* Leitura dos dados de teste */
			
			/* Detecta equipamentos de medição e faz a leitura dos dados */					
			Modbus_GetData(NULL_SLAVE_ADDRESS, FC_READ_INPUT_REGISTERS, (INT8U*)&NULL_IRList.Regs[0], 
					NULL_REGLIST_INPUT_START, NULL_REGLIST_INPUT_NREGS);	
			
			/* Get and set timestamp of reading */			
			GetCalendarTime(&timestamp);	
			SetTimeStamp(MODBUS_NULL, (INT8U*)NULL_IRList.Regs, &timestamp);
			
			if(sizeof(NULL_IRList.Regs) < max_len)
			{
				memcpy(buf,NULL_IRList.Regs,sizeof(NULL_IRList.Regs));
				return (sizeof(NULL_IRList.Regs));
			}
			else
			{
				return 0;
			}
			
}

CONST modbus_slave_t slave_NULL =
{
		MS_NULL,
		"Null Slave",
		slave_null_read_data,
};
