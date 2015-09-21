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
 * modbus_slaves.h
 *
 *  Created on: Aug 14, 2015
 *      Author: UFSM
 */

#ifndef MODBUS_SLAVES_H_
#define MODBUS_SLAVES_H_

#include "stdint.h"

#define MODBUS_NUM_SLAVES (4) 
typedef enum
{
	MS_NULL = 0,
	MS_PM210 = 1,
	MS_TS = 2,
	MS_T500 = 3
}slave_num_t;

#if (PLATAFORMA == ARDUINO || PLATAFORMA == WIN32)
typedef enum {
	MODBUS_NULL = 0,
	MODBUS_PM210 = 1,
	MODBUS_TS = 2,
	MODBUS_T500 = 3,
	MODBUS_NONE
}eMBSlaves;
#endif

typedef uint8_t (*_reader)(uint8_t* buf, uint8_t max_len);

typedef struct
{
	slave_num_t num;
	char* nome;
	_reader slave_reader;
}modbus_slave_t;

#endif /* MODBUS_SLAVES_H_ */
