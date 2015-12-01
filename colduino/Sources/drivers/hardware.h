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

/**
* \file hardware.h
* \brief Processor macros, defines and registers declaration.
*
*
**/

/*********************************************************************************************************
*                                               BRTOS
*                                Brazilian Real-Time Operating System
*                            Acronymous of Basic Real-Time Operating System
*
*                              
*                                  Open Source RTOS under MIT License
*
*
*
*                                         Hardware Header Files
*
*
*   Author: Gustavo Weber Denardin
*   Revision: 1.0
*   Date:     20/03/2009
*
*********************************************************************************************************/

#ifndef HARDWARE_H
#define HARDWARE_H

#ifndef __GNUC__
#include <hidef.h>               /* for EnableInterrupts macro */
#else
/* !!!! unsafe !!! can cause a bug if reg d7 is used in the same part of the code
 * use OSEnterCritical/OSExitCritical instead */
#define EnableInterrupts 	__asm__ volatile("MOVE.W %sr,%d7 		\n\t" \
										 	 "ANDI.L #0xF8FF,%d7 	\n\t" \
											 "MOVE.W %d7,%sr 		\n\t" )

#define DisableInterrupts 	__asm__ volatile("MOVE.W %sr,%d7 		\n\t" \
										 	 "ORI.L #0x0700,%d7 	\n\t" \
											 "MOVE.W %d7,%sr		\n\t" )
#endif

#include "derivative.h"          /* include peripheral declarations */


#endif
