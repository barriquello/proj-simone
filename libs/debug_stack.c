#include "BRTOS.h"
#include "debug_stack.h"
#include "utils.h"
#include "terminal.h"
#include "uart.h"
#include "terminal_io.h"

#include "AppConfig.h"
#include "printf_lib.h"

#if PLATAFORMA==COLDUINO
#pragma warn_implicitconv off
#define DEBUG_STACK_PRINT 1
#endif

#ifdef _WIN32
#define DEBUG_STACK_PRINT 1
#endif


#if DEBUG_STACK_PRINT
#define DPRINTF(a,...) printSer(a,__VA_ARGS__);
#define DPUTCHAR(a,b)  putcharSer(a,b);
#else
#ifndef UNUSED
#define UNUSED(a)		(void)((a))
#endif
#define DPRINTF(a,...)	UNUSED((a));
#define DPUTCHAR(a,b)	UNUSED((a));UNUSED((b));
#endif


void Transmite_Uptime(INT8U Comm)
{
   OSTime Uptime;
   OSDate UpDate;
   CHAR8  string[32];
   
   UserEnterCritical();
   	   Uptime = OSUptime();
   	   UpDate = OSUpDate();
   UserExitCritical();
   
   SNPRINTF(string,SIZEARRAY(string),"UPTIME: %d d %d h %d m %d s\n\r",
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
    
    SNPRINTF(string,SIZEARRAY(string),"MEMORY: %d of %d\n\r",SPAddress,HEAP_SIZE);
    DPRINTF(Comm, string);
}


void Transmite_Task_Stacks(INT8U Comm)
{
    INT16U VirtualStack = 0;
    INT8U  j = 0;
    INT8U  k = 0;
    CHAR8  string[5];
    INT32U *x = 0;
    INT32U *i = 0; 
    INT32U *p = 0; 
   
    DPRINTF(Comm, "\n\rTASK STACK:\n\r");    
          
    for (j=1;j<=NumberOfInstalledTasks;j++)
    {  
      DPUTCHAR(Comm, '[');
      DPUTCHAR(Comm, j+'0');
      DPRINTF(Comm, "] ");
      DPRINTF(Comm, (char*)ContextTask[j].TaskName);
      DPRINTF(Comm, ": ");
      
      UserEnterCritical();
      i = (INT32U*)ContextTask[j].StackPoint;
      if (j == 1)
      {
    	  x = (INT32U*)&STACK[0];
      }else
      {
    	  x = (INT32U*)ContextTask[j-1].StackInit;
      }
      UserExitCritical();  
      
      p = x;
      
      while(*p == 0)
      {
    	p++;  
    	if(p>=i) break;
      }
      
      
#include "stdlib.h"
      
      UserEnterCritical();
      //VirtualStack = ContextTask[j].StackInit - (INT32U)i;
      VirtualStack = ContextTask[j].StackInit - (INT32U) p;
      UserExitCritical();
      
      Print4Digits(VirtualStack, NO_ALIGN, string);
      DPRINTF(Comm, string);
      
      DPRINTF(Comm,  " of ");

      VirtualStack = (ContextTask[j].StackInit - (INT32U) x);
      
      Print4Digits(VirtualStack, NO_ALIGN, string);
      DPRINTF(Comm, string);
      
      DPRINTF(Comm, "\n\r");
    }
    
    DPUTCHAR(Comm, '[');
    DPUTCHAR(Comm, j+'0');
    DPRINTF(Comm, "] ");
    DPRINTF(Comm, "Idle Task: ");
    
    UserEnterCritical();
    i = (INT32U*)ContextTask[NUMBER_OF_TASKS+1].StackPoint;
    x = (INT32U*)ContextTask[j-1].StackInit;     
    UserExitCritical();  
    
    p = x;
         
	 while(*p == 0)
	 {
		p++;  
		if(p>=i) break;
	 }

    UserEnterCritical();
    //VirtualStack = ContextTask[NUMBER_OF_TASKS+1].StackInit - ((INT32U)i + (INT32U)4);
    VirtualStack = ContextTask[NUMBER_OF_TASKS+1].StackInit - (INT32U) p;
    UserExitCritical();
      
    Print4Digits(VirtualStack, NO_ALIGN, string);
    DPRINTF(Comm, string);
    
    DPRINTF(Comm,  " of ");

    VirtualStack = (ContextTask[NUMBER_OF_TASKS+1].StackInit - (INT32U) x);
    
    Print4Digits(VirtualStack, NO_ALIGN, string);
    DPRINTF(Comm, string);   
    
    DPRINTF(Comm, "\n\r");
}




#if (COMPUTES_CPU_LOAD == 1)
void Transmite_CPU_Load(INT8U Comm)
{
    INT32U percent = 0;
    INT8U caracter = 0;
    INT8U cent,dez;    
   
    UserEnterCritical();
    	percent = LastOSDuty;
    UserExitCritical();   
   
    DPRINTF(Comm, "CPU LOAD: ");
    
    if (percent >= 1000)
    {
      DPRINTF(Comm, "100 %");    
    }
    else
    {
        cent = (percent/100);
        caracter = cent + 48;
        if(caracter != 48)
          DPUTCHAR(Comm, caracter);
        dez = ((percent - cent*100)/10);
        caracter = dez + 48;
        DPUTCHAR(Comm, caracter);
        DPUTCHAR(Comm, '.');
        caracter = (percent%10) + 48;
        DPUTCHAR(Comm, caracter);
        DPUTCHAR(Comm, '%');
    }
    DPRINTF(Comm, "\n\r");
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
      DPRINTF(Comm, "Power-on Reset (Cold reset)");
      break;
      
    default:
      DPRINTF(Comm, "unknown reason - Code: ");
      Print3Digits(reason, NO_ALIGN, string);
      DPRINTF(Comm, string);
      break;
  }
#endif  
}


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

