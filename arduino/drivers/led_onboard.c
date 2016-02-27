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
 * led_onboard.c
 *
 *  Created on: Jan 31, 2015
 *      Author: Carlos
 */

#include "hardware.h"
#include "led_onboard.h"
#include "utils.h"

#if ARDUINO
#define LED_PORT		1
#define LED_PORT_DIR	DDRH	
#define LED_PORT_DATA	PORTH
#define RED_LED_PIN			4
#define YELLOW_LED_PIN		5
#define GREEN_LED_PIN		6
#else
#define LED_PORT		0
#define LED_PORT_DIR    
#define LED_PORT_DATA
#define LED_PIN			
#endif

void led_onboard_init(void)
{
#if LED_PORT
	BITSETMASK(LED_PORT_DIR, (0b111 << 4)); // output
	BITCLEARMASK(LED_PORT_DATA, (0b111 << 4)); // turn on all the LEDs
#endif
}

int led_onboard_state(led_color_t led_color)
{
#if LED_PORT
	int state;
	switch(led_color){
		case RED_LED:
			state = (BITTEST(LED_PORT_DATA, RED_LED_PIN) ? LED_ON : LED_OFF);
			break;
		case YELLOW_LED:
			state = (BITTEST(LED_PORT_DATA, YELLOW_LED_PIN) ? LED_ON : LED_OFF);
			break;
		case GREEN_LED:
			state = (BITTEST(LED_PORT_DATA, GREEN_LED_PIN) ? LED_ON : LED_OFF);
			break;
		default:
			break;
	}
	return state;
#else
	return 0;
#endif

}
void led_onboard_on(led_color_t led_color)
{
#if LED_PORT
	switch(led_color){
		case RED_LED:
			BITCLEAR(LED_PORT_DATA,RED_LED_PIN);
			break;
		case YELLOW_LED:
			BITCLEAR(LED_PORT_DATA,YELLOW_LED_PIN);
			break;
		case GREEN_LED:
			BITCLEAR(LED_PORT_DATA,GREEN_LED_PIN);
			break;
		default:
			break;		
	}
#endif
}
void led_onboard_off(led_color_t led_color)
{
#if LED_PORT
	switch(led_color){
		case RED_LED:
			BITSET(LED_PORT_DATA,RED_LED_PIN);
			break;
		case YELLOW_LED:
			BITSET(LED_PORT_DATA,YELLOW_LED_PIN);
			break;
		case GREEN_LED:
			BITSET(LED_PORT_DATA,GREEN_LED_PIN);
			break;
		default:
			break;
	}
#endif
}
void led_onboard_toggle(led_color_t led_color)
{
#if LED_PORT
	switch(led_color){
		case RED_LED:
			BITTOGGLE(LED_PORT_DATA,RED_LED_PIN);
			break;
		case YELLOW_LED:
			BITTOGGLE(LED_PORT_DATA,YELLOW_LED_PIN);
			break;
		case GREEN_LED:
			BITTOGGLE(LED_PORT_DATA,GREEN_LED_PIN);
			break;
		default:
			break;
	}
#endif
}


