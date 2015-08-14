/*
 * modbus_slave_null.h
 *
 *  Created on: Aug 14, 2015
 *      Author: UFSM
 */

#ifndef MODBUS_SLAVE_NULL_H_
#define MODBUS_SLAVE_NULL_H_

#define NULL_REGLIST_INPUT_NREGS  8
#define NULL_REGLIST_INPUT_START  1000
#define NULL_SLAVE_ADDRESS  	  (0x00)

typedef union 
{
	struct
	{
		INT8U Device_id;	/* device id */
		INT8U Hora;			/* timestamp */
		INT8U Minuto;		/* timestamp */
		INT8U Segundo;		/* timestamp */
		INT16U REG0;
		INT16U REG1;
		INT16U REG2;
		INT16U REG3;
		INT16U REG4;
		INT16U REG5;
		INT16U REG6;
		INT16U REG7;
	}Reg;	
	INT16U Regs[8+2]; 
	INT8U  Regs8[8*2+2];
}modbus_null_input_register_list;


#endif /* MODBUS_SLAVE_NULL_H_ */
