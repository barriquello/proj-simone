/*
 * modbus_slaves.h
 *
 *  Created on: Aug 14, 2015
 *      Author: UFSM
 */

#ifndef MODBUS_SLAVES_H_
#define MODBUS_SLAVES_H_

#define NUM_MODBUS_SLAVES (3) 
typedef enum
{
	MS_NULL = 0,
	MS_PM210 = 1,
	MS_TS = 2	
}slave_num_t;

typedef uint8_t (*data_reader)(uint8_t* buf, uint8_t max_len);

typedef struct
{
	slave_num_t num;
	char* nome;
	data_reader slave_reader;
}modbus_slave_t;

#endif /* MODBUS_SLAVES_H_ */
