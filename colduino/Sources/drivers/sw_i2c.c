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

#include "derivative.h"
#include "sw_i2c.h"

#define SDA         PTFD_PTFD4_MASK  // SDA
#define SCL         PTFD_PTFD3_MASK  // SCL
#define PORTAI2C    PTFD
#define PORTAI2CDIR PTFDD
#define PORTAI2CIN  PTFD


/*************************/
static void delay_i2c(unsigned int time_end)
{
	volatile unsigned int timeout_counter = 0x00;
	while (timeout_counter < time_end)
		timeout_counter++;
}

#define I2C_HIGHLOW_TIME  100  

#ifdef I2C_HIGHLOW_TIME
#define	DELAY_I2C()    delay_i2c(I2C_HIGHLOW_TIME)
#else
#define	DELAY_I2C() 
#endif

static void SetLowSDA()
{
	PORTAI2C &= ~SDA;		
	PORTAI2CDIR |= SDA;           // SDA out
	DELAY_I2C();
}
static void SetHighSDA()
{
	PORTAI2CDIR &= ~SDA;         //SDA in
	DELAY_I2C();
}

static void SetLowSCL()
{
	PORTAI2C &= ~SCL;
	DELAY_I2C();
}
static void SetHighSCL()
{
	PORTAI2C |= SCL;
	DELAY_I2C();
}

void sw_i2c_init(void)
{

#ifdef   PORTAI2CSEL 
	PORTAI2CSEL &= ~SDA;
	PORTAI2CSEL &= ~SCL; 
#endif

	PORTAI2C &= ~SCL;   
	PORTAI2C &= ~SDA;   

	PORTAI2CDIR |= SCL;    // SCL output
	PORTAI2CDIR &= ~SDA;    // SDA input

	SetHighSCL();
	SetLowSDA(); 
	SetHighSDA(); 
}

/*************************/
/* Start Data Transfer   */
/*************************/
void sw_i2c_start(void)
{

	/*
	 *  Mudar SDA de high pra low com SCL em high
	 * 
	 */

	SetHighSCL();
	SetHighSDA();

	SetHighSCL();
	SetLowSDA();

	SetLowSCL();
	SetHighSDA();
}
/*************************/
/* Stop  Transfer        */
/*************************/
void sw_i2c_stop(void)
{
	/*
	 *  Mudar SDA de low pra high com SCL em high
	 * 
	 */
	SetLowSCL();
	SetLowSDA();

	SetHighSCL();
	SetLowSDA();

	SetHighSCL();
	SetHighSDA();
}

/*************************/
/* Write  Transfer       */
/*************************/
unsigned char sw_i2c_write(char i2c_data)
{

	unsigned char i;
	static unsigned char retorno;

	for (i = 0; i < 8; i++)
	{
		SetLowSCL(); // so pode mudar linha SDA com clk em nivel baixo

		if (i2c_data & 0x80)
			SetHighSDA();
		else
			SetLowSDA();

		SetHighSCL();
		i2c_data <<= 1;
	}
	SetLowSCL();

	/* ack Read */
	SetHighSDA();

	SetHighSCL();
	
	if (PORTAI2CIN & SDA)
	{
			retorno = NO_I2C_ACK;
	}else
	{
			retorno = OK_I2C_ACK;
	}
	
	SetLowSCL();	
	return (retorno);
}
/*************************/
/* Read  Transfer        */
/*************************/
char sw_i2c_read(unsigned char ack)
{
	int i;
	char caracter = 0x00;

	SetLowSCL();
	SetHighSDA();

	for (i = 0; i < 8; i++)
	{
		caracter = caracter << 1;
		SetHighSCL();
		if (PORTAI2CIN & SDA)
			caracter = caracter + 1;
		SetLowSCL();
	}

	if (ack)
	{                         //Send ACK to sender 
		SetLowSDA();
	}
	SetHighSCL();
	SetLowSCL();

	return (caracter);
}
