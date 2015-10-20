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

#define LED_PORT  0
#define LED_PORT_DIR    
#define LED_PORT_DATA
#define LED_PIN			

void led_onboard_init(void)
{
#if (__GNUC__) && LED_PORT
	BITCLEAR(LED_PORT_DATA,LED_PIN);
	BITSET(PTBDD,LED_PIN);
#endif
}

int led_onboard_state(void)
{
#if (__GNUC__) && LED_PORT
	return (BITTEST(LED_PORT_DATA,LED_PIN) ? LED_ON : LED_OFF);
#endif
}
void led_onboard_on(void)
{
#if (__GNUC__) && LED_PORT
	BITCLEAR(LED_PORT_DATA,LED_PIN);
#endif

}
void led_onboard_off(void)
{
#if (__GNUC__) && LED_PORT
	BITSET(LED_PORT_DATA,LED_PIN);
#endif
}
void led_onboard_toggle(void)
{
#if (__GNUC__) && LED_PORT
	BITTOGGLE(LED_PORT_DATA,LED_PIN);
#endif
}

