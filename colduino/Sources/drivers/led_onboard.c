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

