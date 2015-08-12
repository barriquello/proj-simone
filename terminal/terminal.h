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

typedef struct {
  const char *txt;
  cmd_func * func;
  const char *help_txt;
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

#if PLATAFORMA == COLDUINO
#define CONST 
#else
#define CONST const
#endif

#ifdef __cplusplus
}
#endif

#endif

/****************************** END OF FILE **********************************/
