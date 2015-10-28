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
#include "BRTOS.h"
#include "debug_stack.h"
#include "utils.h"
#include "terminal.h"
#include "uart.h"
#include "terminal_io.h"

#include "AppConfig.h"
#include "printf_lib.h"

#if COLDUINO || ARDUINO
#if !__GNUC__
#pragma warn_implicitconv off
#endif
#define DEBUG_STACK_PRINT 1
#else
#ifdef _WIN32
#define DEBUG_STACK_PRINT 1
#endif
#endif

#if DEBUG_STACK_PRINT
#if COLDUINO
#define DPRINTF(a,...) printSer(a,__VA_ARGS__);
#define DPUTCHAR(a,b)  putcharSer(a,b);
#elif ARDUINO
#define DPRINTF(a,...)		printSer(a,__VA_ARGS__);
#define DPRINTF_P(a,...)	printSer_P(a,__VA_ARGS__);
#define DPUTCHAR(a,b)		putcharSer(a,b);
#endif
#else
#ifndef UNUSED
#define UNUSED(a)		(void)((a))
#endif
#define DPRINTF(a,...)	UNUSED((a));
#define DPUTCHAR(a,b)	UNUSED((a));UNUSED((b));
#endif

#define UptimeText_def		"UPTIME: %d d %d h %d m %d s\n\r"
#define MemoryText_def		"MEMORY: %d of %d\n\r"
#define CPULoadText_def		"CPU LOAD: %d.%d%%\n\r"
#define TaskStackText_def	"\n\rTASK STACK:\n\r"
#define MemoryTextOf_def	": %d of %d\r\n"
#define TaskName_def		 "[%d]"


#if ARDUINO
const CHAR8 UptimeText_str[] PROGMEM = UptimeText_def;
const CHAR8 CPULoadText_str[] PROGMEM = CPULoadText_def;
const CHAR8 TaskStackText_str[] PROGMEM = TaskStackText_def;
const CHAR8 MemoryText_str[] PROGMEM = MemoryText_def;
const CHAR8 MemoryTextOf_str[] PROGMEM = MemoryTextOf_def;
const CHAR8 TaskName_str[] PROGMEM = TaskName_def;

PGM_P CONST DebugStringTable[] PROGMEM =
{
	UptimeText_str,
	CPULoadText_str,
	TaskStackText_str,
	MemoryText_str,
	MemoryTextOf_str,
	TaskName_str
};

#define UptimeText		(&(DebugStringTable[0]))
#define CPULoadText		(&(DebugStringTable[1]))
#define TaskStackText	(&(DebugStringTable[2]))
#define MemoryText		(&(DebugStringTable[3]))
#define MemoryTextOf	(&(DebugStringTable[4]))
#define TaskNameText	(&(DebugStringTable[5]))

#elif COLDUINO
#define UptimeText		UptimeText_def
#define MemoryText		MemoryText_def
#define MemoryTextOf	MemoryTextOf_def
#define CPULoadText		CPULoadText_def
#define TaskStackText	TaskStackText_def
#define TaskNameText	TaskName_def
#endif


#if COLDUINO || ARDUINO
void Transmite_Uptime(INT8U Comm)
{
   OSTime Uptime;
   OSDate UpDate;
   CHAR8  string[32];
   
   UserEnterCritical();
   	   Uptime = OSUptime();
   	   UpDate = OSUpDate();
   UserExitCritical();
   
   SNPRINTF(string,SIZEARRAY(string),UptimeText,
		   UpDate.RTC_Day,Uptime.RTC_Hour,Uptime.RTC_Minute,Uptime.RTC_Second);   
   DPRINTF(Comm,string);
}


void Transmite_RAM_Ocupada(INT8U Comm)
{
    INT16U SPAddress = 0;
    CHAR8  string[32]; 
    
    UserEnterCritical();
    	SPAddress = iStackAddress * sizeof(OS_CPU_TYPE);
    UserExitCritical();    
    
    SNPRINTF(string,SIZEARRAY(string),MemoryText,SPAddress,HEAP_SIZE);
    DPRINTF(Comm, string);
}

#include "stdlib.h" 
#if SP_SIZE == 16
typedef INT16U sp_t;
#else
typedef INT32U sp_t;
#endif

void Transmite_Task_Stacks(INT8U Comm)
{
    INT8U  j = 0;
	INT8U  k = 0;
    CHAR8  string[32];
    sp_t *x = 0;
    sp_t *i = 0; 
    sp_t *p = 0; 
   
    STRCPY(string,TaskStackText);
    DPRINTF(Comm, string);  
    
	j = 0;      
    do
    {  
     if(++j > NumberOfInstalledTasks) 
	 {
		j = NUMBER_OF_TASKS+1;
		k = NumberOfInstalledTasks;
	 }else
	 {		 
		k = j-1;
	 }
	 
     SNPRINTF(string,SIZEARRAY(string),TaskNameText,j);
	 DPRINTF(Comm, string);
	 STRCPY_P(string,(ContextTask[j].TaskName));
	 DPRINTF(Comm, string);     
      
      UserEnterCritical();
      i = (sp_t*)ContextTask[j].StackPoint;
      if (j == 1)
      {
    	  x = (sp_t*)&STACK[0];
      }else
      {		  
		x = (sp_t*)ContextTask[k].StackInit;    	  
      }
      UserExitCritical();  
      
      p = x;      
	  #if (STACK_MARK && ARDUINO)
		p = p+4;
	  #endif
      while(*p++ == 0 && p<i){}         
      
	  i = (sp_t*)ContextTask[j].StackInit;
      SNPRINTF(string,SIZEARRAY(string),MemoryTextOf,(i - p)*sizeof(sp_t), (i - x)*sizeof(sp_t));      
      DPRINTF(Comm, string);
    } while(j < NUMBER_OF_TASKS+1);	
}


#if (COMPUTES_CPU_LOAD == 1)
void Transmite_CPU_Load(INT8U Comm)
{
    INT32U percent = 0;
    CHAR8  string[20]; 
   
    UserEnterCritical();
    	percent = LastOSDuty;
    UserExitCritical(); 
    
    if (percent > 1000)
    {
    	percent = 1000; 
    }    
    
    SNPRINTF(string,SIZEARRAY(string),CPULoadText,percent/10,percent%10);
    DPRINTF(Comm, string);

}
#endif

void Reason_of_Reset(INT8U Comm)
{  
  INT8U reason = 0;
  CHAR8  string[5];
  
#if COLDUINO
  reason = SRS;
  DPRINTF(Comm, "Reset caused by ");
  switch(reason)
  {
  
    case 0b00000000:
      DPRINTF(Comm, "BDM");
      break;
      
    case 0b00000010:
      DPRINTF(Comm, "low voltage");
      break;      
      
    case 0b00001000:
      DPRINTF(Comm, "illegal address");
      break;
      
    case 0b00010000:
      DPRINTF(Comm, "illegal opcode");
      break;
      
    case 0b00100000:
      DPRINTF(Comm, "watchdog");
      break;
      
    case 0b01000000:
      DPRINTF(Comm, "reset pin");
      break;
      
    case 0b10000010:
    case 0b10000000:
      DPRINTF(Comm, "POR (Cold reset)");
      break;
      
    default:
      DPRINTF(Comm, "unknown reason - Code: ");
      Print3Digits(reason, NO_ALIGN, string);
      DPRINTF(Comm, string);
      break;
  }
#endif  
}
#endif

#if (OSTRACE == 1) 
/* OS trace function */
/* coded as 8 bit: 0xTTTTTSSS 
- T: task bits (1-31: task id, 0: ISR) 
- S: syscall (
0: DELAYTASK, 1: SEMPEND, 2: QUEUEPEND, 3: MUTEXPEND
4: SEMPOST, 5: QUEUEPOST, 6: MUTEXPOST, 7: OS_IDLE
0x00: undefined
*/

static INT8U OSTrace[MAX_DEPTH_TRACE];
static INT8U OSTrace_snapshot[MAX_DEPTH_TRACE];
static INT8U index;


// update OSTrace history
void Update_OSTrace (INT8U task, INT8U syscall)
{   
  OSTrace[index] = (INT8U)((task << 5) | syscall);
  
  index++; 
  if(index == MAX_DEPTH_TRACE)
  {
    index=0;
  }
}

// send OSTrace to serial
void Send_OSTrace(INT8U Comm){
  
  #if (NESTING_INT == 1)
  INT16U CPU_SR = 0;
  #endif
  INT8U i=0;
  INT8U j=0;
  const CHAR8 *TaskName;
  
  OSEnterCritical();
  for(i=index, j=0;i<MAX_DEPTH_TRACE;i++,j++){
    OSTrace_snapshot[j] = OSTrace[i];
    OSTrace[i] = 0; // clear history
  }
  
  for(i=0;i<index;i++,j++){
    OSTrace_snapshot[j] = OSTrace[i];
    OSTrace[i] = 0; // clear history
  }
  index = 0;  
  OSExitCritical();
  
  j=0;
  do{      
    for(i=j;i<(j+MAX_TRACE_LINE);i++)
    {
        if(!(OSTrace_snapshot[i]>>5))
        {
            switch(OSTrace_snapshot[i] & 0x07)
            {
              case ISR_ONLY:
                DPRINTF(Comm, "ISR ONLY"); 
                break;         
              case ISR_TICK:
                #if(OS_TICK_SHOW == 1)  
                  DPRINTF(Comm, "ISR TICK"); 
                #endif
                break;
              case SEMPOST:
                DPRINTF(Comm, "ISR SEMPOST");        
                break;
              case QUEUEPOST:
                DPRINTF(Comm, "ISR QUEUEPOST");
                break;
              case MUTEXPOST:
                DPRINTF(Comm, "ISR MUTEXPOST");
                break;
              case OS_IDLE:
                #if(OS_IDLE_SHOW == 1)
                  DPRINTF(Comm, "ISR IDLE");
                #endif
                break; 
              default:
                DPRINTF(Comm, "________");
                break;
            }
        }else
        {
           #if(OS_IDLE_SHOW == 1)  
            DPRINTF(Comm, "TASK ");
            car = OSTrace_snapshot[i]>>5;
            car = (car / 10) + 48;
            DPUTCHAR(Comm, car);
            car = OSTrace_snapshot[i]>>5;
            car = (car%10) + 48;
            DPUTCHAR(Comm, car);
            DPUTCHAR(Comm, ' ');
          #else
           if((OSTrace_snapshot[i]>>5) != (NUMBER_OF_TASKS+1))
           {
              TaskName = ContextTask[OSTrace_snapshot[i]>>5].TaskName;
              DPRINTF(Comm, TaskName);
              DPUTCHAR(Comm, ' ');
           }
          #endif  
            
            switch(OSTrace_snapshot[i] & 0x07){
              case DELAYTASK:
                DPRINTF(Comm, "DELAYTASK");
                break;
              case SEMPEND:
                DPRINTF(Comm, "SEMPEND");
                break;
              case QUEUEPEND:
                DPRINTF(Comm, "QUEUEPEND");
                break;
              case MUTEXPEND:
                DPRINTF(Comm, "MUTEXPEND");
                break;
              case SEMPOST:
                DPRINTF(Comm, "SEMPOST");        
                break;
              case QUEUEPOST:
                DPRINTF(Comm, "QUEUEPOST");
                break;
              case MUTEXPOST:
                DPRINTF(Comm, "MUTEXPOST");
                break;
              case OS_IDLE:
                #if(OS_IDLE_SHOW == 1)
                  DPRINTF(Comm, "IDLE");
                #endif
                break; 
              default:
                break;
            }
        }

        DPRINTF(Comm, " - ");
    }   
    j += MAX_TRACE_LINE;
    DPUTCHAR(Comm, LF); 
  } while(j < MAX_DEPTH_TRACE);

  DPUTCHAR(Comm, CR);

}
#endif

