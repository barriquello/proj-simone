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
	return (BITTEST(LED_PORT_DATA, led_color) ? LED_OFF : LED_ON);
#else
	return 0;
#endif

}
void led_onboard_on(led_color_t led_color)
{
#if LED_PORT
	BITCLEAR(LED_PORT_DATA, led_color);
#endif
}
void led_onboard_off(led_color_t led_color)
{
#if LED_PORT
	BITSET(LED_PORT_DATA, led_color);
#endif
}
void led_onboard_toggle(led_color_t led_color)
{
#if LED_PORT
	BITTOGGLE(LED_PORT_DATA, led_color);
#endif
}


