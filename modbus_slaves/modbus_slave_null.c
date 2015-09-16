/*
 * modbus_slave_null.c
 *
 *  Created on: Aug 14, 2015
 *      Author: Universidade Federal
 */

#ifndef _WIN32
#include "BRTOS.h"
#include "AppConfig.h"
#include "modbus.h"
#else
#define CONST const
#endif


#include "modbus_slaves.h"
#include "modbus_slave_null.h" /* NULL device */
#include "time_lib.h"
#include "string.h"

#if 0
static CONST uint16_t usRegInputBuf[NULL_REGLIST_INPUT_NREGS] =
{ 		
	0xaaaa,0xbbbb,0xcccc,0xdddd,0xeeee,0xffff,0x0001
};
#endif

static modbus_null_input_register_list NULL_IRList;

uint8_t slave_null_read_data(uint8_t* buf, uint8_t max_len);

#define MODBUS_NULL_SLAVE_SIMULATION	1
#if MODBUS_NULL_SLAVE_SIMULATION	
#include "random_lib.h"
#endif

uint8_t slave_null_read_data(uint8_t* buf, uint8_t max_len)
{
								
#if MODBUS_NULL_SLAVE_SIMULATION == 0	
			/* Detecta equipamentos de medição e faz a leitura dos dados */	

#else	
			uint8_t nregs = 0;
			/* return random data */	
			for(nregs = NULL_REGLIST_OFFSET_NREGS; nregs < (NULL_REGLIST_INPUT_NREGS+NULL_REGLIST_OFFSET_NREGS);nregs++)
			{				
				NULL_IRList.Regs[nregs] = random_get();
			}
#endif

#if 0
			/* get and set timestamp of reading and device id */			
			GetCalendarTime(&timestamp);	
			SetTimeStamp(MODBUS_NULL, (INT8U*)NULL_IRList.Regs, &timestamp);
#endif
			
			/* limit number of registers to the max. available */
			if(max_len > sizeof(modbus_null_input_register_list)) 
			{
				max_len = sizeof(modbus_null_input_register_list);
			}
			
			memcpy(buf,NULL_IRList.Regs,max_len);						
			return (max_len);			
}

CONST modbus_slave_t slave_NULL =
{
		MS_NULL,
		"Null Slave",
		slave_null_read_data,
};
