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
 * terminal_commands.h
 *
 *  Created on: 12/05/2011
 *      Author: gustavo
 */

#ifndef _TERMINAL_COMMANDS_H_
#define _TERMINAL_COMMANDS_H_

#include "terminal.h"

// BRTOS version Command
void term_cmd_ver(char *param);
extern CONST command_t ver_cmd;

// TOP Command (similar to the linux command)
void term_cmd_top(char *param);
extern CONST command_t top_cmd;

// Reason of Reset Command
void term_cmd_rst(char *param);
extern CONST command_t rst_cmd;

// File Read Command
void term_cmd_cat(char *param);
extern CONST command_t cat_cmd;

// List Files Command
void term_cmd_ls(char *param);
extern CONST command_t ls_cmd;

// Change Dir Command
void term_cmd_cd(char *param);
extern CONST command_t cd_cmd;

// Mount File System Command
void term_cmd_mount(char *param);
extern CONST command_t mount_cmd;

// Safely unmount File System Command
void term_cmd_sr(char *param);
extern CONST command_t sr_cmd;

// File Delete Command
void term_cmd_rm(char *param);
extern CONST command_t rm_cmd;

// File Rename Command
void term_cmd_rn(char *param);
extern CONST command_t rn_cmd;

// File Create Command
void term_cmd_cr(char *param);
extern CONST command_t cr_cmd;

// Make Dir Command
void term_cmd_mkdir(char *param);
extern CONST command_t mkdir_cmd;

// Copy File Command
void term_cmd_cp(char *param);
extern CONST command_t cp_cmd;

// Write File Test Command
void term_cmd_wt(char *param);
extern CONST command_t wt_cmd;

// Print a string in the terminal
void term_cmd_echo(char *param);
extern CONST command_t echo_cmd;
void echo (char *string, char Terminalbackup);

// Set stdout terminal
void term_cmd_echo_out(char *param);
extern CONST command_t echo_stdout_cmd;

// Core temperature Command
void term_cmd_temp(char *param);
extern CONST command_t temp_cmd;

// Set/get time command
void term_cmd_setget_time(char *param);
extern CONST command_t setget_time_cmd;

// D/A converter sin wave Command
void term_cmd_sin2da(char *param);
extern CONST command_t sin2da_cmd;

// Control esp
void term_cmd_esp(char *param);
extern CONST command_t esp_cmd;

// Control null_modem
void term_cmd_null_modem(char *param);
extern CONST command_t null_modem_cmd;

// Control m590 modem
void term_cmd_m590(char *param);
extern CONST command_t m590_cmd;

// Control null_modem
void term_cmd_modem(char *param);
extern CONST command_t modem_cmd;

// Modbus master
void term_cmd_modbus(char *param);
extern CONST command_t modbus_cmd;

// Monitor control
void term_cmd_monitor(char *param);
extern CONST command_t monitor_cmd;

#endif /* _TERMINAL_COMMANDS_H_ */
