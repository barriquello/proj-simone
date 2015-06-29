// driver RTC DS1307
// DS1307Address 0xD0

#include "BRTOS.h"
#include "rtc_ds1307.h"
#include "sw_i2c.h"
#include "iic.h"


//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------
// Get high byte macro
#define high_byte(x)	((x) >> 8)
#define I2C_DELAY           (100)
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
	INT32U timeout_counter = 0x00;
	while (timeout_counter < time_end)
		timeout_counter++;
}

/*******************************************************************************/

void RTC_ByteWrite(INT8U Address, INT8U Data)
// Description:
//   Byte Write Operation. The communication via the I2C bus with an EEPROM
//   (2465) is realized. A data byte is written into a user defined address.
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
