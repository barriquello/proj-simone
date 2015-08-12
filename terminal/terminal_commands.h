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

// Control m590
void term_cmd_m590(char *param);
extern CONST command_t m590_cmd;

#endif /* _TERMINAL_COMMANDS_H_ */
