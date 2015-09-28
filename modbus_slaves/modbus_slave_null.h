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
 * modbus_slave_null.h
 *
 *  Created on: Aug 14, 2015
 *      Author: UFSM
 */

#ifndef MODBUS_SLAVE_NULL_H_
#define MODBUS_SLAVE_NULL_H_

#include "stdint.h"

#define NULL_REGLIST_OFFSET_NREGS 4
#define NULL_REGLIST_INPUT_NREGS  3
#define NULL_REGLIST_INPUT_START  0
#define NULL_SLAVE_ADDRESS  	  (0x00)

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
		uint16_t Core_Temp;
		uint8_t Pressure_Valve_H;
		uint8_t Pressure_Valve_L;
		uint8_t Oil_Level_H;
		uint8_t Oil_Level_L;
	}Reg;		
	uint8_t  Regs8[NULL_REGLIST_INPUT_NREGS*2+NULL_REGLIST_OFFSET_NREGS*2];
	uint16_t Regs16[NULL_REGLIST_INPUT_NREGS+NULL_REGLIST_OFFSET_NREGS];
	uint32_t Regs32[NULL_REGLIST_INPUT_NREGS/2+NULL_REGLIST_OFFSET_NREGS/2];
}modbus_null_input_register_list;


void Modus_slave_null_init(void);

#endif /* MODBUS_SLAVE_NULL_H_ */
