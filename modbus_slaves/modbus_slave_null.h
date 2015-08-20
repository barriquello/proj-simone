/*
 * modbus_slave_null.h
 *
 *  Created on: Aug 14, 2015
 *      Author: UFSM
 */

#ifndef MODBUS_SLAVE_NULL_H_
#define MODBUS_SLAVE_NULL_H_

#include "stdint.h"

#define NULL_REGLIST_OFFSET_NREGS 2
#define NULL_REGLIST_INPUT_NREGS  8
#define NULL_REGLIST_INPUT_START  1000
#define NULL_SLAVE_ADDRESS  	  (0x00)

typedef union 
{
	struct
	{
		uint8_t Device_id;	/* device id */
		uint8_t Hora;			/* timestamp */
		uint8_t Minuto;		/* timestamp */
		uint8_t Segundo;		/* timestamp */
		uint16_t REG0;
		uint16_t REG1;
		uint16_t REG2;
		uint16_t REG3;
		uint16_t REG4;
		uint16_t REG5;
		uint16_t REG6;
		uint16_t REG7;
	}Reg;	
	uint16_t Regs[NULL_REGLIST_INPUT_NREGS+NULL_REGLIST_OFFSET_NREGS];
	uint8_t  Regs8[NULL_REGLIST_INPUT_NREGS*2+NULL_REGLIST_OFFSET_NREGS];
}modbus_null_input_register_list;


#endif /* MODBUS_SLAVE_NULL_H_ */
