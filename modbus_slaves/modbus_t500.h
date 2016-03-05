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
 * modbus_t500.h
 *
 *  Created on: Sep 15, 2015
 *      Author: Universidade Federal
 */
 /** \addtogroup modbus
 *  @{
 */
 
 /** \defgroup t500 Slave T500
 *  @{
 */

#ifndef MODBUS_T500_H_
#define MODBUS_T500_H_

#define T500_REGLIST1_INPUT_START  2
#define T500_REGLIST2_INPUT_START  236

#define T500_REGLIST1_INPUT_NREGS  11
#define T500_REGLIST2_INPUT_NREGS  13

#define T500_SLAVE_ADDRESS  	(0x01)
#define T500_REG_OFFSET			(4)

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
	uint32_t Regs32[T500_REGLIST1_INPUT_NREGS+T500_REG_OFFSET/2];
	uint16_t Regs16[T500_REGLIST1_INPUT_NREGS*2+T500_REG_OFFSET];
	uint8_t  Regs8[T500_REGLIST1_INPUT_NREGS*4+T500_REG_OFFSET*2];
}modbus_t500_input_register_list1;


#endif /* MODBUS_T500_H_ */
/** @} */
/** @} */
