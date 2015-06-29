/*
 * led_onboard.h
 *
 *  Created on: Jan 31, 2015
 *      Author: Carlos
 */

#ifndef LED_ONBOARD_H_
#define LED_ONBOARD_H_


void led_onboard_init(void);
int  led_onboard_state(void);
void led_onboard_on(void);
void led_onboard_off(void);
void led_onboard_toggle(void);

#define LED_ON  1
#define LED_OFF 0

#endif /* LED_ONBOARD_H_ */
