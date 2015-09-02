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
#include "drivers.h"
#include "tasks.h"
#include "AppConfig.h"

#ifdef __cplusplus
extern "C"
#endif

/******************************************************************************
 * \file main.c
 * \author Carlos H. Barriquello
 * \brief  This is the main entry point of the software
 *****************************************************************************/

#if ((defined _MCF51MM256_H) || (defined _MCF51JE256_H) || (defined _MCF51JE128_H))
const unsigned char boot:0x040A = 0x00;   //zero out checksum to bypass boot loader
#endif /* (defined _MCF51MM256_H) || (defined _MCF51JE256_H) */

/******************************************************************************
 * \name        main
 * \brief       This function calls the application
 * \param       None
 * \return      None
 *****************************************************************************/
void main(void)
{	
	main_app();
	
	for (;;)
	{
		__RESET_WATCHDOG();		
	} /* loop forever */
}

