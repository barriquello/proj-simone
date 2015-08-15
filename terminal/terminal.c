/****************************************************************************
 * *  Created on: 12/05/2011
 *      Author: gustavo
 ***************************************************************************/
#include "types.h"
#include "terminal.h"
#include "virtual_com.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
#define MAX_CMDS      22
#define MAX_CMD_SIZE  8
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

/*****************************************************************************
 * Module variables.
 *****************************************************************************/
static CONST command_t term_help_cmd = {
  "help", term_cmd_help, "Help of commands"
};

static char			SilentMode = 0; 
static char 		term_cmd_line[256];
static uint_8 		term_cmd_line_ndx;

static uint_8 		term_n_cmd;
static command_t 	*term_cmds[MAX_CMDS];

static unsigned char (*putch)(char);


void putchar_terminal(char c)
{
    while(c != (char)putch(c)){};
}


void getchar_terminal(char *c)
{    
	INT8U data;
	(void)OSQueuePend(USB, &data, 0);
	*c=(char)data;
}
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
void printf_terminal(char *s)
{
  while(*s)
  {
      while(*s != (char)putch(*s)){};
      s++;
  }
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
int term_cmp_str(char *a, char *b)
{
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
  printf_usb("\r\nI understand the following commands:\r\n");

  for(x=0; x < term_n_cmd; x++)
  {
    printf_usb("  ");
    name = (char*)term_cmds[x]->txt;
    y = 0;
    while(*name)
    {
      y++;
      name++;
    }
    printf_usb((char *)term_cmds[x]->txt);
    for(y;y<MAX_CMD_SIZE;y++)
    {
      printf_usb(" ");
    }
    printf_usb((char *)term_cmds[x]->help_txt);
    printf_usb("\r\n");
  }
  printf_usb("\r\n");
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
  printf_terminal("\r\n>");
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
	printf_terminal("CDC Virtual Comm Demo.\r\n");
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
*    Inicialise the terminal. Set local varaibles to a default value, print
*    greeting message and prompt.
*
* Assumptions:
*    --
*****************************************************************************/
void terminal_init(unsigned char (*putch_)(char))
{
  term_cmd_line[sizeof(term_cmd_line)-1]='\0';
  term_cmd_line_ndx=0;

  term_cmds[0]=(void *)&term_help_cmd;
  term_n_cmd=1;
  
  putch=putch_;

 //print_greeting();
 //term_print_prompt();
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
	
	getchar_terminal(&c);
#if 0	
    switch(c)
    {
    	case '\n':
    		break;
    	case '\r':
    		break;
    	case 0x7F: //DEL
    		if (term_cmd_line_ndx)
			{
			  while(c!=(char)(*putch)(c)){};
			}
    		break;  		
    	default:
      	  if (SilentMode == FALSE)
      	  {
      		  while(c!=(char)(*putch)(c)){};
      	  }    		
    }
#else
	  if (SilentMode == FALSE)
	  {
		  if(c !='\n' && c!='\r')
		  {
			  if(c != 0x7F || term_cmd_line_ndx) //DEL
			  {
				  while(c!=(char)(*putch)(c)){};
			  }			  
		  }
	  } 
    
#endif
        
    
    /* Execute command if enter is received, or term_cmd_line is full. */
    if ((c=='\r') || (term_cmd_line_ndx == sizeof(term_cmd_line)-2))
    {
      int term_start = term_skipp_space(term_cmd_line, 0);
      int term_end = term_find_word(term_cmd_line, term_start);
      int term_x;

      /* Separate command string from parameters, and close
         parameters string. */
      term_cmd_line[term_end]=term_cmd_line[term_cmd_line_ndx]='\0';

      /* Identify command. */
      term_x=term_find_command(term_cmd_line+term_start);
      
      /* Command not found. */
      if (term_x == -1)
      {
        printf_terminal("\r\nUnknown command!\r\n");
      }
      else
      {
        (*term_cmds[term_x]->func)(term_cmd_line+term_end+1);
      }
      term_cmd_line_ndx=0;
      term_print_prompt();      
      SetSilentMode((char)FALSE);
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
          if (c == 0x7F)
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
    
    if (SilentMode == FALSE)
    {
    	cdc_process();
    }
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
