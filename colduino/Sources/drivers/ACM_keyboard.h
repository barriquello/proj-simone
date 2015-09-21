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
#include "BRTOS.h"

extern BRTOS_Sem *sKeyboard;

////////////////////////////////////////////////
////////////////////////////////////////////////
///    Rotinas do ACM                        ///
////////////////////////////////////////////////
//////////////////////////////////////////////// 

#define Enable  1
#define Disable 0

#define External  1
#define Internal 0

#define FallingAndRising 0
#define Falling 1
#define Rising  2

#define ACM_CHANNEL0	1
#define ACM_CHANNEL1	2
#define ACM_CHANNEL2	4
#define ACM_CHANNEL3	8
#define ACM_CHANNEL4	16
#define ACM_CHANNEL5	32
#define ACM_CHANNEL6	64

void ACM_Keyb_Setup(unsigned char State, unsigned char Interrupt, unsigned char Mode, unsigned char channel);
void ACMEnable(void);  
void ACMDisable(void);
void Analog_comparator(void);
              
  // State - ENABLE/DISABLE
  // Bandgap - INTERNAL/EXTERNAL
  // Interrupt - ENABLE/DISABLE
  // Output - Output the state of ACM: ENABLE/DISABLE
  // MODE - Mode of detection: Rising, Falling, FallingAndRising     
              
