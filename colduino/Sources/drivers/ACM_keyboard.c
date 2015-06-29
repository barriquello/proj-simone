#include "hardware.h"
#include "ACM_keyboard.h"

#pragma warn_implicitconv off

BRTOS_Sem *sKeyboard;

////////////////////////////////////////////////
////////////////////////////////////////////////
///    Rotinas do Analog Comparator Module   ///
////////////////////////////////////////////////
////////////////////////////////////////////////

void ACM_Keyb_Setup(unsigned char State, unsigned char Interrupt, unsigned char Mode, unsigned char channel)
{
 unsigned char Setup;
 
 SCGC2 |= SCGC2_PRACMP_MASK;           			/* Enables PRACMP clock */
 
 Setup = (State<<7);
 Setup = Setup | (Mode << 1); 
 Setup = Setup | (Interrupt);
 
 PRACMPC0 = 0x60 | (channel >> 1);
 PRACMPC1 = 0;
 PRACMPC2 = channel; 
 PRACMPCS = Setup;
 
}



void ACMEnable(void)
{
	PRACMPCS_ACEN=1;
}
 
  
void ACMDisable(void)
{
	PRACMPCS_ACEN=0;
}


#if (NESTING_INT == 1)
#pragma TRAP_PROC
void Analog_comparator(void)
#else
interrupt void Analog_comparator(void)
#endif
{
  // ************************
  // Entrada de interrupção
  // ************************
  OS_INT_ENTER();

  // Interrupt handling
  PRACMPCS_ACMPF = 0;
  
  // Disable analog comparator interrupt
  // will be re-enabled after key analysis
  ACMDisable();  
  
  #if (NESTING_INT == 1)
  OS_ENABLE_NESTING();
  #endif
  
  // Call the keyboard analysis task
  OSSemPost(sKeyboard);  
  
  // ************************
  // Interrupt Exit
  // ************************
  OS_INT_EXIT();  
  // ************************
}
