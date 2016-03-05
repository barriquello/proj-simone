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
 * led_onboard.h
 *
 *  Created on: Jan 31, 2015
 *      Author: Carlos
 */

 /** \addtogroup drivers  Drivers
 *  @{
 */
 
 /*! \defgroup led LEDs
 * @{
 */
 
 
#ifndef LED_ONBOARD_H_
#define LED_ONBOARD_H_

typedef enum{
	RED_LED=4,
	YELLOW_LED=5,
	GREEN_LED=6	
} led_color_t;

void led_onboard_init(void);
int  led_onboard_state(led_color_t led_color);
void led_onboard_on(led_color_t led_color);
void led_onboard_off(led_color_t led_color);
void led_onboard_toggle(led_color_t led_color);

#define LED_ON  1
#define LED_OFF 0

#endif /* LED_ONBOARD_H_ */

/** @} */
/** @} */
