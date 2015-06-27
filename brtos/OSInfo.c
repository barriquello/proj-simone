/*
 * debug.c
 *
 *  Created on: 12/12/2014
 *      Author: Gustavo
 */
#include "BRTOS.h"
#include "OSInfo.h"

int mem_cpy(char *dst, char *src)
{
	int i = 0;
	while(*src)
	{
		*dst++ = *src++;
		i++;
	}
	return i;
}

char *PrintDecimal(INT16S val, CHAR8 *buff)
{
   INT16U backup;
   INT32U i = 0;
   CHAR8 s = ' ';

   // Fill buffer with spaces
   for (i = 0; i < 6; i++)
   {
      *(buff + i) = ' ';
   }

   // Null termination for data
   *(buff + i) = 0;

   if (val < 0)
   {
      val = -val;
      s = '-';
   }

   // Convert binary value to decimal ASCII
   for (i = 5; i > 0;)
   {
      backup = val;
      val /= 10;
      *(buff + i) = (backup - (val*10)) + '0';
      i--;

      if (val == 0)  break;
   }

   // Completes the string for sign information
   *(buff + i) = s;  // Sign character

   if (*(buff + i) == '-')
   {
	   return (buff+i);
   }else
   {
	   return (buff+i+1);
   }
}


// Imprimir ID, nome, prioridade, stack
// memoria total heap de tarefas
// memoria total heap de filas
void OSTaskList(char *string)
{
    INT16U VirtualStack = 0;
    INT8U  j = 0;
    INT8U  i = 0;
    INT8U  prio = 0;
    CHAR8  str[9];
    INT32U *sp_end = 0;
    INT32U *sp_address = 0;

    string += mem_cpy(string,"\n\r******************************************\n\r");
    string += mem_cpy(string,"ID   NAME           PRIORITY   STACK SIZE\n\r");
    string += mem_cpy(string,"******************************************\n\r");

    int z,count;
    for (j=1;j<=NumberOfInstalledTasks;j++)
    {
      *string++ = '[';
      if (j<10)
      {
    	  *string++ = j+'0';
          string += mem_cpy(string, "]  ");
      }else
      {
    	  (void)PrintDecimal(j, str);
    	  string += mem_cpy(string, (str+4));
          string += mem_cpy(string, "] ");
      }
      z = mem_cpy(string,(char*)ContextTask[j].TaskName);
      string +=z;

      // Task name align
      for(count=0;count<(16-z);count++)
      {
    	  *string++ = ' ';
      }

      // Print the task priority
      UserEnterCritical();
      prio = ContextTask[j].Priority;
      UserExitCritical();

      (void)PrintDecimal(prio, str);
      string += mem_cpy(string, (str+2));
      string += mem_cpy(string,"       ");

      // Print the task stack size
      UserEnterCritical();
      sp_address = (INT32U*)ContextTask[j].StackPoint;
      if (j == 1)
      {
    	  sp_end = (INT32U*)&STACK[0];
      }else
      {
    	  sp_end = (INT32U*)ContextTask[j-1].StackInit;
      }
      UserExitCritical();

      // Find for at least 16 available sp data into task stack
      i = 0;
      while(i<16)
      {
        if (sp_address <= sp_end)
        {
          break;
        }
        if (*sp_address == 0)
        {
          i++;
        }else
        {
          i = 0;
        }
        sp_address--;
      }


      UserEnterCritical();
      VirtualStack = ContextTask[j].StackInit - ((INT32U)sp_address + (i*4));
      UserExitCritical();

      (void)PrintDecimal(VirtualStack, str);
      string += mem_cpy(string, str);

      string += mem_cpy(string, "\n\r");
    }

    *string++ = '[';
    (void)PrintDecimal((NUMBER_OF_TASKS+1), str);
    string += mem_cpy(string, (str+4));
    string += mem_cpy(string, "] ");

    string += mem_cpy(string, "Idle Task");
    for(count=0;count<7;count++)
    {
  	  *string++ = ' ';
    }

    // Print the task priority
    UserEnterCritical();
    prio = ContextTask[NUMBER_OF_TASKS+1].Priority;
    UserExitCritical();

    (void)PrintDecimal(prio, str);
    string += mem_cpy(string, (str+2));
    string += mem_cpy(string,"       ");

    UserEnterCritical();
    sp_address = (INT32U*)ContextTask[NUMBER_OF_TASKS+1].StackPoint;
    sp_end = (INT32U*)ContextTask[j-1].StackInit;
    UserExitCritical();

    i = 0;
    while(i<16)
    {
      if (sp_address <= sp_end)
      {
        break;
      }
      if (*sp_address == 0)
      {
        i++;
      }else
      {
        i = 0;
      }
      sp_address--;
    }


    UserEnterCritical();
    VirtualStack = ContextTask[NUMBER_OF_TASKS+1].StackInit - ((INT32U)sp_address + (INT32U)i*4);
    UserExitCritical();

    (void)PrintDecimal(VirtualStack, str);
    string += mem_cpy(string, str);

    string += mem_cpy(string, "\n\r");

    // End of string
    *string = '\0';
}


void OSAvailableMemory(char *string)
{
    INT16U address = 0;
    CHAR8  str[8];

    string += mem_cpy(string, "\n\r***** BRTOS Memory Info *****\n\r");
    string += mem_cpy(string, "TASK MEMORY HEAP:  ");

    UserEnterCritical();
    address = iStackAddress * sizeof(OS_CPU_TYPE);
    UserExitCritical();

    (void)PrintDecimal(address, str);
    string += mem_cpy(string, &str[2]);
    string += mem_cpy(string, " of ");

    string += mem_cpy(string, PrintDecimal(HEAP_SIZE, str));

    string += mem_cpy(string, "\n\rQUEUE MEMORY HEAP: ");

    UserEnterCritical();
    address = iQueueAddress * sizeof(OS_CPU_TYPE);
    UserExitCritical();

    (void)PrintDecimal(address, str);
    string += mem_cpy(string, &str[2]);

    string += mem_cpy(string, " of ");

    string += mem_cpy(string, PrintDecimal(QUEUE_HEAP_SIZE, str));
    string += mem_cpy(string, "\n\r");

    // End of string
    *string = '\0';
}


void OSUptimeInfo(char *string)
{
   OSTime Uptime;
   OSDate UpDate;
   CHAR8  str[6];

   UserEnterCritical();
   Uptime = OSUptime();
   UpDate = OSUpDate();
   UserExitCritical();

   string += mem_cpy(string, "\n\rBRTOS UPTIME: ");

   // S� funciona at� 255 dias
   if(UpDate.RTC_Day > 0)
   {
      string += mem_cpy(string,PrintDecimal(UpDate.RTC_Day, str));
      string += mem_cpy(string, "d ");
   }

   string += mem_cpy(string,PrintDecimal(Uptime.RTC_Hour, str));
   string += mem_cpy(string, "h ");

   string += mem_cpy(string,PrintDecimal(Uptime.RTC_Minute, str));
   string += mem_cpy(string, "m ");

   string += mem_cpy(string,PrintDecimal(Uptime.RTC_Second, str));
   string += mem_cpy(string, "s\n\r");

   // End of string
   *string = '\0';
}


#if (COMPUTES_CPU_LOAD == 1)
void OSCPULoad(char *string)
{
    INT32U percent = 0;
    INT8U caracter = 0;
    INT8U cent,dez;

    UserEnterCritical();
    percent = LastOSDuty;
    UserExitCritical();

    string += mem_cpy(string, "\n\rCPU LOAD: ");

    if (percent >= 1000)
    {
    	string += mem_cpy(string, "100 %");
    }
    else
    {
        cent = (percent/100);
        caracter = cent + 48;
        if(caracter != 48)
          *string++ = caracter;
        dez = ((percent - cent*100)/10);
        caracter = dez + 48;
        *string++ = caracter;
        *string++ = '.';
        caracter = (percent%10) + 48;
        *string++ = caracter;
        *string++ = '%';
    }
    string += mem_cpy(string, "\n\r");

    // End of string
    *string = '\0';
}
#endif

