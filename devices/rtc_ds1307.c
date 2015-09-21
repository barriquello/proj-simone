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
#include "RTC_DS1307.h"


// driver RTC DS1307
// DS1307Address 0xD0

#include "BRTOS.h"
#include "sw_i2c.h"
#include "iic.h"

//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------
// Get high byte macro
#define high_byte(x)	((x) >> 8)
#define I2C_DELAY       (100)
#define I2C_SW          1

#define CRITICAL_SECTION_START() 		OS_SR_SAVE_VAR; OSEnterCritical();
#define CRITICAL_SECTION_END() 			OSExitCritical();

////////////////////////////////////////////////////////////////////////////////
// 	Routine:	delay_time
//	Inputs:		counter value to stop delaying
//	Outputs:	none
//	Purpose:	To pause execution for pre-determined time
////////////////////////////////////////////////////////////////////////////////
static void delay_time(INT32U time_end)
{
	while (time_end > 0 ) time_end--;
}

/*******************************************************************************/

void RTC_ByteWrite(INT8U Address, INT8U Data)
// Description:
//   Byte Write Operation. The communication via the I2C bus is realized. 
// A data byte is written into a user defined address.
{

#if (defined I2C_SW &&  I2C_SW == 1)
	CRITICAL_SECTION_START();
	sw_i2c_start();							// Send start signal
	sw_i2c_write(DS1307Address & 0b11111110);// Send identifier I2C address     0xA0 = 10100000b
	delay_time(I2C_DELAY);
	sw_i2c_write((INT8U) Address);// Send address to RTC  (byte address) 
	delay_time(I2C_DELAY);
	sw_i2c_write(Data);					// Send low byte to RTC  (data to write)
	delay_time(I2C_DELAY); // Delay a period of time to write   
	sw_i2c_stop();	   // Send I2C Stop Transfer
	delay_time(20);	   // Delay a period of time to write
	CRITICAL_SECTION_END();
#else
	IIC_transmite(DS1307Address, Address, &Data);
#endif
}

/*---------------------------------------------------------------------------*/
INT8U RTC_CurrentAddressRead(void)
// Description:
//   Current Address Read Operation. Data is read from the RTC. The current
//   address from the RTC is used.
{

	INT8U data_in;

#if (defined I2C_SW &&  I2C_SW == 1)
	CRITICAL_SECTION_START();
	sw_i2c_start();				// Send I2C Start Transfer        				
	sw_i2c_write(DS1307Address | 1);	// Send identifer I2C address  (10100001b)
	data_in = sw_i2c_read(0);				// Read byte
	sw_i2c_stop();				// Send I2C Stop Transfer
	CRITICAL_SECTION_END();
#else
	IIC_recebe(DS1307Address, &data_in);
#endif
	return data_in;

}

/*---------------------------------------------------------------------------*/
INT8U RTC_RandomRead(INT8U Address)
// Description:
//   Random Read Operation. Data is read from the RTC. The RTC
//   address is defined with the parameter Address.
{

	INT8U data_in;
#if (defined I2C_SW &&  I2C_SW == 1)
	CRITICAL_SECTION_START();
	sw_i2c_start();							// Send start signal

	sw_i2c_write(DS1307Address);		// Send identifer I2C address  (10100000b)
	delay_time(I2C_DELAY);
	sw_i2c_write((INT8U) Address);			// Send address to EEPROM
	delay_time(I2C_DELAY);
	sw_i2c_start();							// Send I2C Start Transfer
	sw_i2c_write(DS1307Address | 1);	// Send identifer I2C address  (10100001b)
	delay_time(I2C_DELAY);
	data_in = sw_i2c_read(0);			// Read byte
	sw_i2c_stop();			 // Send I2C Stop Transfer
	
	CRITICAL_SECTION_END();
#else
	IIC_transmite(DS1307Address, Address, NULL);
	IIC_recebe(DS1307Address, &data_in);
#endif
	return data_in;

}

INT8U RTC_DS1307_Init(void)
{
#if (defined I2C_SW &&  I2C_SW == 1)
	INT8U ret = NO_I2C_ACK;
	CRITICAL_SECTION_START();
		sw_i2c_init();
	CRITICAL_SECTION_END();
	
	sw_i2c_start();							// Send start signal
	ret = sw_i2c_write(DS1307Address);		// Send identifer I2C address  (10100000b)
	delay_time(I2C_DELAY);
	sw_i2c_stop();	
	
	return ((ret == OK_I2C_ACK) ? TRUE : FALSE);
	
#else
	IIC_init();
#endif

}

/*---------------------------------------------------------------------------*/
void RTC_AckPolling(void)
// Description:
//   Acknowledge Polling. The RTC will not acknowledge if a write cycle is
//   in progress. It can be used to determine when a write cycle is completed.
{

	volatile INT32U count = 0x03FF, ack = 0;
	while ((count != 0))
	{

		count--;
		sw_i2c_start();
		if (sw_i2c_write(DS1307Address))
			count = 0;
		sw_i2c_stop();

	}
}

static INT8U Detected = FALSE;  /*!< TRUE or FALSE */

// Fast division by 10
static INT8U Div10(INT8U n)
{
	n = (n >> 1) + (n >> 2);
	n += 2;
	n = n + (n >> 4);
	n = n + (n >> 8);
	n = n + (n >> 16);
	n = n >> 3;
	return n;
}

static INT8U bin2bcd(INT8U val)
{
	INT8U dez = Div10(val);
	INT8U un = val - dez*10;
	return ((dez << 4) | un);
}

static INT8U bcd2bin(INT8U val)
{
	return (((val >> 4) & 0x0F)*10 + (val & 0x0F));
}

/* return  0 = 24h,  1 = 12h */
static INT8U Get_Hour_Format(void)
{	
	INT8U address_read = RTC_RandomRead(2);
	return (address_read & (1<<6));
}

static void Set_24h_Format(void)
{
	INT8U address_read = RTC_RandomRead(2);
	RTC_ByteWrite(2, address_read & 0b11011111);
}

static void Set_AM_PM_Mode(void)
{
	INT8U address_read = RTC_RandomRead(2);
	RTC_ByteWrite(2, address_read | 0b00100000);
}

static INT8U Get_AM_PM(void)
{
	INT8U address_read = RTC_RandomRead(2);
	return (address_read & (1 << 5));
}


void RTC_DS1307_Config(void)
{
	RTC_DS1307_Start_OSC();
	if(Get_Hour_Format() != 0)
	{
		Set_24h_Format();		
	}
	
}

INT8U RTC_DS1307_GetSeconds(void)
{
	INT8U address_read = RTC_RandomRead(SEC_ADDRESS);
	return (bcd2bin(address_read & 0x7F));
	
}

INT8U RTC_DS1307_GetMinutes(void)
{
	INT8U address_read = RTC_RandomRead(MIN_ADDRESS);
	return (bcd2bin(address_read & 0x7F));
}

// Somente valido para formato 24 h

INT8U RTC_DS1307_GetHours(void)
{
	INT8U address_read = RTC_RandomRead(HOUR_ADDRESS);
	return (bcd2bin(address_read & 0x3F));
}

INT8U RTC_DS1307_GetDayOfMonth(void)
{
	INT8U address_read = RTC_RandomRead(DAY_ADDRESS);
	return (bcd2bin(address_read & 0x3F));
}

INT8U RTC_DS1307_GetMonth(void)
{
	INT8U address_read = RTC_RandomRead(MONTH_ADDRESS);
	return (bcd2bin(address_read & 0x1F));
}

/* 0 a 99, starting from 2000 */ 
INT8U RTC_DS1307_GetYear(void)
{
	INT8U address_read = RTC_RandomRead(YEAR_ADDRESS);
	return (bcd2bin(address_read));
}

void RTC_DS1307_Set_Time(INT8U hour, INT8U min, INT8U sec)
{
	
	RTC_ByteWrite(HOUR_ADDRESS, bin2bcd(hour) & 0x3F); // Ajusta hora
	RTC_ByteWrite(MIN_ADDRESS, bin2bcd(min) & 0x7F); // Ajusta minutos
	RTC_ByteWrite(SEC_ADDRESS, bin2bcd(sec) & 0x7F); // Ajusta segundos
}

void RTC_DS1307_Set_Date(INT8U year, INT8U month, INT8U day)
{
	RTC_ByteWrite(YEAR_ADDRESS, bin2bcd(year) & 0xFF); // Ajusta ano
	RTC_ByteWrite(MONTH_ADDRESS, bin2bcd(month) & 0x1F); // Ajusta mes
	RTC_ByteWrite(DAY_ADDRESS, bin2bcd(day) & 0x3F); // Ajusta dia
}

void RTC_DS1307_Update(RTC_DS1307 *rtc_timer)
{
	rtc_timer->Year = (INT16U)(RTC_DS1307_GetYear() + RTC_YEAR_INIT);
	rtc_timer->Month = RTC_DS1307_GetMonth();
	rtc_timer->Day = RTC_DS1307_GetDayOfMonth();
	rtc_timer->Hour = RTC_DS1307_GetHours();
	rtc_timer->Min = RTC_DS1307_GetMinutes();
	rtc_timer->Sec = RTC_DS1307_GetSeconds();
}

void RTC_DS1307_Start_OSC(void)
{
	INT8U Reg_00 = RTC_RandomRead(0);
	if ((Reg_00 & 0x80) == 0x80) // check CH (clock halt) bit
	{
		Reg_00 = Reg_00 & ~0x80; 
		RTC_ByteWrite(0, Reg_00);
	}	
}

INT8U RTC_DS1307_GetStatus(void)
{
		return Detected;
}

void RTC_DS1307_SetStatus(INT8U st)
{
		Detected = (st ? TRUE : FALSE);
}

