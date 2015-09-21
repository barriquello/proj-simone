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

void led_onboard_init(void)
{
	PTBD_PTBD0 = 0;
	PTBDD_PTBDD0 = 1;
}

int led_onboard_state(void)
{
	return (PTBD_PTBD0 ? LED_ON : LED_OFF);
}
void led_onboard_on(void)
{
	PTBD_PTBD0 = 0;
}
void led_onboard_off(void)
{
	PTBD_PTBD0 = 1;
}
void led_onboard_toggle(void)
{
	PTBD_PTBD0 = ~PTBD_PTBD0;
}

