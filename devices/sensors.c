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
#include "AppConfig.h"

#if COLDUINO
/* port of input pins */
#define SENSOR_LEVEL_INPUT_A 		PTCD_PTCD2
#define SENSOR_LEVEL_INPUT_B 		PTCD_PTCD1
#define SENSOR_LEVEL_INPUT_C 		PTCD_PTCD0

#define PRESSURE_VALVE_INPUT_A 		PTCD_PTCD3

#define INPUT_PORT_DIR		PTCDD
#define INPUT_PORT_DATA		PTCD

#elif ARDUINO

#define INPUT(PIN,x)		(((PIN) & (1<<(x))) == 1<<(x))	
#define SENSOR_LEVEL_INPUT_A 		INPUT(PINF,3)
#define SENSOR_LEVEL_INPUT_B 		INPUT(PINF,4)
#define SENSOR_LEVEL_INPUT_C 		INPUT(PINF,5)
#define SENSOR_LEVEL_INPUT_D 		
#define PRESSURE_VALVE_INPUT_A 		INPUT(PINF,2)


#define INPUT_PORT_DIR		DDRF	/* atmega2560 input dir */
#define INPUT_PORT_PUP		PORTF	/* atmega2560 input pull-up */
#define INPUT_PORT_DATA		PINF	/* atmega2560 input data */

#endif

static uint8_t sensors_init_status = FALSE;

/* TODO: sensor debug */
uint8_t sensors_read(sensor_id_t sensor_id)
{
		uint8_t val = 0;
		switch(sensor_id)
		{			
			case PRESSURE_VALVE:
				val = (uint8_t)(PRESSURE_VALVE_INPUT_A);
			break;
			case SENSOR_LEVEL:
				val = (uint8_t)(SENSOR_LEVEL_INPUT_A + SENSOR_LEVEL_INPUT_B + SENSOR_LEVEL_INPUT_C);
			break;
			default:
			break;
		}	
		return val;				
}

void sensors_init(void)
{	
	sensors_init_status = TRUE;
	INPUT_PORT_DIR = 0; // input
	INPUT_PORT_PUP = 0; // input
}

uint8_t sensors_status(void)
{
	return sensors_init_status;
}
