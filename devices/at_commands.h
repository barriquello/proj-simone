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
 * gc864_modem.h
 *
 *  Created on: Aug 7, 2015
 *      Author: UFSM
 */

#ifndef AT_COMMANDS_H_
#define AT_COMMANDS_H_

#include "OS_types.h"
#include "AppConfig.h"

typedef enum
{
	AT = 0,
	CREG,
	XISP,
	GPRS0,
	GPRS1,
	GPRS,
	XIIC1,
	XIIC,
	IPSTAT,
	CLK,
	CLOSE0,
	CLOSE1,
	CGDCONT,
	XGAUTH,
	SKTRST,
	ATZ
}at_enum_cmd;

#define MODEM_APN		 "tim.br"
#define MODEM_PWD		 "tim"

#define AT_def		"AT\r\n"
#define	CREG_def	"AT+CREG?\r\n"
#define XISP_def	"AT+XISP=0\r\n"
#define GPRS0_def	"AT#GPRS=0\r\n"
#define GPRS1_def	"AT#GPRS=1\r\n"
#define GPRS_def	"AT#GPRS?\r\n"
#define XIIC1_def	"AT+XIIC=1\r\n"
#define	XIIC_def	"AT+XIIC?\r\n"
#define IPSTAT_def  "AT+IPSTATUS=0\r"
#define	CLK_def		"AT+CCLK?\r\n"
#define	CLOSE0_def	"AT+TCPCLOSE=0\r\n"
#define	CLOSE1_def  "AT+TCPCLOSE=1\r\n"
#define	CGDCONT_def  ("AT+CGDCONT=1,\"IP\",\"" MODEM_APN "\"\r\n")
#define	XGAUTH_def	 ("AT+XGAUTH=1,1,\"" MODEM_PWD "\",\"" MODEM_PWD "\"\r\n")
#define SKTRST_def	"AT#SKTRST\r\n"
#define ATZ_def     "ATZ\r\n"

extern const char * const modem_init_cmd[];

#endif /* AT_COMMANDS_H_ */
