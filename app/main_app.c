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
#include "AppConfig.h"
#include "BRTOS.h"
#include "drivers.h"
#include "tasks.h"
#include "modbus.h"
#include "modbus_slave_null.h"


#ifdef __cplusplus
extern "C"
#endif

/******************************************************************************
 * \file main_app.c
 * \author Carlos H. Barriquello
 * \brief   This software is the main entry of the project
 *****************************************************************************/

#define TaskName_SystemTime_def		"System Time"
#define TaskName_Monitors_def		"Monitors"
#define TaskName_Terminal_def		"Terminal"

#if ARDUINO

#if (__GNUC__)
#define CONST const
#else
#define CONST 
#endif

const CHAR8 TaskName_SystemTime_str[] PROGMEM = TaskName_SystemTime_def;
const CHAR8 TaskName_Monitors_str[] PROGMEM = TaskName_Monitors_def;
const CHAR8 TaskName_Terminal_str[] PROGMEM = TaskName_Terminal_def;

PGM_P CONST MainStringTable[] PROGMEM =
{
	TaskName_SystemTime_str,
	TaskName_Monitors_str,
	TaskName_Terminal_str
};
#define	TaskName_SystemTime (PGM_P)pgm_read_word((&(MainStringTable[0])))
#define TaskName_Monitors   (PGM_P)pgm_read_word((&(MainStringTable[1])))
#define	TaskName_Terminal   (PGM_P)pgm_read_word((&(MainStringTable[2])))
#else
#define	TaskName_SystemTime TaskName_SystemTime_def
#define TaskName_Monitors   TaskName_Monitors_def
#define	TaskName_Terminal   TaskName_Terminal_def
#endif


/******************************************************************************
 * \name        main_app
 * \brief       This function initializes the system and installs the application tasks
 * \param       None
 * \return      None
 *****************************************************************************/
#include "stdint.h"
char check_ints(void)
{
	if(sizeof(uint8_t) != 1) return 0;
	if(sizeof(uint16_t) != 2) return 0;
	if(sizeof(uint32_t) != 4) return 0;	
	if(sizeof(INT8U) != 1) return 0;
	if(sizeof(INT16U) != 2) return 0;
	if(sizeof(INT32U) != 4) return 0;
	if(sizeof(BYTE) != 1) return 0;
	if(sizeof(WORD) != 2) return 0;
	if(sizeof(DWORD) != 4) return 0;
	
	return 1;
}

char str[] = "Config";

void main_app(void)
{
	
	/* init the MCU system */
	System_Init();

	if(check_ints() == 0)
	{
		while(1){}
	}

	/* Init BRTOS system */
	BRTOS_Init();	
	
#if (COLDUINO || ARDUINO) && !SIMULATION
	led_onboard_init();	 /* Init LED onboard */
	Modbus_init(); 		 /* Init Modbus */
	Modus_slave_null_init(); /* Init Modbus Slave Null */
#endif	

	/* Install task for keeping system clock, date and time */
	if (InstallTask(&System_Time, TaskName_SystemTime, TASK_STACKSIZE_SYSTEM_TIME, TASK_PRIORITY_SYSTEM_TIME, NULL) != OK)
	{
		sleep_forever();
	};
	
#if 1	
	if (InstallTask(&main_monitor, TaskName_Monitors, TASK_STACKSIZE_MONITORS, TASK_PRIORITY_MONITORS, NULL) != OK)
	{
		sleep_forever();
	};
#endif	
	
#if TESTE_MODBUS

	if (InstallTask(&Task_modbus_slave, "MB slave", 256, 5, NULL) != OK)
	{
		while (1){}
	}
	

	if (InstallTask(&Task_modbus_slave_test, "MB slave test", 256, 6, NULL) != OK)
	{
		while (1){}
	}
	
#if TESTE_MODBUS_SLAVE
#if (TESTE_MODBUS_MASTER == 1)	
	
	if (InstallTask(&Task_modbus_master_test, "MB master test", (384+64), 5, NULL) != OK)
	{
		while (1){}
	}
#endif
#endif	
	
#endif	
	
#if USB_DEVICE_ENABLED && (USB_CLASS_TYPE == BRTOS_USB_MSD)
	if(InstallTask(&Mass_Storage_Device_Task,"Mass Storage Device Task",TASK_STACKSIZE_MSD,TASK_PRIORITY_TERMINAL,NULL) != OK)
	{
		while(1)
		{};
	};
#endif


#if (USB_DEVICE_ENABLED && (USB_CLASS_TYPE == BRTOS_USB_CDC)) || ARDUINO
	if (InstallTask(&Terminal_Task, TaskName_Terminal, TASK_STACKSIZE_TERMINAL, TASK_PRIORITY_TERMINAL, NULL) != OK)
	{
		sleep_forever();
	};
#endif

	/* Start Task Scheduler */
	if (BRTOSStart() != OK)
	{
		while (1){};
	};

}

/* function to handle any system error */
#if COLDUINO || ARDUINO
#include "led_onboard.h"
#endif

#undef PRINTS_ENABLED
#define PRINTS_ENABLED  1
#include "prints_def.h"

void sleep_forever(void)
{

	PRINTS_ERRO_P(PSTR("Sleeping forever ..."));
	while(1)
	{
		#if COLDUINO || ARDUINO
			/* sleep forever */
			led_onboard_on();
			DelayTask(500); 
			led_onboard_off();
			DelayTask(500);
		#endif
	}
}


/* function to handle printf/scanf */
#if COLDUINO && !__GNUC__

#include "terminal.h"

void InitializeUART(void);
void WriteUARTN(char c);
char ReadUARTN(void);

void InitializeUART(void)
{
		
}


void WriteUARTN(char c)
{
	putchar_terminal(c);	
}


char ReadUARTN(void)
{
	char c;
	getchar_terminal(&c);
	return c;
}
#endif




