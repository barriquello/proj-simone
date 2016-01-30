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
 * modbus_pm210.h
 *
 *  Created on: Jan 30, 2015
 *      Author: Carlos
 */

#ifndef MODBUS_PM210_H_
#define MODBUS_PM210_H_

#define PM210_REGLIST1_INPUT_START  4000
#define PM210_REGLIST2_INPUT_START  4105
#define PM210_REGLIST_HOLDING_START  7000

#define PM210_REGLIST1_INPUT_NREGS  (36)
#define PM210_REGLIST2_INPUT_NREGS  13
#define PM210_REGLIST_HOLDING_NREGS  7

#define PM210_SLAVE_ADDRESS  	(0xAA)
#define PM210_REG_OFFSET		(4)

typedef union
{	
	struct
	{
		uint8_t Device_id;		/* device id */
		uint8_t Entradas;		/* entradas locais */
		uint8_t Ano;			/* timestamp */
		uint8_t Mes;			/* timestamp */
		uint8_t Dia;			/* timestamp */
		uint8_t Hora;			/* timestamp */
		uint8_t Minuto;			/* timestamp */
		uint8_t Segundo;		/* timestamp */	
		uint16_t Real_Energy_Consumption_H; /* kWh, scale = reg 4108 */
		uint16_t Real_Energy_Consumption_L; /* kWh, scale = reg 4108 */
		uint16_t Apparent_Energy_Consumption_H; /* kVAh, scale = reg 4108 */
		uint16_t Apparent_Energy_Consumption_L; /* kVAh, scale = reg 4108 */
		uint16_t Reactive_Energy_Consumption_H; /* kVARh, scale = reg 4108 */
		uint16_t Reactive_Energy_Consumption_L; /* kVARh, scale = reg 4108 */
		uint16_t Total_Real_Power; /* kWh, scale = reg 4107 */
		uint16_t Total_Apparent_Power; /* kVAh, scale = reg 4107 */
		uint16_t Total_Reactive_Power; /* kVARh, scale = reg 4107 */
		uint16_t Total_Power_Factor; /* scale 0.0001, 0 to 10000  */
		//uint16_t Unused1; /* reg. 10  */
		//uint16_t Unused2; /* reg. 11  */
		//uint16_t Unused3; /* reg. 12  */
		uint16_t Frequency; /* Hz, scale 0.01, 4500 to 6500 */
		uint16_t Total_Real_Power_Present_Demand; /* kWh, scale = reg 4107 */
		uint16_t Total_Apparent_Power_Present_Demand; /* kVAh, scale = reg 4107 */
		uint16_t Total_Reactive_Power_Present_Demand; /* kVARh, scale = reg 4107 */
		uint16_t Total_Real_Power_Max_Demand; /* kWh, scale = reg 4107 */
		uint16_t Total_Apparent_Power_Max_Demand; /* kVAh, scale = reg 4107 */
		uint16_t Total_Reactive_Power_Max_Demand; /* kVARh, scale = reg 4107 */
		uint16_t Current_Instantaneous_Phase_A; /* Amp, scale = reg 4105 */
		uint16_t Current_Instantaneous_Phase_B; /* Amp, scale = reg 4105 */
		uint16_t Current_Instantaneous_Phase_C; /* Amp, scale = reg 4105 */
		//uint16_t Unused4; /* reg. 23 */
		uint16_t Current_Present_Demand_Phase_A; /* Amp, scale = reg 4105 */
		uint16_t Current_Present_Demand_Phase_B; /* Amp, scale = reg 4105 */
		uint16_t Current_Present_Demand_Phase_C; /* Amp, scale = reg 4105 */
		uint16_t Current_Max_Demand_Phase_A; /* Amp, scale = reg 4105 */
		uint16_t Current_Max_Demand_Phase_B; /* Amp, scale = reg 4105 */
		uint16_t Current_Max_Demand_Phase_C; /* Amp, scale = reg 4105 */
		uint16_t Voltage_Phase_A_B; /* Volt, scale = reg 4106 */
		uint16_t Voltage_Phase_B_C; /* Volt, scale = reg 4106 */
		uint16_t Voltage_Phase_C_A; /* Volt, scale = reg 4106 */
		uint16_t Voltage_Phase_A_N; /* Volt, scale = reg 4106 */
		uint16_t Voltage_Phase_B_N; /* Volt, scale = reg 4106 */
		uint16_t Voltage_Phase_C_N; /* Volt, scale = reg 4106 */
		uint16_t Scale_Factor_I;  /* –4 = 0.0001, –3 = 0.001, –2 = 0.01, –1 = 0.1, 0 = 1.0, 1 = 10.0, 2 = 100.0, 3 = 1000.0, 4 = 10000.0 */
		uint16_t Scale_Factor_V;  /* –4 = 0.0001, –3 = 0.001, –2 = 0.01, –1 = 0.1, 0 = 1.0, 1 = 10.0, 2 = 100.0, 3 = 1000.0, 4 = 10000.0 */
		uint16_t Scale_Factor_W;  /* –4 = 0.0001, –3 = 0.001, –2 = 0.01, –1 = 0.1, 0 = 1.0, 1 = 10.0, 2 = 100.0, 3 = 1000.0, 4 = 10000.0 */
		uint16_t Scale_Factor_E;  /* –4 = 0.0001, –3 = 0.001, –2 = 0.01, –1 = 0.1, 0 = 1.0, 1 = 10.0, 2 = 100.0, 3 = 1000.0, 4 = 10000.0 */
	} Reg;
	
	uint8_t  Regs8[PM210_REGLIST1_INPUT_NREGS*2+PM210_REG_OFFSET*2];
	uint16_t Regs16[PM210_REGLIST1_INPUT_NREGS+PM210_REG_OFFSET];
	uint32_t Regs32[PM210_REGLIST1_INPUT_NREGS/2+PM210_REG_OFFSET/2];
	
}modbus_pm210_input_register_list1;


typedef union 
{
	struct
	{
		uint8_t Device_id;		/* device id */
		uint8_t Entradas;		/* entradas locais */
		uint8_t Ano;			/* timestamp */
		uint8_t Mes;			/* timestamp */
		uint8_t Dia;			/* timestamp */
		uint8_t Hora;			/* timestamp */
		uint8_t Minuto;			/* timestamp */
		uint8_t Segundo;		/* timestamp */			
		//uint16_t Unused1;
		//uint16_t Unused2;
		//uint16_t Unused3;
		uint16_t Error_Bitmap;  /* */
		//uint16_t offset[4];
		uint16_t Thermal_Demand_Interval; /* Minutes - 1 to 60 */
		uint16_t Power_Block_Demand_Interval; /* Minutes - 1 to 60 */
		uint16_t Power_Block_Demand_Sub_Intervals; /* 0 to 60 */
		uint16_t CT_Ratio_Primary;
		uint16_t CT_Ratio_Secondary;
		uint16_t PT_Ratio_Primary;
		uint16_t PT_Ratio_Scale; /* 0,1,10,100 */
		uint16_t PT_Ratio_Secondary; /* 100,110,115,120 */
		uint16_t Service_Frequency; /* 50 or 60 Hz*/
		uint16_t Reset; /* Write 30078 to clear all Energy Accumulators. Write 21212 to reset Peak Demand values to Present Demand Values. Read always returns 0. */
		uint16_t System_Type; /* 10, 11, 12, 30, 31, 32, 40, 42, 44 */
		uint16_t Units; /* 0 = IEC, 1 = IEEE units */
	}Reg;		
	uint8_t  Regs8[PM210_REGLIST2_INPUT_NREGS*2+PM210_REG_OFFSET*2];
	uint16_t Regs16[PM210_REGLIST2_INPUT_NREGS+PM210_REG_OFFSET];
	uint32_t Regs32[PM210_REGLIST2_INPUT_NREGS/2+PM210_REG_OFFSET/2];
}modbus_pm210_input_register_list2;

typedef union 
{
	struct
	{
		uint16_t Firmware_Version_Reset_System;
		uint16_t Firmware_Version_Operating_System;
		uint16_t Serial_Number_H;  /* (date/time of mfg. in UTC) */
		uint16_t Serial_Number_L;  /* (date/time of mfg. in UTC) */
		uint16_t Device_ID; /* 15201 */
		uint16_t Modbus_Address; /* 1 to 247 */
		uint16_t Baud_rate;	 /* 2400,4800,9600,19200 */
		//uint16_t Unused;	 /* */
	} Reg;
	uint8_t Regs8[PM210_REGLIST_HOLDING_NREGS*2];
	uint16_t Regs16[PM210_REGLIST_HOLDING_NREGS];
	uint32_t Regs32[PM210_REGLIST_HOLDING_NREGS/2];
}modbus_pm210_holding_register_list;


#endif /* MPDBUS_PM210_H_ */
