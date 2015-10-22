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

#if COLDUINO || ARDUINO
#include "printf_lib.h"
#include "terminal.h"
#include "terminal_commands.h"
#endif

#if COLDUINO
#include "virtual_com.h"
#endif

#include "led_onboard.h"

#if ARDUINO
#define __RESET_WATCHDOG()	wdt_reset()
#endif

/* Task to keep system date and time */
void System_Time(void)
{

	/* task setup */
	INT16U milis = 0;
	INT16U segundos = 0;
	
	OSResetTime();

	/* LED onboard ON */
	led_onboard_on();
	
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
	led_onboard_off();

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

#define TERM_UART1   0
#define TERM_UART2   0

/* Task to process terminal commands */
void Terminal_Task(void)
{
	/* task setup */
	
	/* Init the UART 1 */
	#if ENABLE_UART1 && TERM_UART1
	#define UART1_BUFSIZE	256
	#if UART1_MUTEX
	uart_init(1,9600,UART1_BUFSIZE,TRUE,UART1_MUTEX_PRIO);
	#else
	uart_init(1,9600,UART1_BUFSIZE,FALSE,0);
	#endif
	#endif

	/* Init the UART 2 */
	#if ENABLE_UART2 && TERM_UART2
	#define UART2_BUFSIZE	256
	#if UART2_MUTEX
	uart_init(2,9600,UART2_BUFSIZE,TRUE,UART2_MUTEX_PRIO);
	#else
	uart_init(2,9600,UART2_BUFSIZE,FALSE,0);
	#endif
	#endif
		
#if COLDUINO	
#if (USB_CLASS_TYPE == BRTOS_USB_CDC)		
	(void) CDC_Init();  /* Init the USB CDC Application */
	terminal_init(putchar_usb);
#endif
#elif ARDUINO
	#include "terminal_io.h"
	terminal_init(terminal_output);
#endif

	/* Add terminal commands */
	//(void) terminal_add_cmd((command_t*) &ver_cmd);
	//(void) terminal_add_cmd((command_t*) &top_cmd);
	// (void) terminal_add_cmd((command_t*) &rst_cmd);
	//(void) terminal_add_cmd((command_t*) &temp_cmd);
	//(void) terminal_add_cmd((command_t*) &setget_time_cmd);
	//(void) terminal_add_cmd((command_t*) &cat_cmd);
	//(void) terminal_add_cmd((command_t*) &ls_cmd);
	//(void) terminal_add_cmd((command_t*) &cd_cmd);
	//(void) terminal_add_cmd((command_t*) &mount_cmd);
	//(void) terminal_add_cmd((command_t*) &sr_cmd);
	//(void) terminal_add_cmd((command_t*) &rm_cmd);
	//(void) terminal_add_cmd((command_t*) &rn_cmd);
	//(void) terminal_add_cmd((command_t*) &cr_cmd);
	//(void) terminal_add_cmd((command_t*) &mkdir_cmd);
	//(void) terminal_add_cmd((command_t*) &cp_cmd);
	//(void) terminal_add_cmd((command_t*) &wt_cmd);
	// (void) terminal_add_cmd((command_t*) &echo_cmd);
	// (void) terminal_add_cmd((command_t*) &echo_stdout_cmd);
	//(void) terminal_add_cmd((command_t*) &esp_cmd);
	//(void) terminal_add_cmd((command_t*) &m590_cmd);	
	//(void) terminal_add_cmd((command_t*) &modbus_cmd);	

	while (1)
	{
		/* process incoming terminal commands */
		terminal_process();
	}
}


#if 0
void BRTOS_TimerHook(void)
{

}
#endif

