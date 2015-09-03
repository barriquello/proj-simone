/*
 * debug.c
 *
 *  Created on: 12/12/2014
 *      Author: Gustavo
 */
#include "BRTOS.h"
#include "OSInfo.h"

static int str_cpy(char *dst, char *src)
{
	int i = 0;
	while(*src)
	{
		*dst++ = *src++;
		i++;
	}
	return i;
}

static char *PrintDecimal(INT16S val, CHAR8 *buff)
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
      backup = (INT16U)val;
      val /= 10;
      *(buff + i) = (INT8U) ((backup - (val*10)) + '0');
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

    string += str_cpy(string,"\n\r******************************************\n\r");
    string += str_cpy(string,"ID   NAME           PRIORITY   STACK SIZE\n\r");
    string += str_cpy(string,"******************************************\n\r");

    int z,count;
    for (j=1;j<=NumberOfInstalledTasks;j++)
    {
      *string++ = '[';
      if (j<10)
      {
    	  *string++ = (INT8U)(j+'0');
          string += str_cpy(string, "]  ");
      }else
      {
    	  (void)PrintDecimal(j, str);
    	  string += str_cpy(string, (str+4));
          string += str_cpy(string, "] ");
      }
      z = str_cpy(string,(char*)ContextTask[j].TaskName);
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
      string += str_cpy(string, (str+2));
      string += str_cpy(string,"       ");

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
      VirtualStack = (INT16U)(ContextTask[j].StackInit - ((INT32U)sp_address + (i*4)));
      UserExitCritical();

      (void)PrintDecimal((INT16S)VirtualStack, str);
      string += str_cpy(string, str);

      string += str_cpy(string, "\n\r");
    }

    *string++ = '[';
    (void)PrintDecimal((NUMBER_OF_TASKS+1), str);
    string += str_cpy(string, (str+4));
    string += str_cpy(string, "] ");

    string += str_cpy(string, "Idle Task");
    for(count=0;count<7;count++)
    {
  	  *string++ = ' ';
    }

    // Print the task priority
    UserEnterCritical();
    prio = ContextTask[NUMBER_OF_TASKS+1].Priority;
    UserExitCritical();

    (void)PrintDecimal(prio, str);
    string += str_cpy(string, (str+2));
    string += str_cpy(string,"       ");

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
    VirtualStack = (INT16U) (ContextTask[NUMBER_OF_TASKS+1].StackInit - ((INT32U)sp_address + (INT32U)i*4));
    UserExitCritical();

    (void)PrintDecimal((INT16S)VirtualStack, str);
    string += str_cpy(string, str);

    string += str_cpy(string, "\n\r");

    // End of string
    *string = '\0';
}


void OSAvailableMemory(char *string)
{
    INT16U address = 0;
    CHAR8  str[8];

    string += str_cpy(string, "\n\r***** BRTOS Memory Info *****\n\r");
    string += str_cpy(string, "TASK MEMORY HEAP:  ");

    UserEnterCritical();
    address = iStackAddress * sizeof(OS_CPU_TYPE);
    UserExitCritical();

    (void)PrintDecimal((INT16S)address, str);
    string += str_cpy(string, &str[2]);
    string += str_cpy(string, " of ");

    string += str_cpy(string, PrintDecimal(HEAP_SIZE, str));

    string += str_cpy(string, "\n\rQUEUE MEMORY HEAP: ");

    UserEnterCritical();
    address = iQueueAddress * sizeof(OS_CPU_TYPE);
    UserExitCritical();

    (void)PrintDecimal((INT16S)address, str);
    string += str_cpy(string, &str[2]);

    string += str_cpy(string, " of ");

    string += str_cpy(string, PrintDecimal(QUEUE_HEAP_SIZE, str));
    string += str_cpy(string, "\n\r");

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

   string += str_cpy(string, "\n\rBRTOS UPTIME: ");

   // Só funciona até 255 dias
   if(UpDate.RTC_Day > 0)
   {
      string += str_cpy(string,PrintDecimal(UpDate.RTC_Day, str));
      string += str_cpy(string, "d ");
   }

   string += str_cpy(string,PrintDecimal(Uptime.RTC_Hour, str));
   string += str_cpy(string, "h ");

   string += str_cpy(string,PrintDecimal(Uptime.RTC_Minute, str));
   string += str_cpy(string, "m ");

   string += str_cpy(string,PrintDecimal(Uptime.RTC_Second, str));
   string += str_cpy(string, "s\n\r");

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

    string += str_cpy(string, "\n\rCPU LOAD: ");

    if (percent >= 1000)
    {
    	string += str_cpy(string, "100 %");
    }
    else
    {
        cent = (INT8U) (percent/100);
        caracter = cent + 48;
        if(caracter != 48)
          *string++ = caracter;
        dez = (INT8U) ((percent - cent*100)/10);
        caracter = dez + 48;
        *string++ = caracter;
        *string++ = '.';
        caracter = (INT8U)((percent%10) + 48);
        *string++ = caracter;
        *string++ = '%';
    }
    string += str_cpy(string, "\n\r");

    // End of string
    *string = '\0';
}
#endif

