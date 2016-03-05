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
 * sensors.h
 *
 *  Created on: Aug 14, 2015
 *      Author: UFSM
 */

 /*! \file sensors.h
 \brief Interface para ler dados de sensores.
 
 Funcoes de leitura e escrita sao feitas por GPIO ou ADC.
 */


/*! \defgroup Devices Sensors */

/** \addtogroup Devices
 *  @{
 */
 
 
 
#ifndef SENSORS_H_
#define SENSORS_H_

#include "stdint.h"

typedef enum
{
	PRESSURE_VALVE = 0,
	SENSOR_LEVEL = 1
}sensor_id_t;

#define LEVEL_MIN (0)
#define LEVEL_MED (1)
#define LEVEL_MAX (2)

void sensors_init(void);
uint8_t sensors_status(void);
uint8_t sensors_read(sensor_id_t);
uint8_t sensors_read_all(void);

#endif /* SENSORS_H_ */
/** @}*/
