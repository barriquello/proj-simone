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

extern int terminal_add_cmd(command_t *cmd);
extern int terminal_delete_cmd(command_t *cmd);
extern void terminal_init(void);
extern void terminal_process(void);
extern int skipp_space(char *cmd_line, int start);
extern int find_word(char *cmd_line, int start);
extern int cmp_str(char *a, char *b);

#ifdef __cplusplus
}
#endif

#endif

/****************************** END OF FILE **********************************/
