/*
 * Timer1Second.h
 *
 *  Created on: Oct 8, 2014
 *      Author: Rafael
 */

#ifndef TIMER1SECOND_H_
#define TIMER1SECOND_H_

void Timer1SecondSetup(void);

void Clear1SecondInterrupt(void);

//interrupt void Timer1SecondOverflow(void);
interrupt void timeOfDayInterrupt(void);
#endif /* TIMER1SECOND_H_ */
