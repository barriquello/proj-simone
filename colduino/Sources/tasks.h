/**
* \file tasks.h
* \brief Task function prototypes.
*
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
*                                              OS Tasks
*
*
*   Author:   Gustavo Weber Denardin
*   Revision: 1.0
*   Date:     20/03/2009
*
*********************************************************************************************************/

void System_Time(void);

void Terminal_Task(void);
void Mass_Storage_Device_Task(void);

void HMI(void);
void Keyboard_Handler(void);

void Tarefa_termometro(void);
void Tarefa_datalogger(void);
void Tarefa_GPRS(void);

void Tarefa_RS485(void);

void Task_modbus_slave_test(void);
void Task_modbus_slave(void);

void Task_modbus_master_test(void);
