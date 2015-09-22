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
 * timer2.c
 *
 *  Created on: 13/12/2011
 *      Author: gustavo
 */

#include "timer2.h"
#include "BRTOS.h"

#if TIMER2_ENABLED

static TimerOverflowCallback_fn TimerOverflowCallback;

void Timer2Setup(INT16U module, INT8U enabled, TimerOverflowCallback_fn callback)
{
	
	if (callback != NULL){
		
		TimerOverflowCallback = callback; // set callback for timer overflow
		
		SCGC1 |= SCGC1_TPM2_MASK; /* System Clock Gating Control: Enables tpm2 clock */
		/* TPM2SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=0,PS2=0,PS1=0,PS0=0 */
		
		TPM2SC = 0x00; /* Stop and reset counter */
		TPM2CNT = 0;
		TPM2MOD = module;
		(void) (TPM2SC == 0); /* Overflow int. flag clearing (first part) */
		/* TPM1SC: TOF=0,TOIE=1,CPWMS=0,CLKSB=0,CLKSA=1,PS2=0,PS1=0,PS0=0 */
		if (enabled == TRUE)
		{
			TPM2SC = 0x48; // Bus clock
		}
	}
	
	/* ### */
}

void Timer2Stop(unsigned char zero)
{
	TPM2SC = 0;
	if (zero == TRUE)
	{
		TPM2CNT = 0;
	}
}

void Timer2Start(void)
{
	TPM2SC = 0x48; // Bus clock
}

void Timer2ChangeModule(unsigned short int module)
{
	unsigned char backup = TPM2SC;
	TPM2SC = 0;
	TPM2MOD = module;
	if (TPM2SC != backup)
	{
		TPM2SC = backup;
	}
}


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

static int counter_isr = 0;
#if (NESTING_INT == 1)
#pragma TRAP_PROC
void Timer2Overflow(void)
#else
interrupt void Timer2Overflow(void)
#endif
{
	// ************************
	// Entrada de interrupção
	// ************************
	OS_INT_ENTER();
		
	// Interrupt handling
	TPM2SC_TOF = 0;

#if (NESTING_INT == 1)
	OS_ENABLE_NESTING();
#endif   

	// ************************
	// Handler code for the tick
	// ************************	
	TimerOverflowCallback();

	// ************************
	// Interrupt Exit
	// ************************
	OS_INT_EXIT();
	// ************************  
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

#endif
