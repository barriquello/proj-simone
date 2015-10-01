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

#include "hardware.h"
#include "Timer1Second.h"
#include "HAL.h"

void Timer1SecondSetup()
{
	TODSC = 0b01001000;
	TODC = 0b11001010;
	/*
	 TODC_TODCLKS = 2;
	 TODC_TODCLKEN = 0;
	 TODC_TODPS = 3;
	 TODSC_SECF = 1;
	 TODSC_QSECIE = 0;
	 TODSC_SECIE = 1;
	 TODSC_MTCHIE = 0;
	 TODSC_MTCHEN = 0;

	 // last step
	 TODC_TODEN = 1;*/

}

void Clear1SecondInterrupt()
{
	TODSC |= 0b001000000;
	//|
	//|-> 1s interrupt en.

	TODC |= 0b00100000;
	//|
	//|-> reseta contador

}

//interrupt void Timer1SecondOverflow(void)
/*
 interrupt VectorNumber_Vtod void tod_ISR(void)
 {
 	 Clear1SecondInterrupt();
 }*/

#if (NESTING_INT == 1)
#pragma TRAP_PROC
#if __GNUC__
__attribute__((__interrupt__))
#endif
void timeOfDayInterrupt(void)
#else
#if __GNUC__
__attribute__((__interrupt__))
#else
interrupt
#endif
void timeOfDayInterrupt(void)
#endif
{
	Clear1SecondInterrupt();
}
