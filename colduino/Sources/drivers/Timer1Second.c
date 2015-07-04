
#include "hardware.h"
#include "Timer1Second.h"
#include "printf_lib.h"

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
 printf_colduino("1s interrupt ocurred");
 Clear1SecondInterrupt();
 }*/

#if (NESTING_INT == 1)
#pragma TRAP_PROC
void timeOfDayInterrupt(void)
#else
interrupt void timeOfDayInterrupt(void)
#endif
{
	Clear1SecondInterrupt();
}
