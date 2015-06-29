#include "BRTOS.h"
#include "debug_stack.h"
#include "utils.h"
#include "usb_terminal.h"
#include "uart.h"

#pragma warn_implicitconv off




void Transmite_Uptime(INT8U Comm)
{
   OSTime Uptime;
   OSDate UpDate;
   CHAR8  string[6];
   
   UserEnterCritical();
   Uptime = OSUptime();
   UpDate = OSUpDate();
   UserExitCritical();
   
   printSer(Comm, "UPTIME: ");

   // Só funciona até 255 dias
   if(UpDate.RTC_Day > 0)
   {    
      Print3Digits(UpDate.RTC_Day, NO_ALIGN, string);
      printSer(Comm, string);
      printSer(Comm, "d ");
   }
   
   Print2Digits(Uptime.RTC_Hour, NO_ALIGN, string);
   printSer(Comm, string);
   printSer(Comm, "h ");
   
   Print2Digits(Uptime.RTC_Minute, NO_ALIGN, string);
   printSer(Comm, string);
   printSer(Comm, "m ");

   Print2Digits(Uptime.RTC_Second, NO_ALIGN, string);
   printSer(Comm, string);
   printSer(Comm, "s\n\r");
}




void Transmite_RAM_Ocupada(INT8U Comm)
{
    INT16U SPAddress = 0;
    CHAR8  string[7];
    INT8U  i = 0;
   
    printSer(Comm, "MEMORY: ");
    
    UserEnterCritical();
    SPAddress = iStackAddress * sizeof(OS_CPU_TYPE);
    UserExitCritical();
    
    PrintDecimal(SPAddress, string);
    i = 0;
    while(string[i] == ' ')
    {
    	i++;
    	if (i > 6)
		{
    		i = 6;
    		break;	
		}
    };
    printSer(Comm, &string[i]);

    printSer(Comm, " of ");
       
    PrintDecimal(HEAP_SIZE, string);
    i = 0;
    while(string[i] == ' ')
    {
    	i++;
    	if (i > 6)
		{
    		i = 6;
    		break;	
		}
    };     
    printSer(Comm, &string[i]);
    
    printSer(Comm, "\n\r");
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
   
    printSer(Comm, "\n\rTASK STACK:\n\r");    
          
    for (j=1;j<=NumberOfInstalledTasks;j++)
    {  
      putcharSer(Comm, '[');
      putcharSer(Comm, j+'0');
      printSer(Comm, "] ");
      printSer(Comm, (char*)ContextTask[j].TaskName);
      printSer(Comm, ": ");
      
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
      
#if 0      
      k = 0;
      while(k<8)
      {
        if (i <= x)
        {
          break;
        }
        if (*i == 0)
        {
          k++;
        }else 
        {
          k = 0;
        }
        i--;
      } 
#endif      
      
#include "stdlib.h"
      
      UserEnterCritical();
      //VirtualStack = ContextTask[j].StackInit - (INT32U)i;
      VirtualStack = ContextTask[j].StackInit - (INT32U) p;
      UserExitCritical();
      
      Print4Digits(VirtualStack, NO_ALIGN, string);
      printSer(Comm, string);
      
      printSer(Comm,  " of ");

      VirtualStack = (ContextTask[j].StackInit - (INT32U) x);
      
      Print4Digits(VirtualStack, NO_ALIGN, string);
      printSer(Comm, string);
      
      printSer(Comm, "\n\r");
    }
    
    putcharSer(Comm, '[');
    putcharSer(Comm, j+'0');
    printSer(Comm, "] ");

    printSer(Comm, "Idle Task: ");
    
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

#if 0
    k = 0;
    while(k<32)
    {
      if (i <= x)
      {
        break;
      }
      if (*i == 0)
      {
        k++;
      }else 
      {
        k = 0;
      }
      i--;
    } 
#endif    
    
    
    UserEnterCritical();
    //VirtualStack = ContextTask[NUMBER_OF_TASKS+1].StackInit - ((INT32U)i + (INT32U)4);
    VirtualStack = ContextTask[NUMBER_OF_TASKS+1].StackInit - (INT32U) p;
    UserExitCritical();
      
    Print4Digits(VirtualStack, NO_ALIGN, string);
    printSer(Comm, string);
    
    printSer(Comm,  " of ");

    VirtualStack = (ContextTask[NUMBER_OF_TASKS+1].StackInit - (INT32U) x);
    
    Print4Digits(VirtualStack, NO_ALIGN, string);
    printSer(Comm, string);
    
    
    printSer(Comm, "\n\r");
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
   
    printSer(Comm, "CPU LOAD: ");
    
    if (percent >= 1000)
    {
      printSer(Comm, "100 %");    
    }
    else
    {
        cent = (percent/100);
        caracter = cent + 48;
        if(caracter != 48)
          putcharSer(Comm, caracter);
        dez = ((percent - cent*100)/10);
        caracter = dez + 48;
        putcharSer(Comm, caracter);
        putcharSer(Comm, '.');
        caracter = (percent%10) + 48;
        putcharSer(Comm, caracter);
        putcharSer(Comm, '%');
    }
    printSer(Comm, "\n\r");
}
#endif


void Reason_of_Reset(INT8U Comm)
{  
  INT8U reason = 0;
  CHAR8  string[5];
  
  reason = SRS;
  switch(reason)
  {
    case 0b00000000:
      printSer(Comm, "Reset caused by BDM");
      break;
      
    case 0b00000010:
      printSer(Comm, "Reset caused by low voltage");
      break;      
      
    case 0b00001000:
      printSer(Comm, "Reset caused by illegal address");
      break;
      
    case 0b00010000:
      printSer(Comm, "Reset caused by illegal opcode");
      break;
      
    case 0b00100000:
      printSer(Comm, "Reset caused by watchdog");
      break;
      
    case 0b01000000:
      printSer(Comm, "Reset caused by reset pin");
      break;
      
    case 0b10000010:
    case 0b10000000:
      printSer(Comm, "Power-on Reset (Cold reset)");
      break;
      
    default:
      printSer(Comm, "Unknown reason - Code: ");
      Print3Digits(reason, NO_ALIGN, string);
      printSer(Comm, string);
      break;
  }
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
                printSer(Comm, "ISR ONLY"); 
                break;         
              case ISR_TICK:
                #if(OS_TICK_SHOW == 1)  
                  printSer(Comm, "ISR TICK"); 
                #endif
                break;
              case SEMPOST:
                printSer(Comm, "ISR SEMPOST");        
                break;
              case QUEUEPOST:
                printSer(Comm, "ISR QUEUEPOST");
                break;
              case MUTEXPOST:
                printSer(Comm, "ISR MUTEXPOST");
                break;
              case OS_IDLE:
                #if(OS_IDLE_SHOW == 1)
                  printSer(Comm, "ISR IDLE");
                #endif
                break; 
              default:
                printSer(Comm, "________");
                break;
            }
        }else
        {
           #if(OS_IDLE_SHOW == 1)  
            printSer(Comm, "TASK ");
            car = OSTrace_snapshot[i]>>5;
            car = (car / 10) + 48;
            putcharSer(Comm, car);
            car = OSTrace_snapshot[i]>>5;
            car = (car%10) + 48;
            putcharSer(Comm, car);
            putcharSer(Comm, ' ');
          #else
           if((OSTrace_snapshot[i]>>5) != (NUMBER_OF_TASKS+1))
           {
              TaskName = ContextTask[OSTrace_snapshot[i]>>5].TaskName;
              printSer(Comm, TaskName);
              putcharSer(Comm, ' ');
           }
          #endif  
            
            switch(OSTrace_snapshot[i] & 0x07){
              case DELAYTASK:
                printSer(Comm, "DELAYTASK");
                break;
              case SEMPEND:
                printSer(Comm, "SEMPEND");
                break;
              case QUEUEPEND:
                printSer(Comm, "QUEUEPEND");
                break;
              case MUTEXPEND:
                printSer(Comm, "MUTEXPEND");
                break;
              case SEMPOST:
                printSer(Comm, "SEMPOST");        
                break;
              case QUEUEPOST:
                printSer(Comm, "QUEUEPOST");
                break;
              case MUTEXPOST:
                printSer(Comm, "MUTEXPOST");
                break;
              case OS_IDLE:
                #if(OS_IDLE_SHOW == 1)
                  printSer(Comm, "IDLE");
                #endif
                break; 
              default:
                break;
            }
        }

        printSer(Comm, " - ");
    }   
    j += MAX_TRACE_LINE;
    putcharSer(Comm, LF); 
  } while(j < MAX_DEPTH_TRACE);

  putcharSer(Comm, CR);

}

#endif

