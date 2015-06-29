/*
 * timer2.c
 *
 *  Created on: 13/12/2011
 *      Author: gustavo
 */

#include "timer2.h"
#include "BRTOS.h"
#include "SD_API.h"

#include "mbport.h"


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

#if (SD_WAVE == 1)
#include "sound_driver.h"
#endif

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
	
#if (SD_WAVE == 1)
	OSSemPost(Audio);
#endif

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
