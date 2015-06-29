/*
 * usb_terminal_commands.h
 *
 *  Created on: 12/05/2011
 *      Author: gustavo
 */

#ifndef USB_TERMINAL_COMMANDS_H_
#define USB_TERMINAL_COMMANDS_H_

#include "usb_terminal.h"
//#include "sound_driver.h"


// BRTOS version Command
void usb_cmd_ver(char *param);
extern const command_t usb_ver_cmd;

// TOP Command (similar to the linux command)
void usb_cmd_top(char *param);
extern const command_t usb_top_cmd;

// Reason of Reset Command
void usb_cmd_rst(char *param);
extern const command_t usb_rst_cmd;

// SD Card Read Command
void cmd_cat(char *param);
extern const command_t cat_cmd;

// SD Card List Files Command
void cmd_ls(char *param);
extern const command_t ls_cmd;

// SD Card Change Dir Command
void cmd_cd(char *param);
extern const command_t cd_cmd;

// Mount SD Card Command
void cmd_mount(char *param);
extern const command_t mount_cmd;

// Safely remove SD Card Command
void cmd_sr(char *param);
extern const command_t sr_cmd;

// SD Card Delete Command
void cmd_rm(char *param);
extern const command_t rm_cmd;

// SD Card Rename Command
void cmd_rn(char *param);
extern const command_t rn_cmd;

// SD Card Create File Command
void cmd_cr(char *param);
extern const command_t cr_cmd;

// SD Card Make Dir Command
void cmd_mkdir(char *param);
extern const command_t mkdir_cmd;

// SD Card Copy File Command
void cmd_cp(char *param);
extern const command_t cp_cmd;

// SD Card Write File Test Command
void cmd_wt(char *param);
extern const command_t wt_cmd;

// Print a string in the terminal
void cmd_echo(char *param);
extern const command_t echo_cmd;
void echo (char *string, char Terminalbackup);

// Set stdout terminal
void cmd_echo_out(char *param);
extern const command_t echo_stdout_cmd;

// Core temperature Command
void usb_cmd_temp(char *param);
extern const command_t usb_temp_cmd;

// Set/get time command
void cmd_setget_time(char *param);
extern const command_t setget_time_cmd;

// D/A converter sin wave Command
void cmd_sin2da(char *param);
extern const command_t sin2da_cmd;

// Control esp
void cmd_esp(char *param);
extern const command_t esp_cmd;

#if (SD_WAVE == 1)
	extern CHAR8 SoundName[(CONSOLE_BUFFER_SIZE/2)];
	
	// Play Wave sound from SD Card Command
	void cmd_play(char *param);
	extern const command_t play_cmd;
	
	/*----------------------------------------------------------------------*/
	/* Pause a playing Wave sound from SD Card Command						*/
	/*----------------------------------------------------------------------*/
	void cmd_pause(char *param);
	extern const command_t pause_cmd;
	
	/*----------------------------------------------------------------------*/
	/* Stop a playing Wave sound from SD Card Command						*/
	/*----------------------------------------------------------------------*/
	void cmd_stop(char *param);
	extern const command_t stop_cmd;
	
	void cmd_vol(char *param);
	extern const command_t vol_cmd;
	
	void cmd_play_LCD(char *param);
	void cmd_stop_LCD(void);		
	
#endif



#endif /* USB_TERMINAL_COMMANDS_H_ */
