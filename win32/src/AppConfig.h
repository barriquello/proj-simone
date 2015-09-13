///////////////////////////////////////////////////////////////
/////                                                     /////
/////                   User App Defines                  /////
/////                                                     /////
/////             !User App configuration defines!        /////
/////                                                     /////
///////////////////////////////////////////////////////////////
#ifndef _WIN32
#include "user_config.h"
#endif


#define SD_PRESENTE         0
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



#ifdef _WIN32
#ifndef WIN32
#define WIN32 1
#endif
#define PLATAFORMA  WIN32
#endif

#ifndef CONST
#define CONST const
#endif







