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

/** \addtogroup app
 *  @{
 Camada de tarefas/aplicações – contém as implementações da lógica do sistema de monitoramento
 */


#include "AppConfig.h"
#include "BRTOS.h"
#include "drivers.h"
#include "tasks.h"

#if COLDUINO || ARDUINO
#include "printf_lib.h"
#include "terminal.h"
#include "terminal_commands.h"
	#if COLDUINO
	#include "virtual_com.h"
	#endif
#endif

#include "led_onboard.h"
#include "simon-api.h"


/** \defgroup app_system_time	Relógio do sistema
 *  @{
 * Tarefa para manutenção e atualização do relógio/calendário do sistema e do cão-de-guarda (watchdog).
 */

 
 
#if ARDUINO
#define __RESET_WATCHDOG()	wdt_reset()
#define __ENABLE_WATCHDOG()	wdt_enable(WDTO_250MS)
#else
#define __ENABLE_WATCHDOG()	
#endif

/* Task to keep system date and time */
void System_Time(void)
{

	/* task setup */
	INT16U milis = 0;
	INT16U segundos = 0;
	
	#if (WATCHDOG == 1)	
		__ENABLE_WATCHDOG();
	#endif	
	
	OSResetTime();

	/* LED onboard ON */
	//led_onboard_on(RED_LED);
	
	#if RTC_PRESENTE
		while(Init_Calendar() == FALSE)
		{
			DelayTask(10);
			#if (WATCHDOG == 1)
				__RESET_WATCHDOG();
			#endif			
		}
	#endif	
	
	/* LED onboard OFF */
	//led_onboard_off(RED_LED);

	/* task main loop */
	for (;;)
	{
		#if (WATCHDOG == 1)
			__RESET_WATCHDOG();
		#endif     

		DelayTask(10);	/* delay 10ms */
		milis += 10;
		
		if (milis >= 1000) /* 1000ms ? */
		{
			milis = 0;
			
			/* update time and calendar */
			OSUpdateUptime();
			OSUpdateCalendar();
			
			/* update simon main clock - unix time */
			simon_clock_update();
			
			//led_onboard_toggle(YELLOW_LED);
			
			segundos++;
			if (segundos == 3600)
			{
				segundos = 0;
				
				#if RTC_PRESENTE				
					Resync_calendar();  /* resync with RTC every 3600s = 60min = 1h */
				#endif				
				
			}
		}
		
		/* FatFS Timer Handler  */	
		disk_timerproc();       
	}

}
/** @} */


#if COLDUINO
#include "user_config.h"
#if (USB_CLASS_TYPE == BRTOS_USB_MSD)
void Mass_Storage_Device_Task(void)
{
	/* task setup */
	(void)MSD_Init(); /* Initialize the USB Test Application */

	while(1)
	{
		/* Call the application task */
		MSD_Task();
	}
}
#endif
#endif


/** \defgroup app_terminal	Terminal de Comandos
 *  @{
 * Tarefa para processamento de comandos recebidos por terminal.
 */
 
 
/* Config terminal task */
#if ARDUINO
#define TERM_UART			0
#endif

#define TERM_BUFSIZE		36
#define TERM_MUTEX			TRUE
#define TERM_BAUDRATE		19200

#if TERM_UART == 0
#define TERM_MUTEX_PRIO		UART0_MUTEX_PRIO
#define TERM_OUTPUT			putchar_uart0
#elif  TERM_UART == 1
#define TERM_MUTEX_PRIO		UART1_MUTEX_PRIO
#define TERM_OUTPUT			putchar_uart1
#else
#define TERM_MUTEX_PRIO		UART2_MUTEX_PRIO
#define TERM_OUTPUT			putchar_uart2
#endif

/* Task to process terminal commands */
#include "terminal_io.h"	

void Terminal_Task(void)
{
	/* task setup */
	/* Init the Term UART */
#ifdef TERM_UART		
	uart_init(TERM_UART,BAUD(TERM_BAUDRATE),TERM_BUFSIZE,TERM_MUTEX,TERM_MUTEX_PRIO);
	
#if !SIMULATION
	terminal_set_output(TERM_OUTPUT);
#endif

#endif	
			
#if COLDUINO	
#if (USB_CLASS_TYPE == BRTOS_USB_CDC)		
	(void) CDC_Init();  /* Init the USB CDC Application */
	terminal_init(putchar_usb);
#endif
#elif ARDUINO
	terminal_init(terminal_output);
#endif
	
	/* Add terminal commands */
	(void) terminal_add_cmd((command_t*) &ver_cmd);
	(void) terminal_add_cmd((command_t*) &top_cmd);
	#if COLDUINO
		(void) terminal_add_cmd((command_t*) &rst_cmd);
	#endif
	//(void) terminal_add_cmd((command_t*) &temp_cmd);
	//(void) terminal_add_cmd((command_t*) &setget_time_cmd);
	(void) terminal_add_cmd((command_t*) &cat_cmd);
	(void) terminal_add_cmd((command_t*) &ls_cmd);
	(void) terminal_add_cmd((command_t*) &cd_cmd);
	(void) terminal_add_cmd((command_t*) &mount_cmd);
	(void) terminal_add_cmd((command_t*) &sr_cmd);
	(void) terminal_add_cmd((command_t*) &rm_cmd);
	(void) terminal_add_cmd((command_t*) &rn_cmd);
	(void) terminal_add_cmd((command_t*) &cr_cmd);
	(void) terminal_add_cmd((command_t*) &mkdir_cmd);
	(void) terminal_add_cmd((command_t*) &cp_cmd);
	//(void) terminal_add_cmd((command_t*) &wt_cmd);
	(void) terminal_add_cmd((command_t*) &echo_cmd);
	(void) terminal_add_cmd((command_t*) &echo_stdout_cmd);
	//(void) terminal_add_cmd((command_t*) &esp_cmd);
	//(void) terminal_add_cmd((command_t*) &m590_cmd);	
	//(void) terminal_add_cmd((command_t*) &null_modem_cmd);	
	(void) terminal_add_cmd((command_t*) &modem_cmd);
	(void) terminal_add_cmd((command_t*) &modbus_cmd);
	(void) terminal_add_cmd((command_t*) &monitor_cmd);
		
	terminal_acquire();
	printf_terminal_P(PSTR("Terminal started\r\n"));
	terminal_release();
	
	while (1)
	{
		#if !SIMULATION
			/* process incoming terminal commands */
			terminal_process();
		#else
			DelayTask(1000);
		#endif		
	}
}
/** @} */


/** @} */




