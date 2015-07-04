/*
 * datalogger.c
 *
 *  Created on: 2014
 *      Author: Carlos H. Barriquello
 */

#include "datalogger.h"
#include "printf_lib.h"
#include "time_lib.h"
#include "BRTOS.h"
#include "debug_stack.h"
#include "SD_API.h"
#include "utils.h"
#include "Timer_RTC_DS1307.h"
#include "eeprom.h"
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


