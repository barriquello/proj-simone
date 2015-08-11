/****************************************************************************************
* 
*   FILE        :    usb_terminal_commands.c
*   DATE CREATED:    
*   DESCRIPTION	:    
*
*   Author		:     
*  	Location	:    
*   Purpose		:
*   Copyright	:    
*                                                  
* UPDATED HISTORY:
*
* REV   YYYY.MM.DD  AUTHOR          	DESCRIPTION OF CHANGE
* ---   ----------  ------          	--------------------- 
* 1.0   2011.05.12  Gustavo Denardin	Initial version
*
****************************************************************************************/

/*
 * usb_terminal_commands.c
 *
 *  Created on: 12/05/2011
 *      Author: gustavo
 */
#include "AppConfig.h"
#include "usb_terminal.h"
#include "usb_terminal_commands.h"
#include "virtual_com.h"
#include "BRTOS.h"
#include "debug_stack.h"
#include "tasks.h"
#include "utils.h"
#include "da.h"
//#include "sound_driver.h"
#include "UART.h"
#include "string.h"

INT8U entradas[CONSOLE_BUFFER_SIZE]; //vetor para a entrada de dados

// BRTOS version Command
void usb_cmd_ver(char *param)
{
  (void)*param;
  printf_usb("\n\r");
  printf_usb((CHAR8*)version);
  printf_usb("\n\r");
}

const command_t usb_ver_cmd = {
  "ver", usb_cmd_ver, "BRTOS Version"
};



// TOP Command (similar to the linux command)
void usb_cmd_top(char *param)
{
  (void)*param;
  printf_usb("\n\r");
  Transmite_CPU_Load(USE_USB);
  Transmite_Uptime(USE_USB);
  Transmite_RAM_Ocupada(USE_USB);
  Transmite_Task_Stacks(USE_USB);
}

const command_t usb_top_cmd = {
  "top", usb_cmd_top, "BRTOS TOP"
};


// Reason of Reset Command
void usb_cmd_rst(char *param)
{
  (void)*param;
  printf_usb("\n\r");
  Reason_of_Reset(USE_USB);
}

const command_t usb_rst_cmd = {
  "rst", usb_cmd_rst, "CPU Reason of the Reset"
};

// Core temperature Command
extern INT16S CoreTemp;
void usb_cmd_temp(char *param)
{
  INT16S temp;
  CHAR8  string[8];
  (void)*param;
  
  UserEnterCritical();
  temp = CoreTemp;
  UserExitCritical();
  
  PrintDecimal(temp, string);
  printf_usb("\n\r");
  printf_usb((CHAR8*)&string[3]);
  printf_usb(" degrees");
}

const command_t usb_temp_cmd = {
  "temp", usb_cmd_temp, "Show core temperature"
};

void cmd_setget_time(char *param){
	
	OS_RTC datetime; /* dd/mm/yyyy hh:mm:ss */
	
	if(*param != NULL) // set
	{				
		datetime.Day = (INT8U)((*param) - '0')*10; // day
		*param++ = NULL;
		
		if(*param != NULL)
		{    			
		    datetime.Day += (INT8U)((*param++) - '0'); // day		    		    		   
		    if(datetime.Day > 31){	goto time_format_error; }
		    		    
			if(*(++param) != NULL)
			{    			
			    datetime.Month = (INT8U)((*param++) - '0')*10; // month
				if(*param != NULL)
				{    			
				    datetime.Month += (INT8U)((*param++) - '0'); // month				    
				    if(datetime.Month > 12) {	goto time_format_error; }
				    if(*(++param) != NULL)
					{    			
					    datetime.Year = (INT16U)((*param++) - '0')*1000; // year
					    if(*param != NULL)
						{    			
							datetime.Year += (INT16U)((*param++) - '0')*100; // year
						    if(*param != NULL)
							{    			
								datetime.Year += (INT16U)((*param++) - '0')*10; // year
							    if(*param != NULL)
								{    			
									datetime.Year += (INT16U)((*param++) - '0'); // year
									if(datetime.Year > 2100){goto time_format_error; }
									
#if RTC_PRESENTE
									RTC_DS1307_Set_Date((INT8U)((datetime.Year%1000)%100),datetime.Month,datetime.Day);
#endif									
									
									if(*(++param) != NULL) // set
									{			
										datetime.Hour = (INT8U)((*param) - '0')*10; // hour
										*param++ = NULL;
										
										if(*param != NULL)
										{    			
											datetime.Hour += (INT8U)((*param++) - '0'); // hour
											if(datetime.Hour > 23){goto time_format_error; }
											
											if(*(++param) != NULL)
											{    			
												datetime.Min = (INT8U)((*param++) - '0')*10; // min
												if(*param != NULL)
												{    			
													datetime.Min += (INT8U)((*param++) - '0'); // min
													if(datetime.Min > 59){goto time_format_error; }
													
													if(*(++param) != NULL)
													{    			
														datetime.Sec = (INT8U)((*param++) - '0')*10; // sec
														if(*param != NULL)
														{    			
															datetime.Sec += (INT8U)((*param++) - '0'); // sec
															if(datetime.Sec > 59){goto time_format_error; }
															
															#if RTC_PRESENTE															
															RTC_DS1307_Set_Time(datetime.Hour,datetime.Min,datetime.Sec);
															#endif
															
															SetCalendar(&datetime);
														}							
													}				    
												}			    
											} 
										}
									}
								}
							}
						}
					}				    
				}			    
			} 
		}
	}
	
	
	
time_format_error:		
	while(*param != NULL){
		*param = NULL;	
		param++;
	}    	    
	
#if 1	
	GetCalendar(&datetime);	
	
	OS_RTC rtc;
	
#if RTC_PRESENTE	
	RTC_DS1307 rtc_ds1307;
	
	RTC_DS1307_Update(&rtc_ds1307);
	rtc.Year = rtc_ds1307.Year;
	rtc.Month = rtc_ds1307.Month;
	rtc.Day = rtc_ds1307.Day;
	rtc.Hour = rtc_ds1307.Hour;
	rtc.Min = rtc_ds1307.Min;
	rtc.Sec = rtc_ds1307.Sec;
#endif	
		
	INT8S cmp = CompareDateTime(&rtc,&datetime);
	if( cmp == 0 || cmp == -1)
	{		
		if (cmp == 0)
			printf_usb("\n\r =");
		else
			printf_usb("\n\r <");
		
		goto print_date;
		
	}
	else
	{
		printf_usb("\n\r > ");
		
		datetime = rtc;
		goto print_date;	
	}
	
print_date:
	char string[5];
			
	/* print current Date & Time */
	printf_usb("\n\r");
	
	/* day */
	Print2Digits(datetime.Day, ZEROS_ALIGN, string);
	printf_usb((CHAR8*)string);
	printf_usb("/");
	
	/* month */
	Print2Digits(datetime.Month, ZEROS_ALIGN, string);
	printf_usb((CHAR8*)string);
	printf_usb("/");
	
	/* year */
	Print4Digits(datetime.Year, ZEROS_ALIGN, string);
	printf_usb((CHAR8*)string);
	printf_usb(" ");
	
	/* hour */
	Print2Digits(datetime.Hour, ZEROS_ALIGN, string);
	printf_usb((CHAR8*)string);
	printf_usb(":");
	
	/* minutes */
	Print2Digits(datetime.Min, ZEROS_ALIGN, string);
	printf_usb((CHAR8*)string);
	printf_usb(":");
	
	/* seconds */
	Print2Digits(datetime.Sec, ZEROS_ALIGN, string);
	printf_usb((CHAR8*)string);	
	printf_usb("\n\r");

#else	
	print_date:
		INT8U string[15]; // yyyymmddhhmmss	
		OSDateTime timestamp;
		
		GetDateTime(&timestamp);
		PrintDateTime(&timestamp, string);
				
		/* print current Date & Time */
		printf_usb("\n\r");
		printf_usb((CHAR8*)string);
		printf_usb("\n\r");
#endif		
	
}

const command_t setget_time_cmd = {
  "time", cmd_setget_time, "Set/Get OS Date and Time"
};


// SD Card Read Command
void cmd_cat(char *param)
{  
  INT8U i       = 0;
  INT8U retorno = 0;
  CHAR8 name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos  
  CHAR8 name2[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos 
  
  for(i=0;i<(CONSOLE_BUFFER_SIZE/2);i++)
  {
    // Limpa o buffer de entradas
    name1[i] = 0;
    name2[i] = 0;
  }      
  
  i = 0;  
  entradas[0] = 0x20;
  i++;
  
  while(*param)
  {
    if (i < CONSOLE_BUFFER_SIZE)
    {  
      entradas[i] = *param;
      i++;
      param++;
    }else
    {
      break;
    }
  }
  
  // verifica o nome digitado
  retorno = file_name_verify(name1,name2,(INT8U*)&entradas[0],1);
  
  if(retorno==API_COMMAND_OK)
  {
    (void)ReadFile(name1,VERBOSE_ON);
  }
  else
  {
	  printSer(USE_USB, (CHAR8*)SD_API_FILE_INVALID);
  }  
  
  for(i=0;i<CONSOLE_BUFFER_SIZE;i++)
  {
    // Limpa o buffer de entradas
    entradas[i] = 0;
  }
}

const command_t cat_cmd = {
  "cat", cmd_cat, "SD Card - Read file"
};


// SD Card List Files Command
void cmd_ls(char *param)
{  
  INT8U i       = 0;
  INT8U retorno = 0;  
  INT8U name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos  
  
  
  (void)*param;
  for(i=0;i<(CONSOLE_BUFFER_SIZE/2);i++)
  {
    // Limpa o buffer de entradas
    name1[i] = 0;
  }  

  retorno = API_COMMAND_OK;
  if(retorno==API_COMMAND_OK)
  {
    (void)ListFiles(name1);
  }
  else
  {
	  printSer(USE_USB, (CHAR8*)SD_API_FILE_INVALID);
  }
  
  for(i=0;i<CONSOLE_BUFFER_SIZE;i++)
  {
    // Limpa o buffer de entradas
    entradas[i] = 0;
  }  
}

const command_t ls_cmd = {
  "ls", cmd_ls, "SD Card - List files"
};


// SD Card Change Dir Command
void cmd_cd(char *param)
{  
  INT8U i       = 0;
  INT8U retorno = 0;
  CHAR8 name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos  
  CHAR8 name2[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos 
  
  for(i=0;i<(CONSOLE_BUFFER_SIZE/2);i++)
  {
    // Limpa o buffer de entradas
    name1[i] = 0;
    name2[i] = 0;
  }      
  
  i = 0;  
  entradas[0] = 0x20;
  i++;
  
  while(*param)
  {
    if (i < CONSOLE_BUFFER_SIZE)
    {  
      entradas[i] = *param;
      i++;
      param++;
    }else
    {
      break;
    }
  }
  
  // verifica o nome digitado
  retorno = file_name_verify(name1,name2,(INT8U*)&entradas[0],1);
  
  if(retorno==API_COMMAND_OK)
  {
    (void)ChangeDir(name1,VERBOSE_ON);
  }
  else
  {
	  printSer(USE_USB, (CHAR8*)SD_API_FILE_INVALID);
  }  
  
  for(i=0;i<CONSOLE_BUFFER_SIZE;i++)
  {
    // Limpa o buffer de entradas
    entradas[i] = 0;
  }
}

const command_t cd_cmd = {
  "cd", cmd_cd, "SD Card - Change Dir"
};

// Mount SD Card Command
#if (SD_WAVE == 1)
extern char musics[WAV_LIST_SIZE][WAV_NAME_SIZE];
#endif

void cmd_mount(char *param)
{    
  INT8U status = 0;
  INT8U i = 0;
  
  #if (SD_WAVE != 1)
  (void)*param;
  #endif
  
  // Initialize SD card
  status = SDCard_Init(VERBOSE_ON);
  
  #if (SD_WAVE == 1)
  if ((status == SD_OK) && (*param == 'r'))
  {
	  // Clean WAV list
	  for (i=0;i<WAV_LIST_SIZE;i++)
	  {
		  musics[i][0] = 0;
	  }
	  
	  //fill the new WAV list
	  WavListFiles((char**)musics);
  }
  #endif
}

const command_t mount_cmd = {
  "mount", cmd_mount, "Mount SD Card"
};


// Safely remove SD Card Command
void cmd_sr(char *param)
{  
  (void)*param;
  
  // Remove SD card safely
  (void)SDCard_SafeRemove(VERBOSE_ON);
}

const command_t sr_cmd = {
  "sr", cmd_sr, "Safely remove the SD Card"
};


// SD Card Delete Command
void cmd_rm(char *param)
{  
  INT8U     i       = 0;
  INT8U     retorno = 0;
  CHAR8     name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos  
  CHAR8     name2[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos 
  
  for(i=0;i<(CONSOLE_BUFFER_SIZE/2);i++)
  {
    // Limpa o buffer de entradas
    name1[i] = 0;
    name2[i] = 0;
  }      
  
  i = 0;  
  entradas[0] = 0x20;
  i++;
  
  while(*param)
  {
    if (i < CONSOLE_BUFFER_SIZE)
    {  
      entradas[i] = *param;
      i++;
      param++;
    }else
    {
      break;
    }
  }
  
  if (entradas[1] == '*') // remove all
  {
	FRESULT fr;
	  
	strcpy(name1, "/");  /* Directory to be emptied */
	fr = empty_directory(name1);

	if (fr) {
		printSer(USE_USB, (CHAR8*)"\r\nFunction failed.\r\n");
	} else {
		printSer(USE_USB, (CHAR8*)"\r\nAll contents were successfully removed.\n");
	}
	
  }
  else
  {
	  // verifica o nome digitado
	  retorno = file_name_verify(name1,name2,(INT8U*)&entradas[0],1);
	  
	  if(retorno==API_COMMAND_OK)
	  {
		(void)DeleteFile(name1, VERBOSE_ON);
	  }
	  else
	  {
		printSer(USE_USB, (CHAR8*)SD_API_FILE_INVALID);
	  }
  }
  
  for(i=0;i<CONSOLE_BUFFER_SIZE;i++)
  {
    // Limpa o buffer de entradas
    entradas[i] = 0;
  }  
}

const command_t rm_cmd = {
  "rm", cmd_rm, "SD Card - Delete File or Directory"
};


// SD Card Rename Command
void cmd_rn(char *param)
{  
  INT8U     i       = 0;
  INT8U     retorno = 0;
  CHAR8 name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos  
  CHAR8 name2[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos 
  
  for(i=0;i<(CONSOLE_BUFFER_SIZE/2);i++)
  {
    // Limpa o buffer de entradas
    name1[i] = 0;
    name2[i] = 0;
  }      
  i = 0;
  
  entradas[0] = 0x20;
  i++;
  
  while(*param)
  {
    if (i < CONSOLE_BUFFER_SIZE)
    {  
      entradas[i] = *param;
      i++;
      param++;
    }else
    {
      break;
    }
  }
  
  // verifica o nome digitado
  retorno = file_name_verify(name2,name1,(INT8U*)&entradas[0],2);
  
  if(retorno==API_COMMAND_OK)
  {
    (void)RenameFile(name1,name2,VERBOSE_ON);
  }
  else
  {
	printSer(USE_USB, (CHAR8*)SD_API_FILE_INVALID);
  }
  
  for(i=0;i<CONSOLE_BUFFER_SIZE;i++)
  {
    // Limpa o buffer de entradas
    entradas[i] = 0;
  }  
}

const command_t rn_cmd = {
  "rn", cmd_rn, "SD Card - Rename File"
};


// SD Card Create File Command
void cmd_cr(char *param)
{  
  INT8U i       = 0;
  INT8U retorno = 0;
  CHAR8 name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos  
  CHAR8 name2[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos 
  
  
  for(i=0;i<(CONSOLE_BUFFER_SIZE/2);i++)
  {
    // Limpa o buffer de entradas
    name1[i] = 0;
  }  
  
  i = 0;
  entradas[0] = 0x20;
  i++;
  
  while(*param)
  {
    if (i < CONSOLE_BUFFER_SIZE)
    {  
      entradas[i] = *param;
      i++;
      param++;
    }else
    {
      break;
    }
  }
  
  // verifica o nome digitado
  retorno = file_name_verify(name1,name2,(INT8U*)&entradas[0],1);
  
  if(retorno==API_COMMAND_OK)
  {
    (void)CreateFile(name1,VERBOSE_ON);
  }
  else
  {
	printSer(USE_USB, (CHAR8*)SD_API_FILE_INVALID);
  }
  
  for(i=0;i<CONSOLE_BUFFER_SIZE;i++)
  {
    // Limpa o buffer de entradas
    entradas[i] = 0;
  }
}

const command_t cr_cmd = {
  "cr", cmd_cr, "SD Card - Create file"
};


// SD Card Make Dir Command
void cmd_mkdir(char *param)
{  
  INT8U i       = 0;
  INT8U retorno = 0;
  CHAR8 name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos  
  CHAR8 name2[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos 
  
  for(i=0;i<(CONSOLE_BUFFER_SIZE/2);i++)
  {
    // Limpa o buffer de entradas
    name1[i] = 0;
    name2[i] = 0;
  }      
  
  i = 0;  
  entradas[0] = 0x20;
  i++;
  
  while(*param)
  {
    if (i < CONSOLE_BUFFER_SIZE)
    {  
      entradas[i] = *param;
      i++;
      param++;
    }else
    {
      break;
    }
  }
  
  // verifica o nome digitado
  retorno = file_name_verify(name1,name2,(INT8U*)&entradas[0],1);
  
  if(retorno==API_COMMAND_OK)
  {
    (void)CreateDir(name1,VERBOSE_ON);
  }
  else
  {
	printSer(USE_USB, (CHAR8*)SD_API_FILE_INVALID);
  }  
  
  for(i=0;i<CONSOLE_BUFFER_SIZE;i++)
  {
    // Limpa o buffer de entradas
    entradas[i] = 0;
  }
}

const command_t mkdir_cmd = {
  "mkdir", cmd_mkdir, "SD Card - Make Dir"
};


// SD Card Copy File Command
void cmd_cp(char *param)
{  
  INT8U     i       = 0;
  INT8U     retorno = 0;
  CHAR8 name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos  
  CHAR8 name2[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos 
  
  for(i=0;i<(CONSOLE_BUFFER_SIZE/2);i++)
  {
    // Limpa o buffer de entradas
    name1[i] = 0;
    name2[i] = 0;
  }      
  i = 0;
  
  entradas[0] = 0x20;
  i++;
  
  while(*param)
  {
    if (i < CONSOLE_BUFFER_SIZE)
    {  
      entradas[i] = *param;
      i++;
      param++;
    }else
    {
      break;
    }
  }
  
  // verifica o nome digitado
  retorno = file_name_verify(name2,name1,(INT8U*)&entradas[0],2);
  
  if(retorno==API_COMMAND_OK)
  {
    (void)CopyFile(name1,name2,VERBOSE_ON);
  }
  else
  {
	printSer(USE_USB, (CHAR8*)SD_API_FILE_INVALID);
  }
  
  for(i=0;i<CONSOLE_BUFFER_SIZE;i++)
  {
    // Limpa o buffer de entradas
    entradas[i] = 0;
  }  
}

const command_t cp_cmd = {
  "cp", cmd_cp, "SD Card - Copy File"
};


// SD Card Write File Test Command
void cmd_wt(char *param)
{  
  INT8U i       = 0;
  INT8U retorno = 0; 
  
  entradas[0] = 0x20;
  i++;
  
  while(*param)
  {
    if (i < CONSOLE_BUFFER_SIZE)
    {  
      entradas[i] = *param;
      i++;
      param++;
    }else
    {
      break;
    }
  }
  
  // verifica o nome digitado
  //retorno = file_name_verify(name1,name2,(INT8U*)&entradas[0],1);
  retorno = API_COMMAND_OK;
  
  if(retorno==API_COMMAND_OK)
  {
    (void)WriteUptimeLog(VERBOSE_ON);
  }
  else
  {
	printSer(USE_USB, (CHAR8*)SD_API_FILE_INVALID);
  }  
  
  for(i=0;i<CONSOLE_BUFFER_SIZE;i++)
  {
    // Limpa o buffer de entradas
    entradas[i] = 0;
  }
}

const command_t wt_cmd = {
  "wt", cmd_wt, "SD Card - Write Uptime - Test for write file"
};

static INT8U stdout = USE_USB;
BRTOS_Queue *stdin_q = NULL;

extern OS_QUEUE SerialPortBuffer1;
extern BRTOS_Queue *Serial1;

extern OS_QUEUE SerialPortBuffer2;
extern BRTOS_Queue *Serial2;


// Print a string in the terminal
void cmd_echo(char *param)
{
	INT8U caracter;
	if(param == NULL) return;
	printSer(USE_USB, "\n\r");

#if UART1_MUTEX
	if(stdout == USE_UART1)
	{
		uart1_acquire();
	}
#endif
	
#if UART2_MUTEX
	if(stdout == USE_UART2)
	{
		uart2_acquire();
	}
#endif
	
	printSer(stdout, (CHAR8*)param);
	printSer(stdout, "\r");
		
	if(stdin_q != NULL)
	{
		while(OSQueuePend(stdin_q, &caracter, 100) != TIMEOUT)
		{
			putcharSer(USE_USB, (CHAR8)caracter);
		}	
	}
	
#if UART1_MUTEX
	if(stdout == USE_UART1)
	{
		uart1_release();
	}
#endif	
	
#if UART2_MUTEX
	if(stdout == USE_UART2)
	{
		uart2_release();
	}
#endif	
}

const command_t echo_cmd = {
  "echo", cmd_echo, "Print the string in the terminal"
};

// Print a string in the terminal
void cmd_echo_out(char *param)
{	
	INT8U std_output;
	printSer(USE_USB, "\n\r");	
	if(param != NULL)
	{		
		std_output = (INT8U)(param[0]-'0');
		if(std_output >= 0 && std_output <= 9)
		{
			stdout = std_output;
			if (stdout == USE_UART1)
			{
				stdin_q = Serial1;
			}
			if (stdout == USE_UART2)
			{
				stdin_q = Serial2;
			}
			printSer(USE_USB, "STDOUT = ");
			putcharSer(USE_USB, (CHAR8)param[0]);
			printSer(USE_USB, "\n\r");
			return;
		}
	}

	error:
		printSer(USE_USB, "INVALID STDOUT\n\r");


}

const command_t echo_stdout_cmd = {
  "stdout", cmd_echo_out, "Set std output for echo cmd"
};


// Function used to print a string in the terminal by other tasks
void echo (char *string, char Terminalbackup)
{
    INT8U backup_cnt = 0;
    INT8U i = 0;
    char backup[(CONSOLE_BUFFER_SIZE/2)];
	char *command_start = "echo ";
    char *command_end   = "\n\r";
    
    if (Terminalbackup == TRUE)
    {
    	backup_cnt = TerminalBackup(&backup[0]);
    }
    
    SetSilentMode(TRUE);
    while (*command_start)
    {
			if (OSQueuePost(USB, *command_start++) == BUFFER_UNDERRUN)
			{
			  // Problema: Estouro de buffer
			  OSCleanQueue(USB);
			}
    }    
    
	while (*string)
    {
			if (OSQueuePost(USB, *string++) == BUFFER_UNDERRUN)
			{
			  // Problema: Estouro de buffer
			  OSCleanQueue(USB);
			}
    }
    
    while (*command_end)
    {
			if (OSQueuePost(USB, *command_end++) == BUFFER_UNDERRUN)
			{
			  // Problema: Estouro de buffer
			  OSCleanQueue(USB);
			}
    }
    
    if (Terminalbackup == TRUE)
    {
		for(i=0;i<backup_cnt;i++)
		{
			if (OSQueuePost(USB, backup[i]) == BUFFER_UNDERRUN)
			{
			  // Problema: Estouro de buffer
			  OSCleanQueue(USB);
			}    	
		}
    }
}

#include "esp8266_at.h"

//const INT8U esp_buffer_send[];
//INT8U esp_buffer_rx[64];

void cmd_esp(char *param)
{	
	printf_usb("\r\n");
	switch (param[0])
	{
		case '1': at_esp_init();
			break;
		case '2': at_esp_open();
			break;
		case '3': at_esp_send(NULL);
					break;
		case '4': at_esp_receive(NULL,NULL);
					break;					
		case '5': at_esp_close();
			break;
		case '6':
			at_esp_init();
			at_esp_open();
			at_esp_send(NULL);
			break;
		default:
			printf_usb(	"\r\n usage:\r\n"
						"1 - init \r\n"
						"2 - open \r\n"
						"3 - send \r\n"
						"4 - receive \r\n"
						"5 - close \r\n"
					  );
	}
}

const command_t esp_cmd = {
  "esp", cmd_esp, "Control ESP8266"
};


#include "m590_at.h"

//const INT8U esp_buffer_send[];
//INT8U esp_buffer_rx[64];

void cmd_m590(char *param)
{	
	printf_usb("\r\n");
	switch (param[0])
	{
		case '1': at_m590_init();
			break;
		case '2': at_m590_open();
			break;
		case '3': at_m590_send(NULL);
			break;
		case '4': at_m590_receive(NULL,NULL);
			break;					
		case '5': at_m590_close();
			break;
		case '6':
			at_m590_init();
			at_m590_open();
			at_m590_send(NULL);
			break;	
		case '7': at_m590_server();
			break;			
		case '8': at_m590_dns(param);
			break;	
		default:
			printf_usb(	"\r\n usage:\r\n"
						"1 - init \r\n"
						"2 - open \r\n"
						"3 - send \r\n"
						"4 - receive \r\n"
						"5 - close \r\n"
						"6 - init, open, send \r\n"
						"7 - server \r\n"
					  );
	}
	param[0] = 0;
}

const command_t m590_cmd = {
  "m590", cmd_m590, "Control M590 modem"
};

// D/A converter sin wave Command
INT16S wave[32]={2048,2447,2831,3185,3495,3750,3939,4056,4095,4056,3939,3750,3495,3185,2831,2447,
		2048,1649,1265,911,601,346,157,40,1,40,157,346,601,911,1265,1649};

void cmd_sin2da(char *param)
{
  INT16U i = 0;
  INT16U j = 0;
  (void)*param;
  while(1)
  {
	  DAConvert(wave[i]);
      DelayTask(2);
	  i++;
	  if (i >= 32)
	  {
		  i = 0;
		  j++;
	  }
	  if (j >= 8) break;
  }    
}

const command_t sin2da_cmd = 
{
  "sin2da", cmd_sin2da, "Play a sin wave through D/A converter"
};

/*----------------------------------------------------------------------*/
/* Play Wave sound from SD Card Command									*/
/*----------------------------------------------------------------------*/
#if (SD_WAVE == 1)
extern BRTOS_Sem   	    *Play;
extern BRTOS_Mutex 		*SLCDResource;
extern INT8U			PlayState;
extern OSTime 			Play_Time;
CHAR8 					SoundName[(CONSOLE_BUFFER_SIZE/2)];

// Play Wave sound from SD Card Command
void cmd_play (char *param)
{  
  INT8U i       	= 0;
  INT8U retorno 	= 0;
  INT8U playstate 	= 0;
  
  i = 0;  
  entradas[0] = 0x20;
  i++;
  
  while(*param)
  {
    if (i < CONSOLE_BUFFER_SIZE)
    {  
      entradas[i] = *param;
      i++;
      param++;
    }else
    {
      break;
    }
  }
  
  // verifica o nome digitado, e retorna em name1
  retorno = file_name_verify(&SoundName[0],&SoundName[0],(INT8U*)&entradas[0],1);
  
  if(retorno==API_COMMAND_OK)
  {
	UserEnterCritical();
	playstate = PlayState;
	UserExitCritical();

	switch(playstate)
	{
		case STOP:
			if ((GetCardStat() & STA_NOINIT) != STA_NOINIT)
			{
			  //Play file			
			  printSer(USE_USB, "\n\rPlaying the file ");
			  printSer(USE_USB, &SoundName[0]);
			  printSer(USE_USB, "\n\r");
			  
			   
			  // Muda estado do player de audio
			  UserEnterCritical();
			  PlayState = PLAYING;
			  UserExitCritical();
			   
			  //Libera para dar Play
			  (void)OSSemPost(Play);
			}else
			{
				printSer(USE_USB, (CHAR8*)SD_API_CARD_NOT_PRESENT);
			}
		   break;

		case PAUSE:
			printSer(USE_USB, "\n\rThere is already a file being played...\n\r");
			break;		   
		   
		case PLAYING:
			printSer(USE_USB, "\n\rThere is already a file being played...\n\r");
			break;
			
		default:
			break;
	}
  }
  else
  {
	  printSer(USE_USB, (CHAR8*)SD_API_FILE_INVALID);
  }  
  
  for(i=0;i<CONSOLE_BUFFER_SIZE;i++)
  {
    // Limpa o buffer de entradas
    entradas[i] = 0;
  }
}


const command_t play_cmd = {
  "play", cmd_play, "SD Card - Play Wave sound"
};


/*----------------------------------------------------------------------*/
/* Pause a playing Wave sound from SD Card Command						*/
/*----------------------------------------------------------------------*/
void cmd_pause(char *param)
{
	INT8U playstate = 0;
	
	(void)*param;
	UserEnterCritical();
	playstate = PlayState;
	UserExitCritical();

	switch(playstate)
	{
		case STOP:
			printSer(USE_USB, "\n\rThere is no sound to be paused...\n\r");
			break;
			
		case PLAYING:
			printSer(USE_USB, "\n\rPaused...\n\r");		
			
			// Muda estado do player de audio
			UserEnterCritical();
			PlayState = PAUSE;
			UserExitCritical();
			
			BlockPriority(ReadWaveFilePriority);			
			break;
			
		case PAUSE:
			printSer(USE_USB, "\n\rContinuing to play...\n\r");			
			
			// Muda estado do player de audio						
			UserEnterCritical();
			PlayState = PLAYING;
			UserExitCritical();
			
			UnBlockPriority(ReadWaveFilePriority);			
			break;
		
		default:
			break;
	}
  
}

const command_t pause_cmd = {
  "pause", cmd_pause, "Pause the current playing sound"
};


/*----------------------------------------------------------------------*/
/* Stop a playing Wave sound from SD Card Command						*/
/*----------------------------------------------------------------------*/
void cmd_stop(char *param)
{
	INT8U playstate = 0;
	
	(void)*param;
	UserEnterCritical();
	playstate = PlayState;
	UserExitCritical();

	switch(playstate)
	{
		case STOP:
			printSer(USE_USB, "\n\rThere is no sound to be stopped...\n\r");
			break;
			
		case PLAYING:
			printSer(USE_USB, "\n\rThe file being played was stopped...\n\r");
			
			UserEnterCritical();
			PlayState = STOP;
			UserExitCritical();
			
			// Reset play time counter
			OSResetTime(&Play_Time);
			break;
			
		case PAUSE:
			printSer(USE_USB, "\n\rThe file being played was stopped...\n\r");
			
			UserEnterCritical();
			PlayState = STOP;
			UserExitCritical();
			
			// Reset play time counter
			OSResetTime(&Play_Time);
			
			UnBlockPriority(ReadWaveFilePriority);		
			break;
		
		default:
			break;
	}
  
}

const command_t stop_cmd = {
  "stop", cmd_stop, "Stop the current playing sound"
};


void cmd_vol(char *param)
{  
  INT8U i       = 0;
  INT8U retorno = 0;
  CHAR8 name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos  
  CHAR8 name2[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos 
  
  for(i=0;i<(CONSOLE_BUFFER_SIZE/2);i++)
  {
    // Limpa o buffer de entradas
    name1[i] = 0;
    name2[i] = 0;
  }      
  
  i = 0;  
  entradas[0] = 0x20;
  i++;
  
  while(*param)
  {
    if (i < CONSOLE_BUFFER_SIZE)
    {  
      entradas[i] = *param;
      i++;
      param++;
    }else
    {
      break;
    }
  }
  
  // verifica o nome digitado, e retorna em name1
  retorno = file_name_verify(name1,name2,(INT8U*)&entradas[0],1);
  
  if(retorno==API_COMMAND_OK)
  {
	  (void)ChangeVol(name1,VERBOSE_ON);
  
  }
  else
  {
	  printSer(USE_USB, "Invalid argument");
  }  
  
  for(i=0;i<CONSOLE_BUFFER_SIZE;i++)
  {
    // Limpa o buffer de entradas
    entradas[i] = 0;
  }
}


const command_t vol_cmd = {
  "vol", cmd_vol, "Control Audio Volume"
};

void cmd_play_LCD (char *param)
{  
  INT8U i       	= 0;
  INT8U retorno 	= 0;
  INT8U playstate 	= 0;
  

	UserEnterCritical();
	playstate = PlayState;
	UserExitCritical();
	
	while(*param)
	{
		SoundName[i++] = *param++;
	}
	SoundName[i] = 0;
		
	switch(playstate)
	{
		case STOP:
			if ((GetCardStat() & STA_NOINIT) != STA_NOINIT)
			{
			  //Play file			
			   
			  // Muda estado do player de audio
			  UserEnterCritical();
			  PlayState = PLAYING;
			  UserExitCritical();
			   
			  //Libera para dar Play
			  (void)OSSemPost(Play);
			}
		   break;

		case PAUSE:
			// Muda estado do player de audio						
			UserEnterCritical();
			PlayState = PLAYING;
			UserExitCritical();
			
			UnBlockPriority(ReadWaveFilePriority);	
			break;		   
		   
		case PLAYING:
			// Muda estado do player de audio
			UserEnterCritical();
			PlayState = PAUSE;
			UserExitCritical();
			
			BlockPriority(ReadWaveFilePriority);
			break;
			
		default:
			break;
	}
}

void cmd_stop_LCD(void)
{
	INT8U playstate = 0;
	
	UserEnterCritical();
	playstate = PlayState;
	UserExitCritical();

	switch(playstate)
	{
		case STOP:
			break;
			
		case PLAYING:
			UserEnterCritical();
			PlayState = STOP;
			UserExitCritical();
			break;
			
		case PAUSE:
			UserEnterCritical();
			PlayState = STOP;
			UserExitCritical();
			
			UnBlockPriority(ReadWaveFilePriority);		
			break;
		
		default:
			break;
	}
  
}


#endif

