///////////////////////////////////////////////////////////////
/////                                                     /////
/////                   User App Defines                  /////
/////                                                     /////
/////             !User App configuration defines!        /////
/////                                                     /////
///////////////////////////////////////////////////////////////

#define SD_PRESENTE         1 
#define RTC_PRESENTE  		0
#define GPRSMODEM_PRESENTE  0
#define PM200_PRESENTE   	0
#define TS_PRESENTE   		0
#define NULL_PRESENTE   	1

#if RTC_PRESENTE
#include "Timer_RTC_DS1307.h"
#endif

#if SD_PRESENTE
#include "SD_API.h"
#define SDCARD_MUTEX_PRIORITY 	29
#endif

#define USB_DEVICE_ENABLED	  0
#define TESTE_MODBUS    	  0
#define TESTE_MODBUS_SLAVE    0
#define TESTE_MODBUS_MASTER   0
#define TESTE_RS485			  0

#define DATALOGGER_DELAY_TIME (3000)

//#define WIN32    	0
//#define COLDUINO 	1
#define ARDUINO 	2

#define PLATAFORMA  ARDUINO

#ifndef CONST
#define CONST const
#endif

#if COLDUINO
#define TASK_STACKSIZE_SYSTEM_TIME		(256+64)
#define TASK_STACKSIZE_MONITORS			(1024*2+512)
#define TASK_STACKSIZE_TERMINAL			(1024)

#define TASK_PRIORITY_SYSTEM_TIME		15
#define TASK_PRIORITY_MONITORS			10
#define TASK_PRIORITY_TERMINAL			5

#elif ARDUINO
#define TASK_STACKSIZE_SYSTEM_TIME		(128)
#define TASK_STACKSIZE_MONITORS			(1024)
#define TASK_STACKSIZE_TERMINAL			(256)

#define TASK_PRIORITY_SYSTEM_TIME		7
#define TASK_PRIORITY_MONITORS			3
#define TASK_PRIORITY_TERMINAL			2
#endif

#include "BRTOSConfig.h"
#define TASK_STACKSIZE_TOTAL		((TASK_STACKSIZE_SYSTEM_TIME)+(TASK_STACKSIZE_MONITORS)+(TASK_STACKSIZE_TERMINAL))

#if HEAP_SIZE < ((TASK_STACKSIZE_TOTAL) + (IDLE_STACK_SIZE))
#error "Must increase HEAP_SIZE"
#endif






