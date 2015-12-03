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
 * gc864_modem.c
 *
 *  Created on: Aug 7, 2015
 *      Author: UFSM
 */

#include "AppConfig.h"
#include "BRTOS.h"
#include "at_commands.h"	

#define CONST const

#if ARDUINO
CONST char AT_str[]    PROGMEM = AT_def;
CONST char CREG_str[]  PROGMEM = CREG_def;
CONST char XISP_str[]  PROGMEM = XISP_def;
CONST char GPRS1_str[]	PROGMEM = GPRS1_def;
CONST char GPRS_str[]	PROGMEM = GPRS_def;
CONST char XIIC1_str[]	PROGMEM = XIIC1_def;
CONST char XIIC_str[]	PROGMEM = XIIC_def;
CONST char IPSTAT_str[] PROGMEM = IPSTAT_def;
CONST char CLK_str[]	PROGMEM = CLK_def;
CONST char CLOSE0_str[] PROGMEM = CLOSE0_def;
CONST char CLOSE1_str[] PROGMEM = CLOSE1_def;
CONST char CGDCONT_str[] PROGMEM = CGDCONT_def;
CONST char XGAUTH_str[] PROGMEM = XGAUTH_def;

CONST char * const modem_init_cmd[] PROGMEM =
{
	AT_str,
	CREG_str,
	XISP_str,
	GPRS1_str,
	GPRS_str,
	XIIC1_str,
	XIIC_str,
	IPSTAT_str,
	CLK_str,
	CLOSE0_str,
	CLOSE1_str,
	CGDCONT_str,
	XGAUTH_str
};
#elif COLDUINO
#define PROGMEM
CONST char * const modem_init_cmd[] =
{
	AT_def,
	CREG_def,
	XISP_def,
	GPRS1_def,
	GPRS_def,
	XIIC1_def,
	XIIC_def,
	IPSTAT_def,
	CLK_def,
	CLOSE0_def,
	CLOSE1_def,
	CGDCONT_def,
	XGAUTH_def
};

#endif	
