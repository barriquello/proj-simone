/*
 * datalogger.c
 *
 *  Created on: 2014
 *      Author: Carlos H. Barriquello
 */

#include "datalogger.h"
#include "printf_colduino.h"
#include "BRTOS.h"
#include "debug_stack.h"
#include "spi.h"
#include "SD_API.h"
//#include "sound_driver.h"
#include "timer2.h"
#include "utils.h"
#include "Timer_RTC_DS1307.h"
#include "OS_RTC.h"
#include "eeprom.h"
#include "iic.h"
#include "mbport.h"

#pragma warn_unusedarg off

/*
 Tarefa 1 - medição e datalogger
 init: detect SD card, RTC
 

 1) Aguarda 30 segundos.

 2) Ajusta relogio
 
 #if RTC_PRESENTE==1
 mutex (RTC)
 - ajusta data e hora usando calendário e RTC
 mutex (RTC)
 #endif

 se cartão SD presente

 mutex(cartão SD)

 3) procura último arquivo salvo (ano_mes_dia_enviado)
 4) Verifica datas:
 - se data do arquivo e data atual coincidem abre o arquivo 
 - senão:
 se data atual > data do arquivo 
 cria novo arquivo com data atual

 se data atual < data do arquivo
 #if RTC_PRESENTE==1
 mutex (RTC)
 - ajusta data e hora
 - ajusta calendário e RTC
 mutex (RTC)
 #else

 abre arquivo encontrado	
 
 #if PM200_PRESENTE==1
 2) Detecta equipamentos de medição
 3) Faz a leitura dos dados
 #else
 3) Faz a leitura dos dados de testes
 #endif

 6) salva os dados no formato:

 tempo em segundos desde às 0h00, sincronizado GPRS ou não, valores csv, enviado ou não, /n

 - fecha arquivo

 mutex(cartão SD)

 */

#define VOLATILE volatile 

#include "modbus.h"
#include "modbus_pm210.h" /* PM210 device */
#include "modbus_ts.h"	  /* TS device */
#include "led_onboard.h"

#include "string.h"

typedef INT32U time_t;

struct tm
	{	
	    int tm_sec; /* Segundos, 0-59*/
	    int tm_min; /* Minutos, 0-59*/
	    int tm_hour; /*Horas 0-23 */
	    int tm_mday; /*dia do mês, 1-31 */
	    int tm_mon; /* mês a partir de janeiro, 0-11 */
	    int tm_year; /* anos a partir de 1900 */
	    int tm_wday; /* dias a partir de domingo, 0-6 */
	    int tm_yday; /* dias a partir de 1 de janeiro 1-365 */
	    int tm_isdst; /* Indicador de horário de verão */
	};

time_t mktime(struct tm *tmbuf);

time_t ConvertDateTimeToUnixTime(OSDateTime * dt);


/* static IR and HR list for PM210 device */
static modbus_pm210_input_register_list1  PM210_IRList1;
static modbus_pm210_input_register_list2  PM210_IRList2;
static modbus_pm210_holding_register_list PM210_HRList;
static modbus_ts_input_register_list  	  TS_IRList;
static modbus_ts_holding_register_list    TS_HRList;

INT8U SetTimeStamp (INT8U device_id, INT8U *data_ptr, OSTime *timestamp);

void Tarefa_datalogger(void)
{
	/* task setup */
	INT8U status = 0;
	OSDateTime DateTime;
	OSTime timestamp;	
	time_t unix_ts;
	
	char LogFileName[15];

	/* Detect and init the SD card */
	SDCard_ResourceInit(SDCARD_MUTEX_PRIORITY);
	do
	{
		status = SDCard_Init(VERBOSE_OFF);
		DelayTask(1000);
	} while (status != SD_OK);

	/* Detect RTC */
	while(RTC_DS1307_GetStatus() == FALSE)
	{		
		DelayTask(1000);
	} 
	
	/* init modbus interface */
	if (Modbus_init() == FALSE) 
	{
		while(1)
		{
			DelayTask(1000);
			led_onboard_toggle();
		}
	}
		
	GetDateTime(&DateTime);
	unix_ts = ConvertDateTimeToUnixTime(&DateTime);	
	    
	/* task main loop */
	for (;;)
	{
		DelayTask(DATALOGGER_DELAY_TIME); /*  Aguarda 30 segundos */
		
		/* ajusta data e hora usando calendário e RTC */
		GetDateTime(&DateTime);
		
		if (SD_PRESENT) // check if SD card is inserted
		{
			VOLATILE INT32U lastFileCreationDate = 0;
			
			// yyyyMMddHH
			//int now = year * 1000000 + month * 10000 + day * 100 + hour;
			VOLATILE INT32U now = (INT32U)((DateTime.date.RTC_Year - 2000) * 1000000 +  DateTime.date.RTC_Month * 10000 
					+ DateTime.date.RTC_Day*100 + DateTime.time.RTC_Hour);
			
			if (GetLastCreatedFileName(LogFileName) == TRUE) {
				// return filename
				lastFileCreationDate = GetFileCreationDate(LogFileName);				
			}
			
			// Se passou 1h, muda fileName e cria outro arquivo
			if (now > lastFileCreationDate)
			{										
				PrintDateTime(&DateTime, LogFileName);
				
				LogFileName[10] = 0; // truncate yyyymmddhhmmss to yyyymmddhh								
				strcpy(LogFileName, &LogFileName[2]); // truncate yyyymmddhh to yymmddhh
				strcat(LogFileName,".log");		
				
				CreateFile(LogFileName, VERBOSE_OFF);		  
			}

			#if PM200_PRESENTE==0
				ModbusSetSlave(MODBUS_PM210);	/* Leitura dos dados de teste */
			#endif
			
			/* Detecta equipamentos de medição e faz a leitura dos dados */	
				
			/* PM210 input registers */		
			Modbus_GetData(PM210_SLAVE_ADDRESS, FC_READ_INPUT_REGISTERS, (INT8U*)&PM210_IRList1.Regs[PM210_REG_OFFSET], 
					PM210_REGLIST1_INPUT_START, PM210_REGLIST1_INPUT_NREGS);	
			
			/* Get and set timestamp of reading */			
			GetCalendarTime(&timestamp);	
			//	unix_ts = ConvertDateTimeToUnixTime(&timestamp);	
			SetTimeStamp(MODBUS_PM210, (INT8U*)PM210_IRList1.Regs, &timestamp);
			
			Modbus_GetData(PM210_SLAVE_ADDRESS, FC_READ_INPUT_REGISTERS, (INT8U*)&PM210_IRList2.Regs[PM210_REG_OFFSET], 
								PM210_REGLIST2_INPUT_START, PM210_REGLIST2_INPUT_NREGS);
			
			/* Get and set timestamp of reading */
			GetCalendarTime(&timestamp);
			SetTimeStamp(MODBUS_PM210, (INT8U*)PM210_IRList2.Regs, &timestamp);
			
			/* TS input registers */	
			Modbus_GetData(TS_SLAVE_ADDRESS, FC_READ_INPUT_REGISTERS, &TS_IRList.Regs[TS_REG_OFFSET], 
					TS_REG_INPUT_START, TS_REG_INPUT_NREGS); 

			/* Get and set timestamp of reading */
			GetCalendarTime(&timestamp);
			SetTimeStamp(MODBUS_PM210, TS_IRList.Regs, &timestamp);
								
			/* Abre arquivo atual, escreve os dados coletados no arquivo atual  e fecha o aquivo */
			WriteFile(&file_obj, LogFileName, (INT8U*)PM210_IRList1.Regs, PM210_REGLIST1_INPUT_NREGS*2+4);
			WriteFile(&file_obj, LogFileName, (INT8U*)PM210_IRList2.Regs, PM210_REGLIST2_INPUT_NREGS*2+4);
			WriteFile(&file_obj, LogFileName, TS_IRList.Regs, TS_REG_INPUT_NREGS+4);
			
		}				
	}
}

INT32U GetFileCreationDate (char fileName[])
{
	INT32U res; 
	fileName[8] = 0; // remove file extension 	 
	res = StringToInteger(fileName);
	fileName[8] = '.'; // restore file extension 
	return res;
}

INT8U SetTimeStamp (INT8U device_id, INT8U *data_ptr, OSTime *timestamp)
{
	
	if(timestamp == NULL) return FALSE;
	
	data_ptr[0] = device_id;
	data_ptr[1] = timestamp->RTC_Hour;
	data_ptr[2] = timestamp->RTC_Minute;
	data_ptr[3] = timestamp->RTC_Second;
	
	return TRUE;
}


/* UTC time function  */

#define YEAR0                   1900
#define EPOCH_YR                1970
#define SECS_DAY                (24L * 60L * 60L)
#define LEAPYEAR(year)          (!((year) % 4) && (((year) % 100) || !((year) % 400)))
#define YEARSIZE(year)          (LEAPYEAR(year) ? 366 : 365)
#define FIRSTSUNDAY(timp)       (((timp)->tm_yday - (timp)->tm_wday + 420) % 7)
#define FIRSTDAYOF(timp)        (((timp)->tm_wday - (timp)->tm_yday + 420) % 7)

#define TIME_MAX                2147483647L

const int _ytab[2][12] = {
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int _daylight = 0;                  // Non-zero if daylight savings time is used
long _dstbias = 0;                  // Offset for Daylight Saving Time
long _timezone = 0;                 // Difference in seconds between GMT and local time

time_t mktime(struct tm *tmbuf) {
  long day, year;
  int tm_year;
  int yday, month;
  /*unsigned*/ long seconds;
  int overflow;
  long dst;

  tmbuf->tm_min += tmbuf->tm_sec / 60;
  tmbuf->tm_sec %= 60;
  if (tmbuf->tm_sec < 0) {
    tmbuf->tm_sec += 60;
    tmbuf->tm_min--;
  }
  tmbuf->tm_hour += tmbuf->tm_min / 60;
  tmbuf->tm_min = tmbuf->tm_min % 60;
  if (tmbuf->tm_min < 0) {
    tmbuf->tm_min += 60;
    tmbuf->tm_hour--;
  }
  day = tmbuf->tm_hour / 24;
  tmbuf->tm_hour= tmbuf->tm_hour % 24;
  if (tmbuf->tm_hour < 0) {
    tmbuf->tm_hour += 24;
    day--;
  }
  tmbuf->tm_year += tmbuf->tm_mon / 12;
  tmbuf->tm_mon %= 12;
  if (tmbuf->tm_mon < 0) {
    tmbuf->tm_mon += 12;
    tmbuf->tm_year--;
  }
  day += (tmbuf->tm_mday - 1);
  while (day < 0) {
    if(--tmbuf->tm_mon < 0) {
      tmbuf->tm_year--;
      tmbuf->tm_mon = 11;
    }
    day += _ytab[LEAPYEAR(YEAR0 + tmbuf->tm_year)][tmbuf->tm_mon];
  }
  while (day >= _ytab[LEAPYEAR(YEAR0 + tmbuf->tm_year)][tmbuf->tm_mon]) {
    day -= _ytab[LEAPYEAR(YEAR0 + tmbuf->tm_year)][tmbuf->tm_mon];
    if (++(tmbuf->tm_mon) == 12) {
      tmbuf->tm_mon = 0;
      tmbuf->tm_year++;
    }
  }
  tmbuf->tm_mday = day + 1;
  year = EPOCH_YR;
  if (tmbuf->tm_year < year - YEAR0) return (time_t) -1;
  seconds = 0;
  day = 0;                      // Means days since day 0 now
  overflow = 0;

  // Assume that when day becomes negative, there will certainly
  // be overflow on seconds.
  // The check for overflow needs not to be done for leapyears
  // divisible by 400.
  // The code only works when year (1970) is not a leapyear.
  tm_year = tmbuf->tm_year + YEAR0;

  if (TIME_MAX / 365 < tm_year - year) overflow++;
  day = (tm_year - year) * 365;
  if (TIME_MAX - day < (tm_year - year) / 4 + 1) overflow++;
  day += (tm_year - year) / 4 + ((tm_year % 4) && tm_year % 4 < year % 4);
  day -= (tm_year - year) / 100 + ((tm_year % 100) && tm_year % 100 < year % 100);
  day += (tm_year - year) / 400 + ((tm_year % 400) && tm_year % 400 < year % 400);

  yday = month = 0;
  while (month < tmbuf->tm_mon) {
    yday += _ytab[LEAPYEAR(tm_year)][month];
    month++;
  }
  yday += (tmbuf->tm_mday - 1);
  if (day + yday < 0) overflow++;
  day += yday;

  tmbuf->tm_yday = yday;
  tmbuf->tm_wday = (day + 4) % 7;               // Day 0 was thursday (4)

  seconds = ((tmbuf->tm_hour * 60L) + tmbuf->tm_min) * 60L + tmbuf->tm_sec;

  if ((TIME_MAX - seconds) / SECS_DAY < day) overflow++;
  seconds += day * SECS_DAY;

  // Now adjust according to timezone and daylight saving time
  if (((_timezone > 0) && (TIME_MAX - _timezone < seconds)) || 
      ((_timezone < 0) && (seconds < -_timezone))) {
          overflow++;
  }
  seconds += _timezone;

  if (tmbuf->tm_isdst) {
    dst = _dstbias;
  } else {
    dst = 0;
  }

  if (dst > seconds) overflow++;        // dst is always non-negative
  seconds -= dst;

  if (overflow) return (time_t) -1;

  if ((time_t) seconds != seconds) return (time_t) -1;
  return (time_t) seconds;
}


time_t ConvertDateTimeToUnixTime(OSDateTime * dt)
{
	struct tm tm;
	time_t unix_time;
	
	tm.tm_hour = dt->time.RTC_Hour;
	tm.tm_min = dt->time.RTC_Minute;
	tm.tm_sec = dt->time.RTC_Second;
	
	tm.tm_year = dt->date.RTC_Year - 1900;
	tm.tm_mon = dt->date.RTC_Month - 1;
	tm.tm_mday = dt->date.RTC_Day;	
	
	unix_time = mktime(&tm);
	
	return unix_time;
}

