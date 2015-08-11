#include "BRTOS.h"
#include "drivers.h"
#include "tasks.h"
#include "AppConfig.h"

#ifdef __cplusplus
extern "C"
#endif

/******************************************************************************
 * @file main_app.c
 * @author Carlos H. Barriquello
 * @brief   This software is the main entry of the project
 *****************************************************************************/


/******************************************************************************
 * @name        main_app
 * @brief       This function initializes the system and installs the application tasks
 * @param       None
 * @return      None
 *****************************************************************************/

void main_app(void)
{
	
#if 1

	/* init the MCU system */
	System_Init();

	/* Init BRTOS system */
	BRTOS_Init();

	/* Install task for keeping system clock time */
	if (InstallTask(&System_Time, "System Time", 256, 31, NULL) != OK)
	{
		while (1){};
	};
	
#if 0	
	if (InstallTask(&main_monitor, "Monitor 1", 1024, 10, NULL) != OK)
	{
		while (1){};
	};
#endif	

#if 0
	if (InstallTask(&Tarefa_termometro, "Tarefa de Termometro", 256, 19, NULL) != OK)
	{
		while (1){};
	};
#endif
	
#if 0
	if (InstallTask(&Tarefa_GPRS, "Tarefa do modem GPRS", 256, 28, NULL) != OK)
	{
		while (1){};
	};
#endif
	
#if TESTE_RS485
	if (InstallTask(&Tarefa_RS485, "Tarefa de teste RS485", 256, 5, NULL) != OK)
	{
		while (1){};
	};
#endif

#if 0
	if (InstallTask(&Tarefa_datalogger, "Datalogger", (384 + 256), 20, NULL) != OK)
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
	if (InstallTask(&Terminal_Task, "USB Terminal Task", 1024, 15, NULL) != OK)
	{
		while (1){};
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

