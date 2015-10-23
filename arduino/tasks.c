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

#if PLATAFORMA == COLDUINO
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

#if 0

void Task_2(void)
{
   /* task setup */
   INT8U cont = 0;   
  
   /* task main loop */
   for (;;)
   {
	  cont++;
      (void)DelayTask(20);
	  PORTB = PORTB ^ 2;
      
      //Acorda a tarefa 3
      (void)OSSemPost(SemTeste);
   }
}



void Task_3(void)
{
   /* task setup */
   PORTB = 0x00;
   DDRB = 0xFF;
  
   /* task main loop */
   for (;;)
   {
      PORTB = PORTB ^ 1;
	  (void)OSSemPend(SemTeste,0);
   }
}
#endif

#if 0
#include "OSInfo.h"

char BufferTextDebug[128];
extern BRTOS_Sem    *SemTeste;
extern BRTOS_Queue  *Serial;

void Task_Serial(void)
{
    /* task setup */
    INT8U pedido = 0;  
  
	strcpy_P(BufferText, (PGM_P)pgm_read_word(&(BRTOSStringTable[0])));
	Serial_Envia_Frase((CHAR8*)BufferText);
			
	Serial_Envia_Caracter(10);
	Serial_Envia_Caracter(13);
			
   // task main loop
   for (;;) 
   {

      if(!OSQueuePend(Serial, &pedido, 0))
      {
		switch(pedido)
        {
          
		  #if (COMPUTES_CPU_LOAD == 1)
          case '1':
            Transmite_CPU_Load();
			//OSCPULoad(BufferTextDebug);
			//Serial_Envia_Frase((CHAR8*)BufferTextDebug);
			Serial_Envia_Caracter(10);
			Serial_Envia_Caracter(13);			
            break;
          #endif
          case '2':
            Transmite_Uptime();
			//OSUptimeInfo(BufferTextDebug);
			//Serial_Envia_Frase((CHAR8*)BufferTextDebug);
			Serial_Envia_Caracter(10);
			Serial_Envia_Caracter(13);			
            break;
          case '3':			
            strcpy_P(BufferText, (PGM_P)pgm_read_word(&(BRTOSStringTable[0])));
            Serial_Envia_Frase((CHAR8*)BufferText);
			
            Serial_Envia_Caracter(10);
            Serial_Envia_Caracter(13);
            break;
          case '4':
            //Transmite_RAM_Ocupada();
			OSAvailableMemory(BufferTextDebug);
			Serial_Envia_Frase((CHAR8*)BufferTextDebug);
			Serial_Envia_Caracter(10);
			Serial_Envia_Caracter(13);			
            break;
		  case '5':
            Transmite_Task_Stacks();
			//OSTaskList(BufferTextDebug);
			//Serial_Envia_Frase((CHAR8*)BufferTextDebug);
			Serial_Envia_Caracter(10);
			Serial_Envia_Caracter(13);			
            break;
          #if (OSTRACE == 1) 
          case '6':
            Send_OSTrace();
            Serial_Envia_Caracter(LF);
            Serial_Envia_Caracter(CR);            
            break;            
          #endif                                    
          default:
            Serial_Envia_Caracter(pedido);
            break;
        }
      }
   }
}
#endif
