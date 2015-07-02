/**
 * \file OS_RTC.c
 * \brief System Time managment functions
 *
 * Functions to reset and update the system time and date
 *
 **/
/*********************************************************************************************************
 *                                               BRTOS
 *                                Brazilian Real-Time Operating System
 *                            Acronymous of Basic Real-Time Operating System
 *
 *                              
 *                                  Open Source RTOS under MIT License
 *
 *
 *
 *                                      OS Time managment functions
 *
 *
 *   Author:   Gustavo Weber Denardin
 *   Revision: 1.1
 *   Date:     11/03/2010
 *
 *   Authors:  Carlos Henrique Barriquelo e Gustavo Weber Denardin
 *   Revision: 1.2
 *   Date:     01/10/2010
 *
 *   Authors:  Carlos Henrique Barriquelo e Gustavo Weber Denardin
 *   Revision: 1.3
 *   Date:     11/10/2010
 *
 *   Authors:  Carlos Henrique Barriquelo e Gustavo Weber Denardin
 *   Revision: 1.4
 *   Date:     19/10/2010
 *
 *   Authors:  Carlos Henrique Barriquelo e Gustavo Weber Denardin
 *   Revision: 1.41
 *   Date:     20/10/2010
 *
 *********************************************************************************************************/

#include "BRTOS.h"
//#include "Timer_RTC_DS1307.h"

// estrutura - Hora

static volatile OSTime Hora;
static volatile OSDate Data;
static volatile OS_RTC OSRtc;

// Lookup table holding the length of each mont. The first element is a dummy.
static const INT8U MonthLength[13] =
{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static INT8U LeapMonth;

static void (*input_rtc) (OS_RTC *rtc);

void CalendarInputSet(void (*input) (OS_RTC *))
{
	input_rtc = input;
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      OS Update Time Function                     /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void OSUpdateTime(void)
{
	OS_SR_SAVE_VAR

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSEnterCritical();

	Hora.RTC_Second++;

	if (Hora.RTC_Second == 60)
	{

		Hora.RTC_Second = 0;
		Hora.RTC_Minute++;

		if (Hora.RTC_Minute == 60)
		{

			Hora.RTC_Minute = 0;
			Hora.RTC_Hour++;

			if (Hora.RTC_Hour == 24)
			{

				Hora.RTC_Hour = 0;

			}
		}
	}

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSExitCritical();

}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      OS Update Time Function                     /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void OSUpdateUptime(void)
{
	OS_SR_SAVE_VAR

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSEnterCritical();

	Hora.RTC_Second++;

	if (Hora.RTC_Second == 60)
	{

		Hora.RTC_Second = 0;
		Hora.RTC_Minute++;

		if (Hora.RTC_Minute == 60)
		{

			Hora.RTC_Minute = 0;
			Hora.RTC_Hour++;

			if (Hora.RTC_Hour == 24)
			{
				Hora.RTC_Hour = 0;
				Data.RTC_Day++;
				

			}
		}
	}

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSExitCritical();
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      OS Update Date Function                     /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void OSUpdateDate(void)
{
	OS_SR_SAVE_VAR

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSEnterCritical();

	Data.RTC_Day++;

	if (Data.RTC_Day == 30)
	{
		// deve-se adaptar para os dias exatos de cada mês

		Data.RTC_Day = 0;
		Data.RTC_Month++;

		if (Data.RTC_Month == 12)
		{

			Data.RTC_Month = 0;
			Data.RTC_Year++;

			if (Data.RTC_Year == 9999)
			{    // ano máximo 9999

				Data.RTC_Year = 0;
			}
		}
	}

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSExitCritical();

}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      OS Reset Time Function                      /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void OSResetTime(void)
{
	OS_SR_SAVE_VAR

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSEnterCritical();

	Hora.RTC_Second = 0;
	Hora.RTC_Minute = 0;
	Hora.RTC_Hour = 0;

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSExitCritical();

}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////    

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      OS Reset Date Function                      /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void OSResetDate(void)
{
	OS_SR_SAVE_VAR

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSEnterCritical();

	Data.RTC_Day = 0;
	Data.RTC_Month = 0;
	Data.RTC_Year = 0;

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSExitCritical();

}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Return Time Function                        /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

OSTime OSUptime(void)
{
	return Hora;
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Return Date Function                        /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

OSDate OSUpDate(void)
{
	return Data;
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void OSUpdateCalendar(void)
{

	OS_SR_SAVE_VAR

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSEnterCritical();

	OSRtc.Sec++;               // increment second

	if (OSRtc.Sec == 60)
	{
		OSRtc.Sec = 0;
		OSRtc.Min++;

		if (OSRtc.Min > 59)
		{
			OSRtc.Min = 0;
			OSRtc.Hour++;

			if (OSRtc.Hour > 23)
			{
				OSRtc.Hour = 0;
				OSRtc.Day++;

				// Check for leap year if month == February
				if (OSRtc.Month == 2)
					if (!(OSRtc.Year & 0x0003))             // if (gYEAR%4 == 0)
						if (OSRtc.Year % 100 == 0)
							if (OSRtc.Year % 400 == 0)
								LeapMonth = 1;
							else
								LeapMonth = 0;
						else
							LeapMonth = 1;
					else
						LeapMonth = 0;
				else
					LeapMonth = 0;

				// Now, we can check for month length
				if (OSRtc.Day > (MonthLength[OSRtc.Month] + LeapMonth))
				{
					OSRtc.Day = 1;
					OSRtc.Month++;

					if (OSRtc.Month > 12)
					{
						OSRtc.Month = 1;
						OSRtc.Year++;
					}
				}
			}
		}
	}

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSExitCritical();
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Return Calendar Function                    /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void GetCalendar(OS_RTC *rtc)
{
	OS_SR_SAVE_VAR

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSEnterCritical();

	*rtc = OSRtc;

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSExitCritical();
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Set Calendar Function                       /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void SetCalendar(OS_RTC *rtc)
{
	OS_SR_SAVE_VAR

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSEnterCritical();

	OSRtc = *rtc;

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSExitCritical();
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////      Calendar Time Function                      /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void GetCalendarTime(OSTime *t)
{
	OS_SR_SAVE_VAR

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSEnterCritical();
	
	t->RTC_Hour = OSRtc.Hour;
	t->RTC_Minute = OSRtc.Min;
	t->RTC_Second = OSRtc.Sec;
	
#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSExitCritical();
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////       Calendar Date Function                     /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void GetCalendarDate(OSDate *d)
{
	OS_SR_SAVE_VAR

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSEnterCritical();
	
	d->RTC_Year = OSRtc.Year;
	d->RTC_Month = OSRtc.Month;
	d->RTC_Day = OSRtc.Day;
	
#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSExitCritical();
}
	
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////       Calendar Date and Time Function    	       /////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void GetDateTime(OSDateTime * dt)
{
	OS_SR_SAVE_VAR

#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSEnterCritical();
	
	dt->date.RTC_Year = OSRtc.Year;
	dt->date.RTC_Month = OSRtc.Month;
	dt->date.RTC_Day = OSRtc.Day;
	
	dt->time.RTC_Hour = OSRtc.Hour;
	dt->time.RTC_Minute = OSRtc.Min;
	dt->time.RTC_Second = OSRtc.Sec;	
	
#if (NESTING_INT == 0)
	if (!iNesting)
#endif
	OSExitCritical();
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

INT8U Init_Calendar(void)
{
	OS_RTC rtc;

#if 0	
	RTC_DS1307 rtc_ds1307;

	RTC_DS1307_SetStatus(FALSE);
	
	if (RTC_DS1307_Init() == FALSE)
	{
		return 	FALSE;
	}	
	
	RTC_DS1307_Config(); /* clear Ch (clock halt) bit, set 24H format */ 
	RTC_DS1307_Update(&rtc_ds1307);
	
	rtc.Year = rtc_ds1307.Year;
	rtc.Month = rtc_ds1307.Month;
	rtc.Day = rtc_ds1307.Day;
	rtc.Hour = rtc_ds1307.Hour;
	rtc.Min = rtc_ds1307.Min;
	rtc.Sec = rtc_ds1307.Sec;
	RTC_DS1307_SetStatus(TRUE);
#endif

	SetCalendar(&rtc);	
	return 	TRUE;
}

void Resync_calendar(void)
{
	OS_RTC rtc;
#if 0		
	RTC_DS1307 rtc_ds1307;
	
	RTC_DS1307_Update(&rtc_ds1307);
		
	rtc.Year = rtc_ds1307.Year;
	rtc.Month = rtc_ds1307.Month;
	rtc.Day = rtc_ds1307.Day;
	rtc.Hour = rtc_ds1307.Hour;
	rtc.Min = rtc_ds1307.Min;
	rtc.Sec = rtc_ds1307.Sec;
#endif	
	
	SetCalendar(&rtc);
}

// return 0 if equal, 1 if rtc1 > rtc2, -1 if rtc1 < rtc2 
INT8S CompareDateTime(OS_RTC const *rtc1, OS_RTC const *rtc2)
{
	
	if(rtc1->Year == rtc2->Year)
	{
		if (rtc1 ->Month == rtc2->Month)
		{
			if(rtc1->Day == rtc2->Day)
			{
				if(rtc1->Hour == rtc2->Hour)
				{
					if(rtc1->Min == rtc2->Min)
					{
						if(rtc1->Sec == rtc2->Sec)
						{
							return 0;
						}
						else
						{
							if(rtc1->Sec > rtc2->Sec)
							{
								return 1;
							}
							else
							{
								return -1;
							}
						}
					}
					else
					{
						if(rtc1->Min > rtc2->Min)
						{
							return 1;
						}
						else
						{
							return -1;
						}
					}

				}
				else
				{
					if(rtc1->Hour > rtc2->Hour)
					{
						return 1;
					}
					else
					{
						return -1;
					}
				}
			}
			else
			{
				if(rtc1->Day > rtc2->Day)
				{
					return 1;
				}
				else
				{
					return -1;
				}
			}

		}
		else
		{
			if(rtc1->Month > rtc2->Month)
			{
				return 1;
			}
			else
			{
				return -1;
			}
		}
	}
	else
	{
		if(rtc1->Year > rtc2->Year)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
}

