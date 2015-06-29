// driver EEPROM
// EEPROMAddress 0xA0

#include "BRTOS.h"
#include "sw_i2c.h"
#include "eeprom.h"
#include "iic.h"


//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------
// Get high byte macro
#define high_byte(x)	(x >> 8)
#define I2C_DELAY    	1
#define I2C_SW          0

////////////////////////////////////////////////////////////////////////////////
// 	Routine:	delay_time
//	Inputs:		counter value to stop delaying
//	Outputs:	none
//	Purpose:	To pause execution for pre-determined time
////////////////////////////////////////////////////////////////////////////////
static void delay_time(u16 time_end)
{
	u16 timeout_counter = 0x00;
	while (timeout_counter < time_end)
		timeout_counter++;
}

/*******************************************************************************/

void EEPROM_ByteWrite(u16 Address, u08 Data)
// Description:
//   Byte Write Operation. The communication via the I2C bus with an EEPROM
//   (2465) is realized. A data byte is written into a user defined address.
{

	/* i2c por SW */
#if (defined I2C_SW &&  I2C_SW == 1)
	sw_i2c_start();							// Send start signal
	sw_i2c_write(EEPROMAddress & 0b11111110);// Send identifier I2C address     0xA0 = 10100000b
	delay_time(I2C_DELAY);
	sw_i2c_write((unsigned char)(high_byte(Address)));// Send address to EEPROM (high byte address)
	delay_time(I2C_DELAY);
	sw_i2c_write((unsigned char) Address);// Send address to EEPROM  (low byte address) 
	delay_time(I2C_DELAY);
	sw_i2c_write(Data);// Send low byte to EEPROM  (data to write)
	delay_time(I2C_DELAY);// Delay a period of time to write   
	sw_i2c_stop();	   // Send I2C Stop Transfer
	delay_time(20);	   // Delay a period of time to write
	DelayTask(WRITE_CYCLE_TIME);
#else
	/* i2c por HW */

	IIC_transmite(EEPROMAddress, Address, &Data);

#endif
}

/*---------------------------------------------------------------------------*/
u08 EEPROM_CurrentAddressRead(void)
// Description:
//   Current Address Read Operation. Data is read from the EEPROM. The current
//   address from the EEPROM is used.
{

	u08 data_in;

#if (defined I2C_SW &&  I2C_SW == 1)
	sw_i2c_start();							// Send start signal
	sw_i2c_write(EEPROMAddress);// Send identifer I2C address  (10100000b)
	sw_i2c_start();			   // Send I2C Start Transfer
	sw_i2c_write(EEPROMAddress + 1);// Send identifer I2C address  (10100001b)
	data_in = sw_i2c_read(0);// Read byte
	sw_i2c_stop();			 // Send I2C Stop Transfer

#else
	IIC_recebe(EEPROMAddress, &data_in);
#endif
	return data_in;
}

/*---------------------------------------------------------------------------*/
u08 EEPROM_RandomRead(u16 Address)
// Description:
//   Random Read Operation. Data is read from the EEPROM. The EEPROM
//   address is defined with the parameter Address.
{

	char data_in;
#if (defined I2C_SW &&  I2C_SW == 1)
	sw_i2c_start();							// Send start signal

	sw_i2c_write(EEPROMAddress);// Send identifer I2C address  (10100000b)
	delay_time(I2C_DELAY);
	sw_i2c_write((unsigned char) (high_byte(Address)));// Send address to EEPROM
	delay_time(I2C_DELAY);
	sw_i2c_write((unsigned char) Address);// Send address to EEPROM
	delay_time(I2C_DELAY);
	sw_i2c_start();// Send I2C Start Transfer
	sw_i2c_write(EEPROMAddress + 1);// Send identifer I2C address  (10100001b)
	delay_time(I2C_DELAY);
	data_in = sw_i2c_read(0);// Read byte
	sw_i2c_stop();			 // Send I2C Stop Transfer
#else

	/* Dummy write: Transmite NULL depois gera um sinal de start repeated */
	IIC_transmite(EEPROMAddress, Address, NULL);
	IIC_recebe(EEPROMAddress, &data_in);
	

#endif
	return data_in;

}

void EEPROM_Init(void)
{
#if (defined I2C_SW &&  I2C_SW == 1)
	sw_i2c_init();
#else
	IIC_init();
#endif
}

/*---------------------------------------------------------------------------*/
void EEPROM_AckPolling(void)
// Description:
//   Acknowledge Polling. The EEPROM will not acknowledge if a write cycle is
//   in progress. It can be used to determine when a write cycle is completed.
{

	volatile unsigned int count = 0x03FF, ack = 0;
	while ((count != 0))
	{

		count--;
		sw_i2c_start();
		if (sw_i2c_write(EEPROMAddress))
			count = 0;
		sw_i2c_stop();

	}
}
