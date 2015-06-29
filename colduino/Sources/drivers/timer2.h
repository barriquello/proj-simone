/*
 * timer2.h
 *
 *  Created on: 13/12/2011
 *      Author: gustavo
 */

#ifndef TIMER2_H_
#define TIMER2_H_

#include "hardware.h"

typedef void ( *TimerOverflowCallback_fn ) ( void );

void Timer2Setup(unsigned short int module, unsigned char enabled, TimerOverflowCallback_fn callback);
void Timer2Stop(unsigned char zero);
void Timer2Start(void);
void Timer2ChangeModule(unsigned short int module);
void Timer2Overflow(void);

#endif /* TIMER2_H_ */
