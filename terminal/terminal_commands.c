/****************************************************************************************
* 
*   FILE        :    terminal_commands.c
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
 * terminal_commands.c
 *
 *  Created on: 12/05/2011
 *      Author: UFSM
 */
#include "BRTOS.h"
#include "AppConfig.h"
#include "terminal.h"
#include "terminal_commands.h"
#include "terminal_io.h"
#include "virtual_com.h"
#include "UART.h"
#include "utils.h"
#include "debug_stack.h"
#include "tasks.h"
#include "da.h"
#include "string.h"

INT8U entradas[CONSOLE_BUFFER_SIZE]; //vetor para a entrada de dados

// BRTOS version Command
void term_cmd_ver(char *param)
{
  (void)*param;
  printf_terminal("\n\r");
  printf_terminal((CHAR8*)version);
  printf_terminal("\n\r");
}

CONST command_t ver_cmd = {
  "ver", term_cmd_ver, "BRTOS Version"
};



// TOP Command (similar to the linux command)
void term_cmd_top(char *param)
{
  (void)*param;
  printf_terminal("\n\r");
  Transmite_CPU_Load(USE_USB);
  Transmite_Uptime(USE_USB);
  Transmite_RAM_Ocupada(USE_USB);
  Transmite_Task_Stacks(USE_USB);
}

CONST command_t top_cmd = {
  "top", term_cmd_top, "BRTOS TOP"
};


// Reason of Reset Command
void term_cmd_rst(char *param)
{
  (void)*param;
  printf_terminal("\n\r");
  Reason_of_Reset(USE_USB);
}

CONST command_t rst_cmd = {
  "rst", term_cmd_rst, "CPU Reason of the Reset"
};

// Core temperature Command
extern INT16S CoreTemp;
void term_cmd_temp(char *param)
{
  INT16S temp;
  CHAR8  string[8];
  (void)*param;
  
  UserEnterCritical();
  temp = CoreTemp;
  UserExitCritical();
  
  PrintDecimal(temp, string);
  printf_terminal("\n\r");
  printf_terminal((CHAR8*)&string[3]);
  printf_terminal(" degrees");
}

CONST command_t temp_cmd = {
  "temp", term_cmd_temp, "Show core temperature"
};

void term_cmd_setget_time(char *param){
	
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
			printf_terminal("\n\r =");
		else
			printf_terminal("\n\r <");
		
		goto print_date;
		
	}
	else
	{
		printf_terminal("\n\r > ");
		
		datetime = rtc;
		goto print_date;	
	}
	
print_date:
	char string[5];
			
	/* print current Date & Time */
	printf_terminal("\n\r");
	
	/* day */
	Print2Digits(datetime.Day, ZEROS_ALIGN, string);
	printf_terminal((CHAR8*)string);
	printf_terminal("/");
	
	/* month */
	Print2Digits(datetime.Month, ZEROS_ALIGN, string);
	printf_terminal((CHAR8*)string);
	printf_terminal("/");
	
	/* year */
	Print4Digits(datetime.Year, ZEROS_ALIGN, string);
	printf_terminal((CHAR8*)string);
	printf_terminal(" ");
	
	/* hour */
	Print2Digits(datetime.Hour, ZEROS_ALIGN, string);
	printf_terminal((CHAR8*)string);
	printf_terminal(":");
	
	/* minutes */
	Print2Digits(datetime.Min, ZEROS_ALIGN, string);
	printf_terminal((CHAR8*)string);
	printf_terminal(":");
	
	/* seconds */
	Print2Digits(datetime.Sec, ZEROS_ALIGN, string);
	printf_terminal((CHAR8*)string);	
	printf_terminal("\n\r");

#else	
	print_date:
		INT8U string[15]; // yyyymmddhhmmss	
		OSDateTime timestamp;
		
		GetDateTime(&timestamp);
		PrintDateTime(&timestamp, string);
				
		/* print current Date & Time */
		printf_terminal("\n\r");
		printf_terminal((CHAR8*)string);
		printf_terminal("\n\r");
#endif		
	
}

CONST command_t setget_time_cmd = {
  "time", term_cmd_setget_time, "Set/Get OS Date and Time"
};


// File Read Command
void term_cmd_cat(char *param)
{  
  INT8U i       = 0;
  INT8U retorno = 0;
  CHAR8 name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos  
  CHAR8 name2[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos 
  
  // Limpa o buffer de entradas
  memset(name1,0x00,CONSOLE_BUFFER_SIZE/2);  
  memset(name2,0x00,CONSOLE_BUFFER_SIZE/2);  
  memset(entradas,0x00,CONSOLE_BUFFER_SIZE); 
  
  entradas[0] = 0x20;  
  strncpy(&entradas[1], param,CONSOLE_BUFFER_SIZE-1);
  
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
  
}

CONST command_t cat_cmd = {
  "cat", term_cmd_cat, "SD Card - Read file"
};


// List Files Command
void term_cmd_ls(char *param)
{  
  INT8U name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos 
  
  (void)*param;

  // Limpa o buffer de entradas
  memset(name1,0x00,CONSOLE_BUFFER_SIZE/2);
  memset(entradas,0x00,CONSOLE_BUFFER_SIZE);
  (void)ListFiles(name1);
  
}

CONST command_t ls_cmd = {
  "ls", term_cmd_ls, "SD Card - List files"
};


// Change Dir Command
void term_cmd_cd(char *param)
{  
  INT8U i       = 0;
  INT8U retorno = 0;
  CHAR8 name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos  
  CHAR8 name2[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos 
  
  // Limpa o buffer de entradas
  memset(name1,0x00,CONSOLE_BUFFER_SIZE/2);
  memset(name2,0x00,CONSOLE_BUFFER_SIZE/2);
  memset(entradas,0x00,CONSOLE_BUFFER_SIZE);
  
  entradas[0] = 0x20;  
  strncpy(&entradas[1], param,CONSOLE_BUFFER_SIZE-1);
  
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

}

CONST command_t cd_cmd = {
  "cd", term_cmd_cd, "SD Card - Change Dir"
};

// Mount SD Card Command
#if (SD_WAVE == 1)
extern char musics[WAV_LIST_SIZE][WAV_NAME_SIZE];
#endif

void term_cmd_mount(char *param)
{    
  INT8U status = 0;
  INT8U i = 0; 

  (void)*param;
  
  // Initialize SD card
  status = SDCard_Init(VERBOSE_ON);
}

CONST command_t mount_cmd = {
  "mount", term_cmd_mount, "Mount SD Card"
};


// Safely remove SD Card Command
void term_cmd_sr(char *param)
{  
  (void)*param;
  
  // Remove SD card safely
  (void)SDCard_SafeRemove(VERBOSE_ON);
}

CONST command_t sr_cmd = {
  "sr", term_cmd_sr, "Remove SD Card"
};


// File Delete Command
void term_cmd_rm(char *param)
{  
  INT8U     i       = 0;
  INT8U     retorno = 0;
  CHAR8     name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos  
  CHAR8     name2[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos 
  
  memset(name1,0x00,CONSOLE_BUFFER_SIZE/2);  
  memset(name2,0x00,CONSOLE_BUFFER_SIZE/2);  
  memset(entradas,0x00,CONSOLE_BUFFER_SIZE);
  
  i = 0;  
  entradas[0] = 0x20;
  i++;
  
  entradas[0] = 0x20;  
  strncpy(&entradas[1], param,CONSOLE_BUFFER_SIZE-1);
  
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
}

CONST command_t rm_cmd = {
  "rm", term_cmd_rm, "Delete File or Dir"
};


// File Rename Command
void term_cmd_rn(char *param)
{  
  INT8U     retorno = 0;
  CHAR8 name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos  
  CHAR8 name2[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos 
  
  memset(name1,0x00,CONSOLE_BUFFER_SIZE/2);  
  memset(name2,0x00,CONSOLE_BUFFER_SIZE/2);  
  memset(entradas,0x00,CONSOLE_BUFFER_SIZE);
  
  entradas[0] = 0x20;  
  strncpy(&entradas[1], param,CONSOLE_BUFFER_SIZE-1);
  
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
}

CONST command_t rn_cmd = {
  "rn", term_cmd_rn, "SD Card - Rename File"
};


// Create File Command
void term_cmd_cr(char *param)
{  
  INT8U retorno = 0;
  CHAR8 name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos  
  CHAR8 name2[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos 
  
  
  memset(name1,0x00,CONSOLE_BUFFER_SIZE/2);  
  memset(name2,0x00,CONSOLE_BUFFER_SIZE/2);  
  memset(entradas,0x00,CONSOLE_BUFFER_SIZE);
  
  entradas[0] = 0x20;  
  strncpy(&entradas[1], param,CONSOLE_BUFFER_SIZE-1);
  
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
}

CONST command_t cr_cmd = {
  "cr", term_cmd_cr, "SD Card - Create file"
};


// Make Dir Command
void term_cmd_mkdir(char *param)
{  
  INT8U i       = 0;
  INT8U retorno = 0;
  CHAR8 name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos  
  CHAR8 name2[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos 
  
  memset(name1,0x00,CONSOLE_BUFFER_SIZE/2);  
  memset(name2,0x00,CONSOLE_BUFFER_SIZE/2);   
  memset(entradas,0x00,CONSOLE_BUFFER_SIZE);
  
  entradas[0] = 0x20;  
  strncpy(&entradas[1], param,CONSOLE_BUFFER_SIZE-1);
  
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
}

CONST command_t mkdir_cmd = {
  "mkdir", term_cmd_mkdir, "SD Card - Make Dir"
};


// Copy File Command
void term_cmd_cp(char *param)
{  
  INT8U     i       = 0;
  INT8U     retorno = 0;
  CHAR8 name1[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos  
  CHAR8 name2[(CONSOLE_BUFFER_SIZE/2)]; //vetor para a leitura dos nomes dos arquivos 
  
  memset(name1,0x00,CONSOLE_BUFFER_SIZE/2);  
  memset(name2,0x00,CONSOLE_BUFFER_SIZE/2);  
  memset(entradas,0x00,CONSOLE_BUFFER_SIZE);
  
  entradas[0] = 0x20;  
  strncpy(&entradas[1], param,CONSOLE_BUFFER_SIZE-1);
  
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
}

CONST command_t cp_cmd = {
  "cp", term_cmd_cp, "SD Card - Copy File"
};


// Write File Test Command
void term_cmd_wt(char *param)
{  
  
  entradas[0] = 0x20;  
  strncpy(&entradas[1], param,CONSOLE_BUFFER_SIZE-1);   
 (void)WriteUptimeLog(VERBOSE_ON);
 
}

CONST command_t wt_cmd = {
  "wt", term_cmd_wt, "Write Uptime"
};

static INT8U stdout = USE_USB;
BRTOS_Queue *stdin_q = NULL;

extern OS_QUEUE SerialPortBuffer1;
extern BRTOS_Queue *Serial1;

extern OS_QUEUE SerialPortBuffer2;
extern BRTOS_Queue *Serial2;


// Print a string in the terminal
void term_cmd_echo(char *param)
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

CONST command_t echo_cmd = {
  "echo", term_cmd_echo, "Print in terminal"
};

// Print a string in the terminal
void term_cmd_echo_out(char *param)
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

CONST command_t echo_stdout_cmd = {
  "stdout", term_cmd_echo_out, "Set output for echo"
};


void echo_post(INT8U * dados, INT8U len)
{
	while(len>0)
	{
		if (OSQueuePost(USB, *dados) == BUFFER_UNDERRUN)
		{ 
		  OSCleanQueue(USB); // Problema: Estouro de buffer
		}   
		len--;
	}
}

// Function used to print a string in the terminal by other tasks
void echo (char *string, char Terminalbackup)
{
    INT8U backup_cnt = 0;
    INT8U i = 0;
    char backup[(CONSOLE_BUFFER_SIZE/2)];
	const char *command_start = "echo ";
	const char *command_end   = "\n\r";
    
    if (Terminalbackup == TRUE)
    {
    	backup_cnt = TerminalBackup(&backup[0]);
    }
    
    SetSilentMode(TRUE);
    echo_post(command_start,strlen(command_start));
    echo_post(string,strlen(string));
    echo_post(command_end,strlen(command_end));
    
    if (Terminalbackup == TRUE)
    {		
    	echo_post(backup,backup_cnt);    	
    }
}

#include "esp8266_at.h"

CONST char cmd_esp_help[] = {
		"\r\n usage:\r\n"
		"1 - init \r\n"
		"2 - open \r\n"
		"3 - send \r\n"
		"4 - receive \r\n"
		"5 - close \r\n"		
};
void term_cmd_esp(char *param)
{	
	printf_terminal("\r\n");
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
			printf_terminal(cmd_esp_help);
	}
}

CONST command_t esp_cmd = {
  "esp", term_cmd_esp, "Control ESP8266"
};


#include "m590_at.h"

CONST char cmd_m590_help[] = {
		"\r\n usage:\r\n"
		"1 - init \r\n"
		"2 - open \r\n"
		"3 - send \r\n"
		"4 - receive \r\n"
		"5 - close \r\n"
		"6 - init, open, send \r\n"
		"7 - server \r\n"
};

void term_cmd_m590(char *param)
{	
	printf_terminal("\r\n");
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
			printf_terminal(cmd_m590_help);
	}
	param[0] = 0;
}

CONST command_t m590_cmd = {
  "m590", term_cmd_m590, "Control M590 modem"
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

CONST command_t sin2da_cmd = 
{
  "sin2da", cmd_sin2da, "Sin wave to DAC"
};

