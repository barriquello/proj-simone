///////////////////////////////////////////////////////////////
/////                                                     /////
/////                   User App Defines                  /////
/////                                                     /////
/////             !User App configuration defines!        /////
/////                                                     /////
///////////////////////////////////////////////////////////////
#include "user_config.h"


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

#define USB_DEVICE_ENABLED	  1

#if USB_DEVICE_ENABLED == 1
#define ENABLE_USB 			  1
#endif

#define TESTE_MODBUS    	  0
#define TESTE_MODBUS_SLAVE    0
#define TESTE_MODBUS_MASTER   0
#define TESTE_RS485			  0

#define DATALOGGER_DELAY_TIME (3000)

//#define WIN32    	0
#define COLDUINO 	1
//#define ARDUINO 	2

#define PLATAFORMA  COLDUINO

#ifndef CONST
#define CONST const
#endif







