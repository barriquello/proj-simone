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


/******************************************************************************
 * \name        main_app
 * \brief       This function initializes the system and installs the application tasks
 * \param       None
 * \return      None
 *****************************************************************************/

void main_app(void)
{
	
#if 1

	/* init the MCU system */
	System_Init();

	/* Init BRTOS system */
	BRTOS_Init();	
	
#if COLDUINO	
	led_onboard_init();	 /* Init LED onboard */
	Modbus_init(); 		 /* Init Modbus */
	Modus_slave_null_init(); /* Init Modbus Slave Null */
#endif	

	/* Install task for keeping system clock, date and time */
	if (InstallTask(&System_Time, "System Time", 256+64, 31, NULL) != OK)
	{
		sleep_forever();
	};
	
#if 1	
	if (InstallTask(&main_monitor, "Monitors", 1024+1024+512, 10, NULL) != OK)
	{
		sleep_forever();
	};
#endif	
	
#if TESTE_RS485
	if (InstallTask(&Tarefa_RS485, "Tarefa de teste RS485", 256, 5, NULL) != OK)
	{
		while (1){};
	};
#endif

#if TESTE_MODBUS

	if (InstallTask(&Task_modbus_slave, "MB slave", 256, 23, NULL) != OK)
	{
		while (1){}
	}
	

	if (InstallTask(&Task_modbus_slave_test, "MB slave test", 256, 22, NULL) != OK)
	{
		while (1){}
	}
	
#if TESTE_MODBUS_SLAVE
#if (defined TESTE_MODBUS_MASTER && TESTE_MODBUS_MASTER == 1)	
	
	if (InstallTask(&Task_modbus_master_test, "MB master test", (384+64), 21, NULL) != OK)
	{
		while (1){}
	}
#endif
#endif	
	
#endif	
	
#if USB_DEVICE_ENABLED == 1
#if (USB_CLASS_TYPE == BRTOS_USB_MSD)
	if(InstallTask(&Mass_Storage_Device_Task,"Mass Storage Device Task",512,15,NULL) != OK)
	{
		while(1)
		{};
	};
#endif


#if (USB_CLASS_TYPE == BRTOS_USB_CDC)
	if (InstallTask(&Terminal_Task, "Terminal", 1024, 15, NULL) != OK)
	{
		sleep_forever();
	};
#endif
#endif


#if 0
	if(InstallTask(&HMI,"Human-Machine Interface task",416,10,NULL) != OK)
	{
		while(1)
		{};
	};

	if(InstallTask(&Keyboard_Handler,"Keyboard handler task",416,12,NULL) != OK)
	{
		while(1)
		{};
	};
#endif

	/* Start Task Scheduler */
	if (BRTOSStart() != OK)
	{
		while (1){};
	};
#endif	
}

/* function to handle any system error */
#if PLATAFORMA==COLDUINO
#include "led_onboard.h"
#endif

void sleep_forever(void)
{

	while(1)
	{
		#if PLATAFORMA==COLDUINO
			/* sleep forever */
			led_onboard_on();
			DelayTask(500); 
			led_onboard_off();
			DelayTask(500);
		#endif
	}
}


/* function to handle printf/scanf */
#if PLATAFORMA==COLDUINO

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




