/****************************************************************************
 * *  Created on: 12/05/2011
 *      Author: gustavo
***************************************************************************/


#ifndef _USB_TERMINAL_H_
#define _USB_TERMINAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "terminal.h"
	
#define CONSOLE_BUFFER_SIZE  (144)

int usb_skipp_space(char *usb_cmd_line, int start);
int usb_find_word(char *usb_cmd_line, int start);
int usb_cmp_str(char *a, char *b);
extern int usb_terminal_add_cmd(command_t *cmd);
extern int usb_terminal_delete_cmd(command_t *cmd);
extern void usb_terminal_init(unsigned char (*putch_)(char));
extern void usb_terminal_process(void);
extern void printf_usb(char *s);
extern void putchar_usb(char c);

void SetSilentMode(char mode);
unsigned char TerminalBackup(char *backup);

#ifdef __cplusplus
}
#endif
#endif

/****************************** END OF FILE **********************************/
