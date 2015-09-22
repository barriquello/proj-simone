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
 * Brief: MODBUS Slave Schneider Electric PM-210
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
#include "modbus_pm210.h"

#ifndef _WIN32
/* Input registers */
// 10 bytes
CONST uint16_t Real_Energy_Consumption_H 			= 4000; /* kWh, scale = reg 4108 */
CONST uint16_t Real_Energy_Consumption_L 			= 4001; /* kWh, scale = reg 4108 */
CONST uint16_t Apparent_Energy_Consumption_H 		= 4002; /* kVAh, scale = reg 4108 */
CONST uint16_t Apparent_Energy_Consumption_L 		= 4003; /* kVAh, scale = reg 4108 */
CONST uint16_t Reactive_Energy_Consumption_H 		= 4004; /* kVARh, scale = reg 4108 */
CONST uint16_t Reactive_Energy_Consumption_L 		= 4005; /* kVARh, scale = reg 4108 */
CONST uint16_t Total_Real_Power 					= 4006; /* kWh, scale = reg 4107 */
CONST uint16_t Total_Apparent_Power 				= 4007; /* kVAh, scale = reg 4107 */
CONST uint16_t Total_Reactive_Power  				= 4008; /* kVARh, scale = reg 4107 */
CONST uint16_t Total_Power_Factor 				= 4009; /* scale 0.0001, 0 to 10000  */

// 10 bytes
CONST uint16_t Frequency 							 = 4013; /* Hz, scale 0.01, 4500 to 6500 */
CONST uint16_t Total_Real_Power_Present_Demand 	 = 4014; /* kWh, scale = reg 4107 */
CONST uint16_t Total_Apparent_Power_Present_Demand = 4015; /* kVAh, scale = reg 4107 */
CONST uint16_t Total_Reactive_Power_Present_Demand = 4016; /* kVARh, scale = reg 4107 */
CONST uint16_t Total_Real_Power_Max_Demand 		 = 4017; /* kWh, scale = reg 4107 */
CONST uint16_t Total_Apparent_Power_Max_Demand 	 = 4018; /* kVAh, scale = reg 4107 */
CONST uint16_t Total_Reactive_Power_Max_Demand 	 = 4019; /* kVARh, scale = reg 4107 */
CONST uint16_t Current_Instantaneous_Phase_A 		 = 4020; /* Amp, scale = reg 4105 */
CONST uint16_t Current_Instantaneous_Phase_B 		 = 4021; /* Amp, scale = reg 4105 */
CONST uint16_t Current_Instantaneous_Phase_C 		 = 4022; /* Amp, scale = reg 4105 */


// 12 bytes
CONST uint16_t Current_Present_Demand_Phase_A 	 = 4024; /* Amp, scale = reg 4105 */
CONST uint16_t Current_Present_Demand_Phase_B 	 = 4025; /* Amp, scale = reg 4105 */
CONST uint16_t Current_Present_Demand_Phase_C 	 = 4026; /* Amp, scale = reg 4105 */
CONST uint16_t Current_Max_Demand_Phase_A 		 = 4027; /* Amp, scale = reg 4105 */
CONST uint16_t Current_Max_Demand_Phase_B 		 = 4028; /* Amp, scale = reg 4105 */
CONST uint16_t Current_Max_Demand_Phase_C 		 = 4029; /* Amp, scale = reg 4105 */
CONST uint16_t Voltage_Phase_A_B 					 = 4030; /* Volt, scale = reg 4106 */
CONST uint16_t Voltage_Phase_B_C 					 = 4031; /* Volt, scale = reg 4106 */
CONST uint16_t Voltage_Phase_A_C 					 = 4032; /* Volt, scale = reg 4106 */
CONST uint16_t Voltage_Phase_A_N 					 = 4033; /* Volt, scale = reg 4106 */
CONST uint16_t Voltage_Phase_B_N 					 = 4034; /* Volt, scale = reg 4106 */
CONST uint16_t Voltage_Phase_C_N 					 = 4035; /* Volt, scale = reg 4106 */

// 4 bytes
CONST uint16_t Scale_Factor_I 					 = 4105;  /* –4 = 0.0001, –3 = 0.001, –2 = 0.01, –1 = 0.1, 0 = 1.0, 1 = 10.0, 2 = 100.0, 3 = 1000.0, 4 = 10000.0 */
CONST uint16_t Scale_Factor_V 					 = 4106;  /* –4 = 0.0001, –3 = 0.001, –2 = 0.01, –1 = 0.1, 0 = 1.0, 1 = 10.0, 2 = 100.0, 3 = 1000.0, 4 = 10000.0 */
CONST uint16_t Scale_Factor_W 					 = 4107;  /* –4 = 0.0001, –3 = 0.001, –2 = 0.01, –1 = 0.1, 0 = 1.0, 1 = 10.0, 2 = 100.0, 3 = 1000.0, 4 = 10000.0 */
CONST uint16_t Scale_Factor_E 					 = 4108;  /* –4 = 0.0001, –3 = 0.001, –2 = 0.01, –1 = 0.1, 0 = 1.0, 1 = 10.0, 2 = 100.0, 3 = 1000.0, 4 = 10000.0 */

// 1 byte
CONST uint16_t Error_Bitmap 						 = 4112;  /* bit 0: Phase A Voltage over range, bit 1: Phase B Voltage over range, bit 2: Phase C Voltage over range
						bit 3: Phase A Current over range, bit 4: Phase B Current over range, bit 5: Phase C Current over range
						bit 6: Frequency out of range, bit 7-15: Reserved for future use */

// 12 bytes
CONST uint16_t Thermal_Demand_Interval 			= 4117; /* Minutes — 1 to 60 */
CONST uint16_t Power_Block_Demand_Interval 		= 4118; /* Minutes — 1 to 60 */
CONST uint16_t Power_Block_Demand_Sub_Intervals 	= 4119; /* 0 to 60 */
CONST uint16_t CT_Ratio_Primary 					= 4120;
CONST uint16_t CT_Ratio_Secondary 				= 4121;
CONST uint16_t PT_Ratio_Primary  					= 4122;
CONST uint16_t PT_Ratio_Scale  					= 4123; /* 0,1,10,100 */
CONST uint16_t PT_Ratio_Secondary 				= 4124; /* 100,110,115,120 */
CONST uint16_t Service_Frequency 					= 4125; /* 50 or 60 Hz*/
CONST uint16_t Reset 								= 4126; /* Write 30078 to clear all Energy Accumulators. Write 21212 to reset Peak Demand values to Present Demand Values. Read always returns 0. */
CONST uint16_t System_Type 						= 4127; /* 10,11,12,30, 31, 32, 40, 42, 44 */
CONST uint16_t Units 								= 4128; /* 0 = IEC, 1 = IEEE units */

/* Holding registers */
// 7 bytes
CONST uint16_t Firmware_Version_Reset_System 		= 7000;
CONST uint16_t Firmware_Version_Operating_System 	= 7001;
CONST uint16_t Serial_Number_H 					= 7002;  /* (date/time of mfg. in UTC) */
CONST uint16_t Serial_Number_L 					= 7003;  /* (date/time of mfg. in UTC) */
CONST uint16_t Device_ID 							= 7004; /* 15201 */
CONST uint16_t Modbus_Address 					= 7005; /* 1 to 247 */
CONST uint16_t Baud_rate 							= 7006;	 /* 2400,4800,9600,19200 */

#endif

/* 
 * Supported MODBUS Commands
Command Description
0x03 Read holding registers
0x04 Read input registers
0x06 Preset single registers
0x10 Preset multiple registers
0x11 Report ID - Return String: byte 1: 0x11, byte 2: number of bytes following without crc, byte 3: ID byte = 250, byte 4: status = 0xFF
bytes 5+: ID string = PM210 Power Meter, last 2 bytes: CRC
0x2B Read device identification, BASIC implementation (0x00, 0x01, 0x02 data), conformity level 1,
Object Values, 0x01: If register 4128 is 0, then “Merlin Gerin. If register 4128 is 1, then “Square D”
0x02: “PM210”, 0x03: “Vxx.yyy” where xx.yyy is the OS version number. This is the reformatted version of
register 7001. If the value for register 7001 is 12345, then the 0x03 data would be “V12.345”
 * 
 * */

/* ----------------------- Modbus includes ----------------------------------*/
#if COLDUINO
#pragma warn_unusedarg off
#include "mb.h"
#include "mbport.h"
#endif

/* ----------------------- CONSTants ------------------------------------------*/

CONST char PM210_ID_string[] = "PM210 Power Meter";
CONST uint16_t SIZEOF_ID_STRING = sizeof(PM210_ID_string);

#include "modbus.h"
#include "modbus_slaves.h"
#include "modbus_pm210.h" /* PM210 device */
#include "string.h"
#include "time_lib.h"

/* static IR and HR list for PM210 device */
static modbus_pm210_input_register_list1  PM210_IRList1;
static modbus_pm210_input_register_list2  PM210_IRList2;
static modbus_pm210_holding_register_list PM210_HRList;

#define MODBUS_SLAVE_PM210_SIMULATION 	1
#if MODBUS_SLAVE_PM210_SIMULATION
#include "random_lib.h"
#endif

uint8_t pm210_read_data(uint8_t* buf, uint8_t max_len);

uint8_t pm210_read_data(uint8_t* buf, uint8_t max_len)
{
		  uint8_t nregs = 0;
			
#if PM200_PRESENTE
			
			OSTime timestamp;
			
			/* Detecta equipamentos de medição e faz a leitura dos dados */					
			/* PM210 input registers */		
			Modbus_GetData(PM210_SLAVE_ADDRESS, FC_READ_INPUT_REGISTERS, (uint8_t*)&PM210_IRList1.Regs[PM210_REG_OFFSET],
					PM210_REGLIST1_INPUT_START, PM210_REGLIST1_INPUT_NREGS);	

			/* Get and set timestamp of reading */			
			GetCalendarTime(&timestamp);	
			SetTimeStamp(MODBUS_PM210, (uint8_t*)PM210_IRList1.Regs, &timestamp);
			
			Modbus_GetData(PM210_SLAVE_ADDRESS, FC_READ_INPUT_REGISTERS, (uint8_t*)&PM210_IRList2.Regs[PM210_REG_OFFSET],
								PM210_REGLIST2_INPUT_START, PM210_REGLIST2_INPUT_NREGS);
			
			/* Get and set timestamp of reading */
			GetCalendarTime(&timestamp);
			SetTimeStamp(MODBUS_PM210, (uint8_t*)PM210_IRList2.Regs, &timestamp);
#else
			/* return random data */
			for(nregs = PM210_REG_OFFSET; nregs < (PM210_REGLIST1_INPUT_NREGS+PM210_REG_OFFSET);nregs++)
			{
				PM210_IRList1.Regs16[nregs] = random_get();
			}

			/* return random data */
			for(nregs = PM210_REG_OFFSET; nregs < (PM210_REGLIST2_INPUT_NREGS+PM210_REG_OFFSET);nregs++)
			{
				PM210_IRList2.Regs16[nregs] = random_get();
			}

#endif
			
#if 0
			if((sizeof(PM210_IRList1.Regs) + sizeof(PM210_IRList2.Regs)) < max_len)
			{
				memcpy(buf,PM210_IRList1.Regs,sizeof(PM210_IRList1.Regs));
				memcpy(buf + sizeof(PM210_IRList2.Regs),PM210_IRList2.Regs,sizeof(PM210_IRList2.Regs));
				return (sizeof(PM210_IRList1.Regs) + sizeof(PM210_IRList2.Regs));
			}
			else
			{
				return 0;
			}
#endif

			/* limit number of registers to the max. available */
			if(max_len > (sizeof(modbus_pm210_input_register_list1) + sizeof(modbus_pm210_input_register_list2)))
			{
				max_len = (sizeof(modbus_pm210_input_register_list1) + sizeof(modbus_pm210_input_register_list2));
			}

			memcpy(buf,PM210_IRList1.Regs8,max_len);

			if(max_len - sizeof(modbus_pm210_input_register_list1) > 0)
			{
				memcpy(buf + sizeof(PM210_IRList1.Regs8),PM210_IRList2.Regs8, max_len - sizeof(modbus_pm210_input_register_list1));
			}
			return (max_len);
			
}


CONST modbus_slave_t slave_PM210 =
{
		MS_PM210,
		"PM210",
		pm210_read_data,
};
