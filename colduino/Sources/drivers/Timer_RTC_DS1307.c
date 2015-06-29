#include "Timer_RTC_DS1307.h"

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

