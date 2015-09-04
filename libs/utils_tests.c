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

