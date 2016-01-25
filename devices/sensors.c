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
 * sensors.c
 *
 *  Created on: Aug 14, 2015
 *      Author: Universidade Federal
 */

#include "drivers.h"
#include "sensors.h"

#if COLDUINO
/* port of input pins */
#define SENSOR_LEVEL_INPUT_H 		PTCD_PTCD2
#define SENSOR_LEVEL_INPUT_H_DIR 	PTCDD_PTCDD2

#define SENSOR_LEVEL_INPUT_L 		PTCD_PTCD1
#define SENSOR_LEVEL_INPUT_L_DIR 	PTCDD_PTCDD1

#define PRESSURE_VALVE_INPUT_H 		PTCD_PTCD0
#define PRESSURE_VALVE_INPUT_H_DIR 	PTCDD_PTCDD0

#define PRESSURE_VALVE_INPUT_L 		PTCD_PTCD3
#define PRESSURE_VALVE_INPUT_L_DIR 	PTCDD_PTCDD3

#define INPUT_PORT_DIR		PTCDD
#define INPUT_PORT_DATA		PTCD

#elif ARDUINO

#define SENSOR_LEVEL_INPUT_H 		(PORTF & 0x04)
#define SENSOR_LEVEL_INPUT_L 		(PORTF & 0x02)
#define PRESSURE_VALVE_INPUT_H 		(PORTF & 0x01)
#define PRESSURE_VALVE_INPUT_L 		(PORTF & 0x08)

#define INPUT_PORT_DIR		DDRF	/* atmega2560 analog input */
#define INPUT_PORT_DATA		PORTF	/* atmega2560 analog input */

#endif

typedef enum
{
	PRESSURE_VALVE = 0,
	SENSOR_LEVEL = 1
}sensor_id_t;

uint8_t sensors_read(uint8_t sensor_id)
{
		uint8_t val = 0;
		switch(sensor_id)
		{
			case PRESSURE_VALVE:
				val = PRESSURE_VALVE_INPUT_H + PRESSURE_VALVE_INPUT_L;
			break;
			case SENSOR_LEVEL:
				val = SENSOR_LEVEL_INPUT_H;
			break;
			default:
			break;
		}	
		return val;				
}

void sensors_init(void)
{	
	INPUT_PORT_DIR = 0; // input
}

