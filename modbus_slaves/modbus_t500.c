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
 * 
 * Brief: MODBUS Slave IMS T500
 * 
 * Slave Address 1 
 * Serial comm: 8-Even-1 @ 19200 baud
 * 
 * 
 * */

#include "stdint.h"

#ifndef _WIN32
#include "BRTOS.h"
#endif

#include "AppConfig.h"
#include "modbus_t500.h"


#ifndef _WIN32

/* Input registers */
CONST	uint16_t T500_Voltage_Phase_Avg = 2; /* Volt */
CONST   uint16_t T500_Current_Phase_Avg = 10; /* Amp */
CONST	uint16_t T500_Voltage_Line_Avg = 18; /* Volt */
CONST	uint16_t T500_Total_Power_Factor_Sign = 26; /* scale ??? */
CONST	uint16_t T500_Total_Real_Power = 34; /* W*/		
CONST	uint16_t T500_Total_Reactive_Power = 42; /* VAR*/
CONST	uint16_t T500_Total_Apparent_Power = 50; /* VA */
CONST	uint16_t T500_Current_Angle_Phase_A = 58; /* deg */
CONST	uint16_t T500_Total_Power_Factor = 66; /* scale ??? */
CONST	uint16_t T500_Caract_Power_Factor = 74; /* scale ??? */
CONST	uint16_t T500_Frequency = 82; /* Hz */	

#endif


/* ----------------------- Modbus includes ----------------------------------*/
#if COLDUINO
#pragma warn_unusedarg off
#include "mb.h"
#include "mbport.h"
#endif

#include "modbus.h"
#include "modbus_slaves.h"
#include "modbus_t500.h" /* T500 device */
#include "string.h"
#include "time_lib.h"
#include "utils.h"

/* static IR list for T500 device */
static modbus_t500_input_register_list1  T500_IRList1;

#define MODBUS_SLAVE_T500_SIMULATION 	0
#if MODBUS_SLAVE_T500_SIMULATION
#include "random_lib.h"
#endif

const uint16_t T500_modbus_map_regs[] =
{
		T500_Voltage_Phase_Avg,T500_Current_Phase_Avg,T500_Voltage_Line_Avg,
		T500_Total_Power_Factor_Sign,T500_Total_Real_Power,T500_Total_Reactive_Power,
		T500_Total_Apparent_Power,T500_Current_Angle_Phase_A,T500_Total_Power_Factor,
		T500_Caract_Power_Factor,T500_Frequency
};

uint8_t t500_read_data(uint8_t slave_addr, uint8_t* buf, uint8_t max_len);

uint8_t t500_read_data(uint8_t slave_addr, uint8_t* buf, uint8_t max_len)
{
		
			uint8_t nregs = 0;	
			uint8_t retries = T500_REGLIST1_INPUT_NREGS*2;
			
			/* limit number of registers to the max. available */
			if(max_len > sizeof(modbus_t500_input_register_list1)) 
			{
				max_len = sizeof(modbus_t500_input_register_list1);
			}
			
			/* Detecta equipamentos de medição e faz a leitura dos dados */					
			/* T500 input registers */
			memset(T500_IRList1.Regs32,0x00,SIZEARRAY(T500_IRList1.Regs32));
			
			for(nregs = 0; nregs < T500_REGLIST1_INPUT_NREGS;)
			{
				
#if MODBUS_SLAVE_T500_SIMULATION			
				/* return random data */
				T500_IRList1.Regs32[nregs + (T500_REG_OFFSET/2)] = (random_get()<<16)+random_get();
#else				
				if(Modbus_GetData(slave_addr, FC_READ_INPUT_REGISTERS, (uint8_t*)&T500_IRList1.Regs32[nregs + (T500_REG_OFFSET/2)],
						T500_modbus_map_regs[nregs], 2) == MODBUS_OK)
				{
					nregs++;
				}else
				{
					if(--retries == 0)
					{
						/* zera tudo e desiste */
						memset(T500_IRList1.Regs32,0x00,SIZEARRAY(T500_IRList1.Regs32));
						break;
					}
					
				}								
#endif					
			}
			
			SetModbusHeader(slave_addr, T500_IRList1.Regs8);			
			memcpy(buf,T500_IRList1.Regs8,max_len);						
			return (max_len);
			
}

CONST modbus_slave_t slave_T500 =
{
		MS_T500,
		"T500",
		t500_read_data,
};

		
