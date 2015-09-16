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
extern void terminal_init(unsigned char (*putch_)(char));
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
