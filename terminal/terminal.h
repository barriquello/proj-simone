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
  char txt[8];
#endif
  cmd_func * func;
#if INROM
  const char *help_txt;
#else
  char help_txt[24];
#endif
} command_t;

#define CONSOLE_BUFFER_SIZE  (144)

extern int terminal_add_cmd(command_t *cmd);
extern int terminal_delete_cmd(command_t *cmd);
extern void terminal_init(void (*putch_)(char));
extern void terminal_process(void);
extern int term_skipp_space(char *cmd_line, int start);
extern int term_find_word(char *cmd_line, int start);
extern int term_cmp_str(char *a, char *b);

void SetSilentMode(char mode);
unsigned char TerminalBackup(char *backup);

extern void printf_terminal(char *s);
extern void putchar_terminal(char c);
extern void getchar_terminal(char *c);

#ifdef __cplusplus
}
#endif

#endif

/****************************** END OF FILE **********************************/
