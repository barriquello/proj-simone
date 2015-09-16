/*
 * modbus_t500.h
 *
 *  Created on: Sep 15, 2015
 *      Author: Universidade Federal
 */

#ifndef MODBUS_T500_H_
#define MODBUS_T500_H_

#define T500_REGLIST1_INPUT_START  2
#define T500_REGLIST2_INPUT_START  236

#define T500_REGLIST1_INPUT_NREGS  11
#define T500_REGLIST2_INPUT_NREGS  13

#define T500_SLAVE_ADDRESS  	(0x01)
#define T500_REG_OFFSET			(1)

typedef union
{	
	struct
	{
		uint8_t Device_id;	/* device id */
		uint8_t Hora;			/* timestamp */
		uint8_t Minuto;		/* timestamp */
		uint8_t Segundo;		/* timestamp */
		uint32_t Voltage_Phase_Avg; /* Volt */
		uint32_t Current_Phase_Avg; /* Amp */
		uint32_t Voltage_Line_Avg; /* Volt */
		uint32_t Total_Power_Factor_Sign; /* scale ??? */
		uint32_t Total_Real_Power; /* W*/		
		uint32_t Total_Reactive_Power; /* VAR*/
		uint32_t Total_Apparent_Power; /* VA */
		uint32_t Current_Angle_Phase_A; /* deg */
		uint32_t Total_Power_Factor; /* scale ??? */
		uint32_t Caract_Power_Factor; /* scale ??? */
		uint32_t Frequency; /* Hz */		
	} Reg;	
	uint32_t Regs32[11+1];
	uint16_t Regs[11*2+2];
	uint8_t  Regs8[11*4+4];	
}modbus_t500_input_register_list1;


#endif /* MODBUS_T500_H_ */
