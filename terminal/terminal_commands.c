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
/*
 * terminal_commands.c
 *
 *  Created on: 12/05/2011
 *      Author: UFSM
 */
#include "BRTOS.h"
#include "AppConfig.h"
#include "drivers.h"
#include "terminal.h"
#include "terminal_commands.h"
#include "terminal_io.h"
#include "utils.h"
#include "debug_stack.h"
#include "tasks.h"
#include "string.h"
#include "printf_lib.h"
//#include "stdio.h"

#define Help_HelpText_def "Help of commands"
#define Ver_HelpText_def "BRTOS Version"
#define Top_HelpText_def "BRTOS TOP"
#define Rst_HelpText_def "CPU Reason of the Reset"
#define Temp_HelpText_def "Show core temperature"
#define SetGetTime_HelpText_def "Set/Get OS Date and Time"
#define Cat_HelpText_def "Read file"
#define Ls_HelpText_def "List files"
#define Cd_HelpText_def "Change dir"
#define Mount_HelpText_def "Mount SD Card"
#define Sr_HelpText_def "Remove SD Card"
#define Rm_HelpText_def "Remove File"
#define Rn_HelpText_def "Rename File"
#define Cr_HelpText_def "Create File"
#define Mkdir_HelpText_def "Make dir"
#define Cp_HelpText_def "Copy File"
#define Wt_HelpText_def "Write Uptime to File"
#define Echo_HelpText_def "Print in terminal"
#define EchoOut_HelpText_def  "Set output for echo"
#define Esp_HelpText_def "Control ESP8266"
#define m590_HelpText_def "Control m590 modem"
#define null_modem_HelpText_def "Control null_modem modem"
#define modem_HelpText_def "Control modem"
#define Modbus_HelpText_def "Control Modbus"
#define monitor_HelpText_def   "Control Monitor"

#if COLDUINO
#include "virtual_com.h"
#define  Help_HelpText Help_HelpText_def
#define  Ver_HelpText Ver_HelpText_def
#define  Top_HelpText Top_HelpText_def
#define  Rst_HelpText Rst_HelpText_def
#define  Temp_HelpText Temp_HelpText_def
#define  SetGetTime_HelpText SetGetTime_HelpText_def
#define  Cat_HelpText Cat_HelpText_def
#define  Ls_HelpText Ls_HelpText_def
#define  Cd_HelpText Cd_HelpText_def
#define  Mount_HelpText Mount_HelpText_def
#define  Sr_HelpText Sr_HelpText_def
#define  Rm_HelpText Rm_HelpText_def
#define  Rn_HelpText Rn_HelpText_def
#define  Cr_HelpText Cr_HelpText_def
#define  Mkdir_HelpText Mkdir_HelpText_def
#define  Cp_HelpText Cp_HelpText_def
#define  Wt_HelpText Wt_HelpText_def
#define  Echo_HelpText Echo_HelpText_def
#define  EchoOut_HelpText  EchoOut_HelpText_def
#define  Esp_HelpText Esp_HelpText_def
#define  m590_HelpText m590_HelpText_def
#define  null_modem_HelpText null_modem_HelpText_def
#define  modem_HelpText modem_HelpText_def
#define  Modbus_HelpText Modbus_HelpText_def
#define  monitor_HelpText monitor_HelpText_def

#elif ARDUINO

typedef enum
{
	HELP = 0, VER, TOP, RST, TEMP, SETGETTIME, CAT, LS, CD, MOUNT, SR, RM,RN, CR_CMD, 
	MKDIR, CP, WT, ECHO, ECHO_OUT, ESP, NULL_MODEM, M590, MODBUS
} enum_help_text_cmd;

const char Ver_HelpText_str[] PROGMEM = Ver_HelpText_def;
const char Top_HelpText_str[] PROGMEM = Top_HelpText_def;
const char Rst_HelpText_str[] PROGMEM = Rst_HelpText_def;
const char Temp_HelpText_str[] PROGMEM = Temp_HelpText_def;
const char SetGetTime_HelpText_str[] PROGMEM = SetGetTime_HelpText_def;
const char Cat_HelpText_str[] PROGMEM = Cat_HelpText_def;
const char Ls_HelpText_str[] PROGMEM = Ls_HelpText_def;
const char Cd_HelpText_str[] PROGMEM = Cd_HelpText_def;
const char Mount_HelpText_str[] PROGMEM = Mount_HelpText_def;
const char Sr_HelpText_str[] PROGMEM = Sr_HelpText_def;
const char Rm_HelpText_str[] PROGMEM = Rm_HelpText_def;
const char Rn_HelpText_str[] PROGMEM = Rn_HelpText_def;
const char Cr_HelpText_str[] PROGMEM = Cr_HelpText_def;
const char Mkdir_HelpText_str[] PROGMEM = Mkdir_HelpText_def;
const char Cp_HelpText_str[] PROGMEM = Cp_HelpText_def;
const char Wt_HelpText_str[] PROGMEM = Wt_HelpText_def;
const char Echo_HelpText_str[] PROGMEM = Echo_HelpText_def;
const char EchoOut_HelpText_str[] PROGMEM =  EchoOut_HelpText_def;
const char Esp_HelpText_str[] PROGMEM = Esp_HelpText_def;
const char m590_HelpText_str[] PROGMEM = m590_HelpText_def;
const char null_modem_HelpText_str[] PROGMEM = null_modem_HelpText_def;
const char modem_HelpText_str[] PROGMEM = modem_HelpText_def;
const char Modbus_HelpText_str[] PROGMEM = Modbus_HelpText_def;
const char monitor_HelpText_str[] PROGMEM = monitor_HelpText_def;

#define  Ver_HelpText Ver_HelpText_str
#define  Top_HelpText Top_HelpText_str
#define  Rst_HelpText Rst_HelpText_str
#define  Temp_HelpText Temp_HelpText_str
#define  SetGetTime_HelpText SetGetTime_HelpText_str
#define  Cat_HelpText Cat_HelpText_str
#define  Ls_HelpText Ls_HelpText_str
#define  Cd_HelpText Cd_HelpText_str
#define  Mount_HelpText Mount_HelpText_str
#define  Sr_HelpText Sr_HelpText_str
#define  Rm_HelpText Rm_HelpText_str
#define  Rn_HelpText Rn_HelpText_str
#define  Cr_HelpText Cr_HelpText_str
#define  Mkdir_HelpText Mkdir_HelpText_str
#define  Cp_HelpText Cp_HelpText_str
#define  Wt_HelpText Wt_HelpText_str
#define  Echo_HelpText Echo_HelpText_str
#define  EchoOut_HelpText  EchoOut_HelpText_str
#define  Esp_HelpText Esp_HelpText_str
#define  m590_HelpText m590_HelpText_str
#define  null_modem_HelpText null_modem_HelpText_str
#define  modem_HelpText modem_HelpText_str
#define  Modbus_HelpText Modbus_HelpText_str
#define  monitor_HelpText monitor_HelpText_str

#endif

/* print outputs */
#undef PRINTS_ENABLED
#define PRINTS_ENABLED  1
#include "prints_def.h"

void terminal_newline(void)
{
	printf_terminal_P(PSTR("\n\r"));
}

// BRTOS version Command
void term_cmd_ver(char *param)
{
  (void)*param;
  terminal_newline();
#if COLDUINO  
  printf_terminal((CHAR8*)version);
#elif ARDUINO    
  printf_terminal_P((CHAR8*)pgm_read_word(&(BRTOSStringTable[0])));
#endif  
  terminal_newline();
}


CONST command_t ver_cmd = 
{
  "ver", term_cmd_ver, Ver_HelpText
};

// TOP Command (similar to the linux command)
void term_cmd_top(char *param)
{
  (void)*param;
  terminal_newline();
  Transmite_CPU_Load(USE_USB);
  Transmite_Uptime(USE_USB);
  Transmite_RAM_Ocupada(USE_USB);
  Transmite_Task_Stacks(USE_USB);
}

CONST command_t top_cmd = {
  "top", term_cmd_top, Top_HelpText
};


// Reason of Reset Command
void term_cmd_rst(char *param)
{
  (void)*param;
  terminal_newline();
  Reason_of_Reset(USE_USB);
}

CONST command_t rst_cmd = {
  "rst", term_cmd_rst, Rst_HelpText
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
  terminal_newline();
  printf_terminal((CHAR8*)&string[3]);
  printf_terminal_P(PSTR(" degrees"));
}

CONST command_t temp_cmd = {
  "temp", term_cmd_temp, Temp_HelpText
};

void term_cmd_setget_time(char *param){
	
	OS_RTC datetime; /* dd/mm/yyyy hh:mm:ss */
	char string[5];
	
	if(param != NULL) // set
	{				
		datetime.Day = (INT8U)((*param) - '0')*10; // day
		param++;
		
		if(*param != '\0')
		{    			
		    datetime.Day += (INT8U)((*param++) - '0'); // day		    		    		   
		    if(datetime.Day > 31){	goto time_format_error; }
		    		    
			if(*(++param) != '\0')
			{    			
			    datetime.Month = (INT8U)((*param++) - '0')*10; // month
				if(*param != '\0')
				{    			
				    datetime.Month += (INT8U)((*param++) - '0'); // month				    
				    if(datetime.Month > 12) {	goto time_format_error; }
				    if(*(++param) != '\0')
					{    			
					    datetime.Year = (INT16U)((*param++) - '0')*1000; // year
					    if(*param != '\0')
						{    			
							datetime.Year += (INT16U)((*param++) - '0')*100; // year
						    if(*param != '\0')
							{    			
								datetime.Year += (INT16U)((*param++) - '0')*10; // year
							    if(*param != '\0')
								{    			
									datetime.Year += (INT16U)((*param++) - '0'); // year
									if(datetime.Year > 2100){goto time_format_error; }
									
#if RTC_PRESENTE
									RTC_DS1307_Set_Date((INT8U)((datetime.Year%1000)%100),datetime.Month,datetime.Day);
#endif									
									
									if(*(++param) != '\0') // set
									{			
										datetime.Hour = (INT8U)((*param) - '0')*10; // hour
										*param++ = '\0';
										
										if(*param != '\0')
										{    			
											datetime.Hour += (INT8U)((*param++) - '0'); // hour
											if(datetime.Hour > 23){goto time_format_error; }
											
											if(*(++param) != '\0')
											{    			
												datetime.Min = (INT8U)((*param++) - '0')*10; // min
												if(*param != '\0')
												{    			
													datetime.Min += (INT8U)((*param++) - '0'); // min
													if(datetime.Min > 59){goto time_format_error; }
													
													if(*(++param) != '\0')
													{    			
														datetime.Sec = (INT8U)((*param++) - '0')*10; // sec
														if(*param != '\0')
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
	while(*param != '\0'){
		*param = '\0';	
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
	terminal_newline();
	if( cmp == 0 || cmp == -1)
	{				
		if (cmp == 0)		
			printf_terminal(" =");
		else
			printf_terminal(" <");		
		goto print_date;
		
	}
	else
	{
		printf_terminal(" > ");
		
		datetime = rtc;
		goto print_date;	
	}
	
print_date:
				
	/* print current Date & Time */
	terminal_newline();
	
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
	terminal_newline();

#else	
	print_date:
		INT8U string[15]; // yyyymmddhhmmss	
		OSDateTime timestamp;
		
		GetDateTime(&timestamp);
		PrintDateTime(&timestamp, string);
				
		/* print current Date & Time */
		terminal_newline();
		printf_terminal((CHAR8*)string);
		terminal_newline();
#endif		
	
}

CONST command_t setget_time_cmd = {
  "time", term_cmd_setget_time, SetGetTime_HelpText
};


// File Read Command
void term_cmd_cat(char *param)
{  
  
  char entradas[CONSOLE_BUFFER_SIZE];
  strncpy(entradas, param,CONSOLE_BUFFER_SIZE-1); 
  (void)ReadFile(entradas,VERBOSE_ON);
  
}

CONST command_t cat_cmd = {
  "cat", term_cmd_cat, Cat_HelpText
};


// List Files Command
void term_cmd_ls(char *param)
{  
  
  (void)*param;
  char entradas[CONSOLE_BUFFER_SIZE];
  (void)ListFiles(entradas);
  
}

CONST command_t ls_cmd = {
  "ls", term_cmd_ls, Ls_HelpText
};

// Change Dir Command
void term_cmd_cd(char *param)
{  
  
  char entradas[CONSOLE_BUFFER_SIZE]; 
  strncpy(entradas, param,CONSOLE_BUFFER_SIZE-1);   
  (void)ChangeDir(entradas,VERBOSE_ON);

}

CONST command_t cd_cmd = {
  "cd", term_cmd_cd, Cd_HelpText
};

// Mount SD Card Command
void term_cmd_mount(char *param)
{    

  (void)*param;  
  // Initialize SD card
  (void) SDCard_Init(VERBOSE_ON);
}

CONST command_t mount_cmd = {
  "mount", term_cmd_mount, Mount_HelpText
};


// Safely remove SD Card Command
void term_cmd_sr(char *param)
{  
  (void)*param;  
  // Remove SD card safely
  (void)SDCard_SafeRemove(VERBOSE_ON);
}

CONST command_t sr_cmd = {
  "sr", term_cmd_sr, Sr_HelpText
};


// File Delete Command
void term_cmd_rm(char *param)
{  

  char entradas[CONSOLE_BUFFER_SIZE];
  strncpy(entradas, param,CONSOLE_BUFFER_SIZE-1);
  
  if (entradas[0] == '*') // remove all
  {
	FRESULT fr;
	  
	strncpy(entradas, "/", sizeof(entradas));  /* Directory to be emptied */
	fr = empty_directory(entradas);

	terminal_newline();
	if (fr) {		
		SDCard_PrintStatus(VERBOSE_ON, SD_CARD_ERROR);
	} else {
		SDCard_PrintStatus(VERBOSE_ON, FILE_REMOVED);
	}	
	terminal_newline();
  }
  else
  {	 
	(void)DeleteFile(entradas, VERBOSE_ON);	  
  }  
}

CONST command_t rm_cmd = {
  "rm", term_cmd_rm, Rm_HelpText
};


// File Rename Command
void term_cmd_rn(char *param)
{  

  char *p;
  char entradas[CONSOLE_BUFFER_SIZE];
  CHAR8 name[(CONSOLE_BUFFER_SIZE)]; //vetor para a leitura dos nomes dos arquivos  
  
  memset(name,0x00,CONSOLE_BUFFER_SIZE);  
  memset(entradas,0x00,CONSOLE_BUFFER_SIZE);
 
  if ((p = strrchr(param, ' ')))
  {	  
	  strncpy(entradas, p+1, CONSOLE_BUFFER_SIZE-1); 
	  *(p) = 0;
	  strncpy(name, param, CONSOLE_BUFFER_SIZE-1); 
  }
  (void)RenameFile(name,entradas,VERBOSE_ON);
  
}

CONST command_t rn_cmd = {
  "rn", term_cmd_rn, Rn_HelpText
};


// Create File Command
void term_cmd_cr(char *param)
{  
  
  char entradas[CONSOLE_BUFFER_SIZE];
  strncpy(entradas, param,CONSOLE_BUFFER_SIZE-1); 
 
  (void)CreateFile(entradas,VERBOSE_ON);
}

CONST command_t cr_cmd = {
  "cr", term_cmd_cr, Cr_HelpText
};


// Make Dir Command
void term_cmd_mkdir(char *param)
{  
  char entradas[CONSOLE_BUFFER_SIZE];  
  strncpy(entradas, param,CONSOLE_BUFFER_SIZE-1); 
  (void)CreateDir(entradas,VERBOSE_ON);
}

CONST command_t mkdir_cmd = {
  "mkdir", term_cmd_mkdir, Mkdir_HelpText
};


// Copy File Command
void term_cmd_cp(char *param)
{  
  char *p;
  CHAR8 name[(CONSOLE_BUFFER_SIZE)]; //vetor para a leitura dos nomes dos arquivos
  char entradas[CONSOLE_BUFFER_SIZE];
  
  if ((p = strrchr(param, ' ')))
  {
	  strncpy(entradas, p+1, CONSOLE_BUFFER_SIZE-1);
	  *(p) = 0;
	  strncpy(name, param, CONSOLE_BUFFER_SIZE-1);
  }
 
  (void)CopyFile(name,entradas,VERBOSE_ON);
  
}

CONST command_t cp_cmd = {
  "cp", term_cmd_cp, Cp_HelpText
};


// Write File Test Command
void term_cmd_wt(char *param)
{    
 (void)WriteUptimeLog(VERBOSE_ON);
}

CONST command_t wt_cmd = {
  "wt", term_cmd_wt, "Write uptime"
};

static INT8U term_stdout = USE_USB;
BRTOS_Queue *stdin_q = NULL;

extern BRTOS_Queue *Serial1;
extern BRTOS_Queue *Serial2;


// Print a string in the terminal
void term_cmd_echo(char *param)
{
	INT8U caracter;
	if(param == NULL) return;
	terminal_newline();

#if UART1_MUTEX
	if(term_stdout == USE_UART1)
	{
		uart1_acquire();
	}
#endif
	
#if UART2_MUTEX
	if(term_stdout == USE_UART2)
	{
		uart2_acquire();
	}
#endif
	
	printSer(term_stdout, (CHAR8*)param);
	printSer(term_stdout, "\r\n");
		
	if(stdin_q != NULL)
	{
		while(OSQueuePend(stdin_q, &caracter, 100) != TIMEOUT)
		{
			putchar_terminal( (CHAR8)caracter);
		}	
	}
	
#if UART1_MUTEX
	if(term_stdout == USE_UART1)
	{
		uart1_release();
	}
#endif	
	
#if UART2_MUTEX
	if(term_stdout == USE_UART2)
	{
		uart2_release();
	}
#endif	
}

CONST command_t echo_cmd = {
  "echo", term_cmd_echo, Echo_HelpText
};

// Print a string in the terminal
void term_cmd_echo_out(char *param)
{	
	INT8U std_output;	
	terminal_newline();
	printf_terminal_P(PSTR("STDOUT = "));
	
	if(param != NULL)
	{		
		std_output = (INT8U)(param[0]-'0');
		if(std_output >= 0 && std_output <= 9)
		{
			term_stdout = std_output;
			if (term_stdout == USE_UART1)
			{
				stdin_q = Serial1;
			}
			if (term_stdout == USE_UART2)
			{
				stdin_q = Serial2;
			}			
			putchar_terminal( (CHAR8)param[0]);
			terminal_newline();
			return;
		}
	}else
	{
		putchar_terminal(term_stdout + '0');
	}
	terminal_newline();
}

CONST command_t echo_stdout_cmd = {
  "stdout", term_cmd_echo_out, EchoOut_HelpText
};


static void echo_post(const char * dados, INT8U len)
{
	while(len>0)
	{
#if COLDUINO		
		if (OSQueuePost(USB, *dados) == BUFFER_UNDERRUN)
		{ 
		  OSCleanQueue(USB); // Problema: Estouro de buffer
		}   
#endif		
		len--;
	}
}

// Function used to print a string in the terminal by other tasks
void echo (char *string, char Terminalbackup)
{
    INT8U backup_cnt = 0;
    char backup[(CONSOLE_BUFFER_SIZE/2)];
	const char *command_start = "echo ";
	const char *command_end   = "\n\r";
    
    if (Terminalbackup == TRUE)
    {
    	backup_cnt = TerminalBackup(&backup[0]);
    }
    
    SetSilentMode(TRUE);
    echo_post(command_start,(INT8U)strlen(command_start));
    echo_post(string,(INT8U)strlen(string));
    echo_post(command_end,(INT8U)strlen(command_end));
    
    if (Terminalbackup == TRUE)
    {		
    	echo_post(backup,backup_cnt);    	
    }
}

#include "stdio.h"

#if 0

#include "esp8266_at.h"

CONST char cmd_esp_help[] PROGMEM = {
		"\r\n usage:\r\n"
		"1 - init \r\n"
		"2 - open \r\n"
		"3 - send \r\n"
		"4 - receive \r\n"
		"5 - close \r\n"		
};
void term_cmd_esp(char *param)
{	
	terminal_newline();
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
			printf_terminal_P((PGM_P)pgm_read_word(cmd_esp_help));
	}
}

CONST command_t esp_cmd = {
  "esp", term_cmd_esp, Esp_HelpText
};

#endif

#if 0
#include "m590_at.h"

CONST char cmd_m590_help[] PROGMEM = {
	"\r\n usage:\r\n"
	"i - init \r\n"
	"o - open \r\n"
	"s - send \r\n"
	"r - receive \r\n"
	"c - close \r\n"
	"a - init, open, send \r\n"
	"e - server \r\n"
	"d - dns \r\n"
	"t - time \r\n"
};

void term_cmd_m590(char *param)
{
	char entradas[CONSOLE_BUFFER_SIZE];
	terminal_newline();
	switch (param[0])
	{
		case 'i': at_m590_init();
		break;
		case 'o': at_m590_open();
		break;
		case 's': at_m590_send(NULL);
		break;
		case 'r': at_m590_receive(entradas,SIZEARRAY(entradas));
		break;
		case 'c': at_m590_close();
		break;
		case 'a':
		at_m590_init();
		at_m590_open();
		at_m590_send(NULL);
		break;
		case 'e': at_m590_server();
		break;
		case 'd': at_m590_dns(param);
		break;
		case 't': at_m590_time();
		break;
		default:
		printf_terminal_P((PGM_P)pgm_read_word(cmd_m590_help));
	}
	param[0] = 0;
}

CONST command_t m590_cmd = {
	"m590", term_cmd_m590, m590_HelpText
};
#endif

#include "null_modem.h"

CONST char cmd_null_modem_help[] PROGMEM = {
		"\r\n usage:\r\n"
		"i - init \r\n"
		"o - open \r\n"
		"s - send \r\n"
		"r - receive \r\n"
		"c - close \r\n"
		"a - init, open, send \r\n"
		"e - server \r\n"
		"d - dns \r\n"
		"t - time \r\n"
};

void term_cmd_null_modem(char *param)
{	
	char entradas[CONSOLE_BUFFER_SIZE];
	terminal_newline();
	switch (param[0])
	{
		case 'i': at_null_modem_init();
			break;
		case 'o': at_null_modem_open();
			break;
		case 's': at_null_modem_send(NULL);
			break;
		case 'r': at_null_modem_receive(entradas,SIZEARRAY(entradas));
			break;					
		case 'c': at_null_modem_close();
			break;
		case 'a':
			at_null_modem_init();
			at_null_modem_open();
			at_null_modem_send(NULL);
			break;	
		case 'e': at_null_modem_server();
			break;			
		case 'd': at_null_modem_dns(param);
			break;	
		case 't': at_null_modem_time();
			break;	
		default:
			break;//printf_terminal_P((PGM_P)pgm_read_word(cmd_null_modem_help));
	}
	param[0] = 0;
}

CONST command_t null_modem_cmd = {
  "null_modem", term_cmd_null_modem, null_modem_HelpText
};


#include "gc864_modem.h"

#define cmd_modem_help_def      \
	"\r\n usage:\r\n"           \
	"i - init \r\n"             \
	"o - open \r\n"             \
	"s - send \r\n"             \
	"r - receive \r\n"          \
	"c - close \r\n"            \
	"a - init, open, send \r\n" \
	"e - server \r\n"           \
	"d - dns \r\n"              \
	"t - time \r\n"             \

	
char host[32];
void term_cmd_modem(char *param)
{
	char entradas[2*CONSOLE_BUFFER_SIZE];

	terminal_newline();
	switch (param[0])
	{
		case 'i': at_modem_init();
			break;
		case 'o':
		    if(sscanf(&param[2], "%s", host) == 1)
			{
		    	at_modem_open(1,host);
			}
		    break;
		case 's':
		    SNPRINTF_P(entradas,sizeof(entradas)-1,PSTR("GET / HTTP/1.1\r\nHost:%s\r\n\r\n\r\n"), host);
			at_modem_send(entradas);
			break;
		case 'r': at_modem_receive(entradas,SIZEARRAY(entradas));
			break;
		case 'c': at_modem_close();
			break;
		case 'a':
		    SNPRINTF_P(entradas,sizeof(entradas)-1,PSTR("GET / HTTP/1.1\r\nHost:%s\r\n\r\n\r\n"), host);
			at_modem_init();
			at_modem_open(1,(char*)host);
			at_modem_send(entradas);
			break;
		default:
		PRINTS_P(PSTR(cmd_modem_help_def));
		terminal_newline();
	}
	param[0] = 0;
}

CONST command_t modem_cmd = {
	"mod", term_cmd_modem, modem_HelpText
};


#if 1

#define cmd_modbus_help_def			\
	"\r\n usage:\r\n"				\
	"a - set slave address \r\n"    \
	"d - set device code \r\n"		\
	"i - read input regs \r\n"	    \
	"h - read holding regs \r\n"    \
	"p - print answer \r\n"         \
	"r - read device regs \r\n"     \
	"s - start reg address \r\n"    \
	"n - num of regs \r\n"          \

static uint16_t start_addr = 0;
static uint8_t slave_addr = 1;
static uint8_t num_regs = 1;
static uint8_t func = 3;
static uint8_t device = 0;

#include "modbus.h"
#include "modbus_slaves.h"
#include "printf_lib.h"
#include "stdio.h"

extern CONST modbus_slave_t * modbus_slaves_all[];

void term_cmd_modbus(char *param)
{	

	int input;
	uint8_t k = 0;
	uint8_t cnt = 0;
	uint16_t modbus_buf[16];
	
	terminal_newline();
	switch (param[0])
	{
		case 'a': 
				if(sscanf(&param[2], "%x", &input) == 1)
				{
					slave_addr = (uint8_t)input;
				}
				break;
		case 'd':
				if(sscanf(&param[2], "%x", &input) == 1)
				{
					if((uint8_t)input < MODBUS_NUM_SLAVES)
					{
						device = (uint8_t)input;
					}else
					{
						PRINTS_P(PSTR("Modbus erro: device not supported!"));
						terminal_newline();
					}
					
				}
				break;	
		case 's': 
			    if(sscanf(&param[2], "%d", &input) == 1)
				{
			    	start_addr = (uint16_t)input;
				}
				break;
		case 'n': 
				if(sscanf(&param[2], "%d", &input) == 1)
				{
					num_regs = (uint8_t)input;
					if(num_regs > SIZEARRAY(modbus_buf))
					{
						num_regs = SIZEARRAY(modbus_buf);
					}
				}
				break;
		case 'h': func = 3; /* read holding regs */
			break;	
		case 'i': func = 4; /* read input regs */
			break;
		case 'p': 		
			memset(modbus_buf,0x00,SIZEARRAY(modbus_buf));			
			if(Modbus_GetData(slave_addr, func, (uint8_t*)modbus_buf, start_addr, num_regs) == MODBUS_OK)
			{			
				terminal_newline();	
				for(k=0;k<num_regs;k++)
				{
					printf_lib("%04X-",modbus_buf[k]);
				}
				putchar_terminal(DEL);
				
			}else
			{
				PRINTS_P(PSTR("Modbus erro"));
				terminal_newline();
			}
			break;
		case 'r':		    
			memset(modbus_buf,0x00,SIZEARRAY(modbus_buf));
			cnt = modbus_slaves_all[device]->slave_reader(slave_addr,(uint8_t*)modbus_buf, sizeof(modbus_buf));
			if(cnt > sizeof(modbus_buf)) cnt = sizeof(modbus_buf);
			terminal_acquire();
			terminal_newline();
			for(k=0;k<cnt/2;k++)
			{
				printf_lib("%04X-",modbus_buf[k]);
			}
			putchar_terminal(DEL);
			terminal_release();
			break;
		default:
			PRINTS_P(PSTR(cmd_modbus_help_def));
			terminal_newline();
			PRINTF_P(PSTR("MB: slave %u, fun %u, "), slave_addr, func);
			PRINTF_P(PSTR("start %u, n_regs %u, "),start_addr, num_regs);
			PRINTF_P(PSTR("device %u\r\n"),device);
			break;
			
	}
	param[0] = 0;
}

CONST command_t modbus_cmd = {
  "mb", term_cmd_modbus, Modbus_HelpText
};
#endif


/* monitor status */
#include "monitor.h"
#include "simon-api.h"

#define cmd_monitor_help_def      \
	"\r\n usage:\r\n"           \
	"s - status \r\n"           \
	"r - reset monitor\r\n"     \
	"c - clear logs\r\n"        \
	"l - list \r\n"             \
	"n - null modem \r\n"       \
	"t - time \r\n"             \
	"k - sinch \r\n"            \
	"v - verbose \r\n"          \

void monitor_stop(void);

void monitor_stop(void)
{
	extern volatile uint8_t monitor_running;
	extern volatile uint8_t monitor_uploading;
	extern volatile uint8_t monitor_is_idle;
	
	OS_SR_SAVE_VAR;
	
	OSEnterCritical();
	while(1)
	{
		if(monitor_is_idle == 1)
		{
			monitor_running = 0;
			monitor_uploading = 0;
			OSExitCritical();
			return;
		}
		else
		{
			OSExitCritical();
			DelayTask(50);
		}
	}	
}

void mcu_reset(void);

void mcu_reset(void)
{
	OS_SR_SAVE_VAR;	
	OSEnterCritical();
	while(1)	
	{		
		// wait watchdog reset
	}
}

time_t str2time(const char *s);

time_t str2time(const char *s)
{
	struct tm tm;
	#define DELIM   ':'
	
	memset(&tm, 0, sizeof(tm));
	if (s) {
		tm.tm_year = atoi(s) - 1900;
		if ( (s = strchr(s, DELIM))) {
			tm.tm_mon = atoi(++s) - 1;
			if ( (s = strchr(s, DELIM))) {
				tm.tm_mday = atoi(++s);
				if ( (s = strchr(s, DELIM))) {
					tm.tm_hour = atoi(++s);
					if ( (s = strchr(s, DELIM))) {
						tm.tm_min = atoi(++s);
						if ( (s = strchr(s, DELIM))) {
							tm.tm_sec = atoi(++s);
						}
					}
				}
			}
		}
	}
	return mktime(&tm);

}

void term_cmd_monitor(char *param)
{
    uint8_t mon = 0;
    uint8_t verb = 0;
    int input;
	char timestamp[24];
	time_t time_now;
	struct tm ts_now;
	
	LOG_DIRTYPE  d;
	LOG_DIRINFO  dir;

    extern monitor_state_t monitor_state[];
    extern uint8_t mon_verbosity;
	extern uint8_t monitor_modem_null;

	terminal_newline();
	switch (param[0])
	{
		case 's':
			for (mon= 0; mon < MAX_NUM_OF_MONITORES; mon++)
			{
				if(monitor_state[mon].state == IN_USE)
				{
					PRINTS_P(PSTR("----------------------------------------------\r\n"));
					PRINTF_P(PSTR("M: %u, Cod: %u, Slave: %u, Sinc: %u \r\n"), mon,
							monitor_state[mon].codigo,
							monitor_state[mon].slave_addr,
							monitor_state[mon].sinc);
					PRINTF_P(PSTR("Config: id = %u, period = %u, entry size = %u \r\n"),
												monitor_state[mon].config_h.mon_id,
												monitor_state[mon].config_h.time_interv,
												monitor_state[mon].config_h.entry_size);
					PRINTF_P(PSTR("Avg time to send: %u\r\n"), monitor_state[mon].avg_time_to_send);
					PRINTF_P(PSTR("Total written: %lu\r\n"), monitor_state[mon].written_entries);
					PRINTF_P(PSTR("Total read: %lu\r\n"), monitor_state[mon].read_entries);
					PRINTF_P(PSTR("Total sent: %lu\r\n"), monitor_state[mon].sent_entries);
					PRINTF_P(PSTR("Sinc at: %lu\r\n"), monitor_state[mon].sinc_time);
					PRINTF_P(PSTR("Last sent at: %lu\r\n"), monitor_state[mon].last_timestamp);
				}
			}
			break;
		case 'r':	
			monitor_stop();	
			mcu_reset();		
			break;
		case 'c':  /* TODO */
			monitor_stop();	
			for (mon=0; mon < MAX_NUM_OF_MONITORES; mon++)
			{
				if(monitor_state[mon].state == IN_USE)
				{
					empty_directory(monitor_state[mon].monitor_dir_name);
				}
			}
			break;
		case 't':
			time_now = simon_clock_get();			
			ts_now = *((struct tm *)localtime(&(time_t){time_now}));	
			PRINTS_P(PSTR("\r\nTime now: "));					
			strftime(timestamp,24,"%Y:%m:%d:%H:%M:%S\r\n",&ts_now);
			PRINTF(timestamp);
			break;
		case 'k':
			 if(sscanf(&param[2], "%s", (char*)timestamp) == 1)
			 {
				 time_now = str2time(timestamp);
				 simon_clock_set(time_now);
			 }	
			 break;
		case 'l':
			for (mon=0; mon < MAX_NUM_OF_MONITORES; mon++)
			{
				if(monitor_state[mon].state == IN_USE)
				{
					 if (monitor_opendir(monitor_state[mon].monitor_dir_name, d))
					 {
						 while (monitor_readdir(dir,d))
						 {
							 #if _WIN32
								PRINTF("%s\r\n", dir->d_name);
							 #else
								PRINTF("%s\r\n", (LOG_DIRINFO*)(&dir)->fname);
							 #endif
						 }						 
						 monitor_closedir(d);
					}
				}
			}
			break;
		case 'n':								
			monitor_modem_null = 1;
			PRINTS_P(PSTR("Null modem set \r\n"));
			break;
		case 'v':
			if(sscanf(&param[2], "%d", &input) == 1)
			{
				verb = (uint8_t)input;
				if(verb > 10) verb = 10;
				mon_verbosity = verb;
			}
			PRINTF_P(PSTR("Verbose level = %u \r\n"), mon_verbosity);
			break;
		default:
			PRINTS_P(PSTR(cmd_monitor_help_def));
			terminal_newline();
	}
	param[0] = 0;
}

CONST command_t monitor_cmd = 
{
	"mon", term_cmd_monitor, monitor_HelpText
};

