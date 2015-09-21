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
 * utils_tests.c
 *
 *  Created on: Aug 12, 2015
 *      Author: UFSM
 */

/*-----------------------------------------------------------------------------------*/

#include "assert.h"
#include "utils.h"

static void test_hextoint(void)
{
	uint16_t r;
	r = hex2byte('A','B');
	assert(r==0xAB);

	r = hex2byte('1','9');
	assert(r==0x19);

	r = byte2int(hex2byte('A','B'),hex2byte('1','9'));
	assert(r==0xAB19);
}

static void test_inttohex(void)
{

	char ret[4];
	byte2hex(ret,0xFF);
	assert((ret[0] == 'F') && (ret[1]== 'F'));

	byte2hex(ret,0x11);
	assert((ret[0] == '1') && (ret[1]== '1'));

	byte2hex(ret,0xA0);
	assert((ret[0] == 'A') && (ret[1]== '0'));

	byte2hex(ret,0x9E);
	assert((ret[0] == '9') && (ret[1]== 'E'));

	int2hex(ret,0xFF11);
	assert((ret[0] == 'F') && (ret[1]== 'F') && (ret[2] == '1') && (ret[3]== '1'));

	int2hex(ret,0xA09E);
	assert((ret[0] == 'A') && (ret[1]== '0') && (ret[2] == '9') && (ret[3]== 'E'));
}

static void test_u8tobcd(void)
{
	char ret[4];

	u8tobcd(ret,99);
	assert((ret[0] == '9') && (ret[1]== '9'));

	u8tobcd(ret,13);
	assert((ret[0] == '1') && (ret[1]== '3'));
}

void utils_tests(void)
{
	test_hextoint();
	test_inttohex();
	test_u8tobcd();
}

