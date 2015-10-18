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

#include "drivers.h"
#include "modbus_slaves.h"
#include "modbus_slave_null.h" /* NULL device */
#include "time_lib.h"
#include "string.h"

static modbus_null_input_register_list NULL_IRList;

uint8_t slave_null_read_data(uint8_t slave_addr, uint8_t* buf, uint8_t max_len);

#define MODBUS_NULL_SLAVE_SIMULATION	1
#if MODBUS_NULL_SLAVE_SIMULATION	
#include "random_lib.h"
#endif

#if COLDUINO
/* port of input pins */
#define SENSOR_LEVEL_INPUT_H 		PTCD_PTCD2
#define SENSOR_LEVEL_INPUT_H_DIR 	PTCDD_PTCDD2

#define SENSOR_LEVEL_INPUT_L 		PTCD_PTCD1
#define SENSOR_LEVEL_INPUT_L_DIR 	PTCDD_PTCDD1

#define PRESSURE_VALVE_INPUT_H 		PTCD_PTCD0
#define PRESSURE_VALVE_INPUT_H_DIR 	PTCDD_PTCDD0

#define PRESSURE_VALVE_INPUT_L 		PTCD_PTCD3
#define PRESSURE_VALVE_INPUT_L_DIR 	PTCDD_PTCDD3

#define INPUT_PORT_DIR		PTCDD
#define INPUT_PORT_DATA		PTCD

#elif ARDUINO

#define INPUT_PORT_DIR		0 /* definir */
#define INPUT_PORT_DATA		0 /* definir */

#endif

uint8_t slave_null_read_data(uint8_t slave_addr, uint8_t* buf, uint8_t max_len)
{
		
#if MODBUS_NULL_SLAVE_SIMULATION == 0				
			/* Detecta equipamentos de medição e faz a leitura dos dados */	
			NULL_IRList.Reg.Core_Temp = AD_get_core_temp();
			NULL_IRList.Reg.Pressure_Valve_H = PRESSURE_VALVE_INPUT_H;
			NULL_IRList.Reg.Pressure_Valve_L = PRESSURE_VALVE_INPUT_L;
			NULL_IRList.Reg.Oil_Level_H = SENSOR_LEVEL_INPUT_H;
			NULL_IRList.Reg.Oil_Level_L = SENSOR_LEVEL_INPUT_L;
#else	
			uint8_t nregs = 0;
			/* return random data */	
			for(nregs = NULL_REGLIST_OFFSET_NREGS; nregs < (NULL_REGLIST_INPUT_NREGS+NULL_REGLIST_OFFSET_NREGS);nregs++)
			{				
				NULL_IRList.Regs16[nregs] = random_get();
			}
#endif

		
			/* get and set timestamp of reading and device id */
			SetModbusHeader(slave_addr, NULL_IRList.Regs8);
			
			/* limit number of registers to the max. available */
			if(max_len > sizeof(modbus_null_input_register_list)) 
			{
				max_len = sizeof(modbus_null_input_register_list);
			}
			
			memcpy(buf,NULL_IRList.Regs8,max_len);						
			return (max_len);			
}

CONST modbus_slave_t slave_NULL =
{
		MS_NULL,
		"Null Slave",
		slave_null_read_data,
};


void Modus_slave_null_init(void)
{
	
	#if COLDUINO
		ADSetup(NormalPower, HighSpeed, ShortSampleTime, 20, 12);
	#endif
	
#if 0	
	SENSOR_LEVEL_INPUT_H_DIR = 1;
	SENSOR_LEVEL_INPUT_L_DIR = 1;
	PRESSURE_VALVE_INPUT_H_DIR = 1;
	PRESSURE_VALVE_INPUT_L_DIR = 1;	
#else
	INPUT_PORT_DIR = 0; // input
#endif
}

#ifndef _WIN32

uint8_t SetTimeStamp (uint8_t device_id, uint8_t *data_ptr, OSTime *timestamp)
{
	
	if(timestamp == NULL) return FALSE;
	
	data_ptr[0] = device_id;
	data_ptr[1] = timestamp->RTC_Hour;
	data_ptr[2] = timestamp->RTC_Minute;
	data_ptr[3] = timestamp->RTC_Second;
	
	return TRUE;
}

uint8_t SetModbusHeader (uint8_t device_id, uint8_t *data_ptr)
{
	/* Get and set timestamp of reading */
	OSDateTime timestamp;
	GetDateTime(&timestamp);
	
	data_ptr[0] = device_id;
	data_ptr[1] = INPUT_PORT_DATA;
	data_ptr[2] = (uint8_t)(timestamp.date.RTC_Year);
	data_ptr[3] = timestamp.date.RTC_Month;
	data_ptr[4] = timestamp.date.RTC_Day;
	data_ptr[5] = timestamp.time.RTC_Hour;
	data_ptr[6] = timestamp.time.RTC_Minute;
	data_ptr[7] = timestamp.time.RTC_Second;
	
	return TRUE;
}
#endif
