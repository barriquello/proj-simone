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

#define PM210_REGLIST1_INPUT_NREGS  36
#define PM210_REGLIST2_INPUT_NREGS  28
#define PM210_REGLIST_HOLDING_NREGS  8

#define PM210_SLAVE_ADDRESS  	(0xAA)
#define PM210_REG_OFFSET		(2)

typedef union
{	
	struct
	{
		INT8U Device_id;	/* device id */
		INT8U Hora;			/* timestamp */
		INT8U Minuto;		/* timestamp */
		INT8U Segundo;		/* timestamp */
		INT16U Real_Energy_Consumption_H; /* kWh, scale = reg 4108 */
		INT16U Real_Energy_Consumption_L; /* kWh, scale = reg 4108 */
		INT16U Apparent_Energy_Consumption_H; /* kVAh, scale = reg 4108 */
		INT16U Apparent_Energy_Consumption_L; /* kVAh, scale = reg 4108 */
		INT16U Reactive_Energy_Consumption_H; /* kVARh, scale = reg 4108 */
		INT16U Reactive_Energy_Consumption_L; /* kVARh, scale = reg 4108 */
		INT16U Total_Real_Power; /* kWh, scale = reg 4107 */
		INT16U Total_Apparent_Power; /* kVAh, scale = reg 4107 */
		INT16U Total_Reactive_Power; /* kVARh, scale = reg 4107 */
		INT16U Total_Power_Factor; /* scale 0.0001, 0 to 10000  */	
		INT16U Unused1; /* reg. 10  */	
		INT16U Unused2; /* reg. 11  */
		INT16U Unused3; /* reg. 12  */			
		INT16U Frequency; /* Hz, scale 0.01, 4500 to 6500 */
		INT16U Total_Real_Power_Present_Demand; /* kWh, scale = reg 4107 */
		INT16U Total_Apparent_Power_Present_Demand; /* kVAh, scale = reg 4107 */
		INT16U Total_Reactive_Power_Present_Demand; /* kVARh, scale = reg 4107 */
		INT16U Total_Real_Power_Max_Demand; /* kWh, scale = reg 4107 */
		INT16U Total_Apparent_Power_Max_Demand; /* kVAh, scale = reg 4107 */
		INT16U Total_Reactive_Power_Max_Demand; /* kVARh, scale = reg 4107 */
		INT16U Current_Instantaneous_Phase_A; /* Amp, scale = reg 4105 */
		INT16U Current_Instantaneous_Phase_B; /* Amp, scale = reg 4105 */
		INT16U Current_Instantaneous_Phase_C; /* Amp, scale = reg 4105 */
		INT16U Unused4; /* reg. 23 */
		INT16U Current_Present_Demand_Phase_A; /* Amp, scale = reg 4105 */
		INT16U Current_Present_Demand_Phase_B; /* Amp, scale = reg 4105 */
		INT16U Current_Present_Demand_Phase_C; /* Amp, scale = reg 4105 */
		INT16U Current_Max_Demand_Phase_A; /* Amp, scale = reg 4105 */
		INT16U Current_Max_Demand_Phase_B; /* Amp, scale = reg 4105 */
		INT16U Current_Max_Demand_Phase_C; /* Amp, scale = reg 4105 */
		INT16U Voltage_Phase_A_B; /* Volt, scale = reg 4106 */
		INT16U Voltage_Phase_B_C; /* Volt, scale = reg 4106 */
		INT16U Voltage_Phase_A_C; /* Volt, scale = reg 4106 */
		INT16U Voltage_Phase_A_N; /* Volt, scale = reg 4106 */
		INT16U Voltage_Phase_B_N; /* Volt, scale = reg 4106 */
		INT16U Voltage_Phase_C_N; /* Volt, scale = reg 4106 */
	} Reg;
	
	INT16U Regs[36+2]; 
	INT8U  Regs8[36*2+2];
	
}modbus_pm210_input_register_list1;


typedef union 
{
	struct
	{
		INT8U Device_id;	/* device id */
		INT8U Hora;			/* timestamp */
		INT8U Minuto;		/* timestamp */
		INT8U Segundo;		/* timestamp */
		INT16U Scale_Factor_I;  /* –4 = 0.0001, –3 = 0.001, –2 = 0.01, –1 = 0.1, 0 = 1.0, 1 = 10.0, 2 = 100.0, 3 = 1000.0, 4 = 10000.0 */
		INT16U Scale_Factor_V;  /* –4 = 0.0001, –3 = 0.001, –2 = 0.01, –1 = 0.1, 0 = 1.0, 1 = 10.0, 2 = 100.0, 3 = 1000.0, 4 = 10000.0 */
		INT16U Scale_Factor_W;  /* –4 = 0.0001, –3 = 0.001, –2 = 0.01, –1 = 0.1, 0 = 1.0, 1 = 10.0, 2 = 100.0, 3 = 1000.0, 4 = 10000.0 */
		INT16U Scale_Factor_E;  /* –4 = 0.0001, –3 = 0.001, –2 = 0.01, –1 = 0.1, 0 = 1.0, 1 = 10.0, 2 = 100.0, 3 = 1000.0, 4 = 10000.0 */
		INT16U Unused1;
		INT16U Unused2;
		INT16U Unused3;
		INT16U Error_Bitmap;  /* */
		INT16U offset[4];
		INT16U Thermal_Demand_Interval; /* Minutes — 1 to 60 */ 
		INT16U Power_Block_Demand_Interval; /* Minutes — 1 to 60 */
		INT16U Power_Block_Demand_Sub_Intervals; /* 0 to 60 */
		INT16U CT_Ratio_Primary;
		INT16U CT_Ratio_Secondary;
		INT16U PT_Ratio_Primary;
		INT16U PT_Ratio_Scale; /* 0,1,10,100 */
		INT16U PT_Ratio_Secondary; /* 100,110,115,120 */
		INT16U Service_Frequency; /* 50 or 60 Hz*/
		INT16U Reset; /* Write 30078 to clear all Energy Accumulators. Write 21212 to reset Peak Demand values to Present Demand Values. Read always returns 0. */
		INT16U System_Type; /* 10, 11, 12, 30, 31, 32, 40, 42, 44 */
		INT16U Units; /* 0 = IEC, 1 = IEEE units */
	}Reg;	
	INT16U Regs[24+2]; 
	INT8U  Regs8[24*2+2];
}modbus_pm210_input_register_list2;

typedef union 
{
	struct
	{
		INT8U Firmware_Version_Reset_System;
		INT8U Firmware_Version_Operating_System;
		INT8U Serial_Number_H;  /* (date/time of mfg. in UTC) */
		INT8U Serial_Number_L;  /* (date/time of mfg. in UTC) */
		INT8U Device_ID; /* 15201 */
		INT8U Modbus_Address; /* 1 to 247 */
		INT8U Baud_rate;	 /* 2400,4800,9600,19200 */
		INT8U Unused;	 /* */
	} Reg;
	INT8U Regs[8];
}modbus_pm210_holding_register_list;


#endif /* MPDBUS_PM210_H_ */
