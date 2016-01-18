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

#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void (cmd_func)(char *params);

/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
#define MAX_CMDS			  20
#define MAX_CMD_SIZE		  8
#define CONSOLE_BUFFER_SIZE  (64)

#ifndef CONST
#define CONST const
#endif

#ifndef INROM
#define INROM 	1
#endif

#define DEL 0x7F


typedef struct {
#if INROM
  const char *txt;
#else
  char txt[MAX_CMD_SIZE];
#endif
  cmd_func * func;
#if INROM
  const char *help_txt;
#else
  char help_txt[24];
#endif
} command_t;

int terminal_add_cmd(command_t *cmd);
int terminal_delete_cmd(command_t *cmd);
void terminal_init(void (*putch_)(char));
void terminal_process(void);
int term_skipp_space(char *cmd_line, int start);
int term_find_word(char *cmd_line, int start);
int term_cmp_str(char *a, char *b);

void SetSilentMode(char mode);
unsigned char TerminalBackup(char *backup);

void printf_terminal(const char *s);
void putchar_terminal(char c);
int getchar_terminal(char *c, int timeout);
void terminal_acquire(void);
void terminal_release(void);
void terminal_newline(void);
int is_terminal_idle(void);
void terminal_set_idle(char state);

void printf_terminal_P(const char *s);

#include "AppConfig.h"
#if COLDUINO
#define printf_terminal_P	printf_terminal
#ifndef PSTR
#define PSTR(x)				(x)
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

/****************************** END OF FILE **********************************/
