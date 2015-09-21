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
