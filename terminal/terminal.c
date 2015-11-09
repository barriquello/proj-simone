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
/****************************************************************************
 * *  Created on: 12/05/2011
 *      Author: gustavo
 ***************************************************************************/
#include "AppConfig.h"

#if COLDUINO
#include "types.h"
#include "virtual_com.h"
#if __GNUC__
#include "stdint.h"
#endif
#else
#define printf_usb(x)	
#endif

#include "BRTOS.h"
#include "terminal.h"


#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
 * Local types.
 *****************************************************************************/
/* none */

/*****************************************************************************
 * External references.
 *****************************************************************************/
/* none */

/*****************************************************************************
 * Function predefinitions.
 *****************************************************************************/
static void term_print_greeting(void);
static void term_cmd_help(char *param);
static void term_print_prompt(void);
static int  term_find_command(char *name);

#define Help_HelpText_def "Help of commands"
const char Help_HelpText_str[] PROGMEM = Help_HelpText_def;

/*****************************************************************************
 * Module variables.
 *****************************************************************************/
static const command_t term_help_cmd = {
  "help", term_cmd_help, Help_HelpText_str
};

static char			SilentMode = 0; 
static char 		term_cmd_line[CONSOLE_BUFFER_SIZE];
static uint8_t 		term_cmd_line_ndx;

static uint8_t 		term_n_cmd;
command_t 	*term_cmds[MAX_CMDS];

static void (*putch)(char);
static void (*getch)(char *);

#if ARDUINO
#include "uart.h"
void terminal_acquire(void)	
{
	uart0_acquire();
}
void terminal_release(void)
{
	uart0_release();
}
#elif COLDUINO
void terminal_acquire(void)
{

}
void terminal_release(void)
{

}
#endif

int getchar_terminal(char *c)
{    	
#if COLDUINO
	INT8U data;	
	(void)OSQueuePend(USB, &data, 0);
	*c=(char)data;
	return TRUE;
#elif ARDUINO 	
	return getchar_uart0(c, 500);		
#endif	
	
}

void putchar_terminal(char c)
{
	if(putch != NULL)
	{
		putch(c);
	}
	
}

#if ARDUINO
void printf_terminal_P(const char *s)
{
		
	char c;
		//terminal_acquire();

		while((c=pgm_read_byte(s)) != 0)
		{
			putchar_terminal(c);
			s++;
		}

		//terminal_release();	
}
#endif
/*****************************************************************************
 * Name:
 *    print
 * In:
 *    s: string
 * Out:
 *    n/a
 *
 * Description:
 *    Print the specified string.
 * Assumptions:
 *
 *****************************************************************************/
void printf_terminal(const char *s)
{
  //terminal_acquire();
  while(*s)
  {
#if 0	  
      while(*s != (char)putch(*s)){};
#else
      putchar_terminal(*s);
#endif		
      s++;
  }
  //terminal_release();
}



/*****************************************************************************
 * Name:
 *    skipp_space
 * In:
 *    cmd_line: string to parse
 *    start: start at offset
 * Out:
 *    index of first non space character
 *
 * Description:
 *
 * Assumptions:
 *
 *****************************************************************************/
int term_skipp_space(char *term_cmd_line, int start)
{
  /* Skip leading whitespace. */
  while(term_cmd_line[start] == ' ' || term_cmd_line[start] == '\t')
  {
    start++;
  }
  return(start);
}

/*****************************************************************************
 * Name:
 *    find_word
 * In:
 *    cmd_line - pointer to string to be processed
 *    start    - start offset of word
 *
 * Out:
 *    Index of end of word.
 *
 * Description:
 *    Will find the end of a word (first space, tab or end of line).
 *
 * Assumptions:
 *    --
 *****************************************************************************/
int term_find_word(char *term_cmd_line, int start)
{
  /* Find end of this word. */
  while(term_cmd_line[start] != ' ' && term_cmd_line[start] != '\t' 
        && term_cmd_line[start] != '\0')
  {
    start++;
  }

  return(start);
}

/*****************************************************************************
 * Name:
 *    cmp_str
 * In:
 *    a - pointer to string one
 *    b - pointer to string two
 * Out:
 *    0 - strings differ
 *    1 - strings are the same
 * Description:
 *    Compare two strings.
 *
 * Assumptions:
 *    --
 *****************************************************************************/
#include "string.h"
int term_cmp_str(char *a, char *b)
{
  
#if 0	
  int x=0;
  do
  {
    if (a[x] != b[x])
    { 
      return(0);
    }
    x++;
  } while(a[x] != '\0' && b[x] != '\0');

  return(a[x]==b[x] ? 1 : 0);
#else
  return ((strcmp(a,b) == 0) ? 1 : 0);
#endif  
  
}


/*****************************************************************************
* Name:
*    cmd_help
* In:
*    param - pointer to string containing parameters
*
* Out:
*    N/A
*
* Description:
*    List supported commands.
*
* Assumptions:
*    --
*****************************************************************************/
static void term_cmd_help(char *param)
{
  int x;
  int y;
  char *name;

  (void)param;
  terminal_newline();
  printf_terminal_P(PSTR("Supported commands:"));
  terminal_newline();

  for(x=0; x < term_n_cmd; x++)
  {
    putchar_terminal(' ');
    name = (char*)term_cmds[x]->txt;
    y = (int)strlen(name);
	printf_terminal((char *)name);
    for(;y<MAX_CMD_SIZE;y++)
    {
      putchar_terminal(' ');
    }
    printf_terminal_P(term_cmds[x]->help_txt);
    terminal_newline();
  }
  terminal_newline();
}


/*****************************************************************************
* Name:
*    print_prompt
* In:
*    N/A
*
* Out:
*    N/A
*
* Description:
*    Prints the prompt string.
*
* Assumptions:
*    --
*****************************************************************************/
static void term_print_prompt(void)
{
  terminal_newline();
  putchar_terminal('>');
}

/*****************************************************************************
* Name:
*    print_greeting
* In:
*    N/A
*
* Out:
*    N/A
*
* Description:
*    --
*
* Assumptions:
*    --
*****************************************************************************/
static void term_print_greeting(void)
{
	printf_terminal_P(PSTR("Digite um comando:"));
	terminal_newline();
}

/*****************************************************************************
* Name:
*    find_command
* In:
*    name - pointer to command name string
*
* Out:
*    number - Index of command in "commands" array.
*    -1     - Command not found.
*
* Description:
*    Find a command by its name.
*
* Assumptions:
*    --
*****************************************************************************/
static int term_find_command(char *name)
{
  int x;
  for(x=0; x < term_n_cmd; x++)
  { /* If command found, execute it. */
    if (term_cmp_str(name, (char *) term_cmds[x]->txt))
    {
      return(x);
    }
  }
  return(-1);
}


/*****************************************************************************
* Name:
*    terminal_init
* In:
*    N/A
*
* Out:
*    N/A
*
* Description:
*    Initialise the terminal. Set local variables to a default value, print
*    greeting message and prompt.
*
* Assumptions:
*    --
*****************************************************************************/
void terminal_init(void (*putch_)(char))
{
  term_cmd_line[0]='\0';
  //memset(term_cmd_line,0x00,sizeof(term_cmd_line));
  //term_cmd_line[sizeof(term_cmd_line)-1]='\0';
  term_cmd_line_ndx=0;

  term_cmds[0]=(void *)&term_help_cmd;
  term_n_cmd=1;
  
  putch=putch_;

 //print_greeting();
  term_print_prompt();
}

/*****************************************************************************
* Name:
*    terminal_proces
* In:
*    N/A
*
* Out:
*    N/A
*
* Description:
*    Main loop of terminal application. gathers input, and executes commands.
*
* Assumptions:
*    --
*****************************************************************************/
void terminal_process(void)
{
  char c;
  static char skip_mode = 0;
  
  while(1)
  {
	
	terminal_acquire();
	
	if(getchar_terminal(&c) == FALSE)
	{		
		terminal_release();
		DelayTask(1000);
	}

	if (SilentMode == FALSE)
	{
	  if(c !='\n' && c!='\r')
	  {
		  if(c != DEL || term_cmd_line_ndx)
		  {			  
			  //terminal_acquire();
			  putchar_terminal(c);
			  //terminal_release();
		  }			  
	  }
	} 
        
    
    /* Execute command if enter is received, or term_cmd_line is full. */
    if ((c=='\r') || (term_cmd_line_ndx == sizeof(term_cmd_line)-2))
    {
      int term_start = term_skipp_space(term_cmd_line, 0);
      int term_end = term_find_word(term_cmd_line, term_start);
      int term_x;

      /* Separate command string from parameters, and close
         parameters string. */
      term_cmd_line[term_end]=term_cmd_line[term_cmd_line_ndx]='\0';

      if(term_end == 0) goto exit;
      
      /* Identify command. */
      term_x=term_find_command(term_cmd_line+term_start);
      
      /* Command not found. */
      if (term_x == -1)
      {    	
		terminal_newline();
    	printf_terminal_P(PSTR("Unknown command!"));
		terminal_newline();
      }
      else
      {
		//terminal_acquire();
		(*term_cmds[term_x]->func)(term_cmd_line+term_end+1);		
      }
      exit:
      term_cmd_line_ndx=0;
      term_print_prompt();      
      SetSilentMode((char)FALSE);
	  
	  terminal_release();
    }
    else
    { /* Put character to term_cmd_line. */
      if (c=='\b')
      {
        if (term_cmd_line_ndx > 0)
        {
          term_cmd_line[term_cmd_line_ndx]='\0';
          term_cmd_line_ndx--;
        }
      }
#if 1      
      else if(c=='\n'){
        continue;
      }
#endif      
      else
      {
          if (c == DEL)
          {    	  
              if (term_cmd_line_ndx)
              {
                  term_cmd_line[term_cmd_line_ndx]=0;
				  term_cmd_line_ndx--;
				  term_cmd_line[term_cmd_line_ndx]=0; 
              }
          }else
          {
              term_cmd_line[term_cmd_line_ndx++]=c;             
          }
      }
    }    
    #if COLDUINO
    if (SilentMode == FALSE)
    {
    	cdc_process();
    }
	#endif
  }
}

void SetSilentMode(char mode)
{
	if ((mode == TRUE) || (mode == FALSE))
	{
		SilentMode = mode;
	}
}


unsigned char TerminalBackup(char *backup)
{
	unsigned char i = 0;
	
	for(i=0;i<term_cmd_line_ndx;i++)
	{
		*backup++ = term_cmd_line[i];
		if (i >= ((CONSOLE_BUFFER_SIZE/2)-1)) break;
	}
	
	term_cmd_line_ndx = 0;
	
	return i;
}

/*****************************************************************************
* Name:
*    terminal_add_cmd
* In:
*    N/A
*
* Out:
*    N/A
*
* Description:
*    Main loop of terminal application. gathers input, and executes commands.
*
* Assumptions:
*    --
*****************************************************************************/
int terminal_add_cmd(command_t *cmd)
{
  if (term_n_cmd >= MAX_CMDS)
  {
    return(1);
  }

  term_cmds[term_n_cmd]=cmd;
  term_n_cmd++;
  return(0);
}

/*****************************************************************************
* Name:
*    terminal_delete_cmd
* In:
*    N/A
*
* Out:
*    N/A
*
* Description:
*    Main loop of terminal application. gathers input, and executes commands.
*
* Assumptions:
*    --
*****************************************************************************/
int terminal_delete_cmd(command_t *cmd)
{
  int x;

  for(x=0; x<term_n_cmd; x++)
  {
    if (term_cmds[x] == cmd)
    {
      while(x<term_n_cmd-1)
      {
        term_cmds[x]=term_cmds[x+1];
        x++;
      }

      term_cmds[x]=0;
      term_n_cmd--;
      
      return(0);
    }
  }
  return(1);
}

#ifdef __cplusplus
}
#endif
/****************************** END OF FILE **********************************/
