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
 * logger.h
 *
 *  Created on: 15/04/2015
 *      Author: UFSM
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include "stdlib.h"
#include "stdint.h"
#include "pt.h"

#ifdef _WIN32
#include <stdio.h>
#endif

#ifndef _WIN32
#include "time_lib.h"
#include "printf_lib.h"
#define  puts(x)		printf_lib(x)
#else
#include "time.h"
#endif

#ifndef NULL
#define NULL  (void*)0
#endif

#if _WIN32
#include <dirent.h>
#define LOG_FILETYPE                  	  FILE*
#define monitor_openread(filename,file)   ((*(file) = fopen((filename),"rb+")) != NULL)
#define monitor_openwrite(filename,file)  ((*(file) = fopen((filename),"wb")) != NULL)
#define monitor_openappend(filename,file)  ((*(file) = fopen((filename),"ab+")) != NULL)
#define monitor_close(file)               (fclose(*(file)) == 0)
#define monitor_read(buffer,size,file)    (fgets((char*)(buffer),(size),*(file)) != NULL)
#define monitor_write(buffer,file)        (fputs((char*)(buffer),*(file)) >= 0)
#define monitor_rename(source,dest)       (rename((source), (dest)) == 0)
#define monitor_remove(filename)          (remove(filename) == 0)

#define LOG_FILEPOS                   fpos_t
#define monitor_tell(file,pos)            ((*(pos) = ftell(*(file))) != (-1L)) //(fgetpos(*(file), (pos)) == 0)
#define monitor_seek(file,pos)            (fseek(*(file), *(pos), SEEK_SET) == 0) // (fsetpos(*(file), (pos)) == 0)
#define monitor_seek_end(file)            (fseek(*(file), 0, SEEK_END) == 0) // (fsetpos(*(file), (pos)) == 0)
#define monitor_seek_begin(file)          (fseek(*(file), 0, SEEK_SET) == 0) // (fsetpos(*(file), (pos)) == 0)

#define LOG_DIRTYPE                   DIR*
#define LOG_DIRINFO 				  struct dirent *
#define LOG_FILEINFO 				  struct stat
#define monitor_stat(filename, fileinfo)  (stat((filename), (fileinfo)) == 0)
#define monitor_opendir(dirname,dir)	  (((dir) = opendir(dirname)) != NULL)
#define monitor_closedir(dir)			  closedir(dir)
#define monitor_readdir(dirinfo,dir)  	  (((dirinfo) = readdir(dir)) != NULL)
#define monitor_chdir(dirname)			  chdir(dirname)
#define monitor_mkdir(dirname)			  (_mkdir(dirname) == 0)
#endif

#if _WIN32
#define FATFS_ENABLE 0
#else
#define FATFS_ENABLE 1
#endif

#if FATFS_ENABLE
#define LOG_BUFFERSIZE  256       /* maximum line length, maximum path length */

/* You must set _USE_STRFUNC to 1 or 2 in the include file ff.h (or tff.h)
 * to enable the "string functions" fgets() and fputs().
 */
#include "ff.h"                   /* include tff.h for FatFs */

#define LOG_FILETYPE    			  	  FIL
#define monitor_openread(filename,file)   (f_open((file), (filename), FA_READ+FA_OPEN_EXISTING) == FR_OK)
#define monitor_openwrite(filename,file)  (f_open((file), (filename), FA_WRITE+FA_CREATE_ALWAYS) == FR_OK)
#define monitor_openappend(filename,file) (f_open((file), (filename), FA_WRITE) == FR_OK)
#define monitor_close(file)               (f_close(file) == FR_OK)
#define monitor_read(buffer,size,file)    f_gets((buffer), (size),(file))
#define monitor_write(buffer,file)        (f_puts((buffer), (file)) != EOF)
#define monitor_remove(filename)          (f_unlink(filename) == FR_OK)

#define LOG_FILEPOS                   	  DWORD
#define monitor_tell(file,pos)            (*(pos) = f_tell((file)))
#define monitor_seek(file,pos)            (f_lseek((file), *(pos)) == FR_OK)
#define monitor_seek_end(file)            (f_lseek((file), f_size((file))) == FR_OK)

#define LOG_DIRTYPE						  DIR
#define LOG_DIRINFO 					  FILINFO
#define LOG_FILEINFO 					  FILINFO
#define monitor_stat(filename, fileinfo)  (f_stat((filename), (fileinfo)) == FR_OK)
#define monitor_opendir(dirname,dir)	  (f_opendir(&(dir),dirname) == FR_OK)
#define monitor_closedir(dir)			  f_closedir(&(dir))
#define monitor_readdir(dirinfo,dir)  	  (f_readdir(&(dir), &(dirinfo)) == FR_OK)
#define monitor_chdir(dirname)			  f_chdir(dirname)
#define monitor_mkdir(dirname)			  (f_mkdir(dirname) == FR_OK)

#endif

#ifndef NULL
#define NULL  (void*)0
#endif

#define LOG_HEADER_LEN		 50
#define LOG_MAX_ENTRY_SIZE   256
#define FILENAME_MAX_LENGTH  13
#define LOG_FILENAME_START   "99123123.txt"
#define LOG_METAFILE   		 "metafile.txt"
#define MAX_NUM_OF_ENTRIES   (2880) //(56400) // equivalente a 20 dias, max. 16 bits
#define MAX_NUM_OF_MONITORES 4
#define NUM_OF_FIELDS        5

/* type verification code */
union
{
    char            int8_t_incorrect[sizeof( int8_t ) == 1];
    char            uint8_t_incorrect[sizeof( uint8_t ) == 1];
    char            int16_t_incorrect[sizeof( int16_t ) == 2];
    char            uint16_t_incorrect[sizeof( uint16_t ) == 2];
    char            int32_t_incorrect[sizeof( int32_t ) == 4];
    char            uint32_t_incorrect[sizeof( uint32_t ) == 4];
}u;

typedef struct
{
	uint16_t year;	/* Years since 0000 */
	uint8_t mon;	/* Months *since* january: 0-11 */
	uint8_t	mday;	/* Day of the month: 1-31 */
	uint8_t	hour;	/* Hours since midnight: 0-23 */
	uint8_t	min;	/* Minutes: 0-59 */
	uint8_t	sec;	/* Seconds: 0-59 */
}timestamp_t;

typedef struct
{
	time_t ts; /* entry timestamp - unix time */
	uint8_t size; /* size of entry in number of bytes, must be not greater than LOG_MAX_ENTRY_SIZE */
	uint8_t *values; /* pointer to 8-bit entry values */
}monitor_entry_t;

typedef struct
{
	uint8_t version;
	uint8_t mon_id;
	uint16_t entry_size;
	uint16_t time_interv;
}monitor_headerl1_t;

typedef struct
{
	uint16_t year;	/* Years since 0000 */
	uint8_t mon;	/* Months *since* january: 0-11 */
	uint8_t	mday;	/* Day of the month: 1-31 */
	uint8_t	hour;	/* Hours since midnight: 0-23 */
	uint8_t	min;	/* Minutes: 0-59 */
	uint8_t	sec;	/* Seconds: 0-59 */
	uint8_t synched; /* synch flag: (1) TRUE (0) FALSE */
}monitor_headerl2_t;

typedef struct
{
	monitor_headerl1_t h1; /* version, id, entry size and time interval */
	monitor_headerl2_t h2; /* timestamp and synch flag */
	uint16_t last_idx;	/* index of last sent line */
	uint16_t count;		/* entries count */
}monitor_header_t;

typedef enum{
	UNUSED = 0,
	IN_USE = 1
} monitor_used_t;

#if (COLDUINO && !__GNUC__)
typedef unsigned long long clock_t;
#elif ARDUINO
typedef unsigned long long clock_t;
#endif

typedef struct timer 
{ 
	clock_t start;
	clock_t interval; 
}mon_timer_t;

typedef struct pt pt_t;

typedef uint8_t (*data_reader)(uint8_t slave_addr, uint8_t* buf, uint8_t max_len);

typedef struct
{
	monitor_used_t state;
	char  monitor_name_writing[FILENAME_MAX_LENGTH];
	char  monitor_name_reading[FILENAME_MAX_LENGTH];
	char  monitor_dir_name[FILENAME_MAX_LENGTH];
	monitor_headerl1_t config_h;
	mon_timer_t read_timer;
	mon_timer_t write_timer;	
	pt_t read_pt;
	pt_t write_pt;
	uint8_t slave_addr;
	uint8_t codigo;
	uint8_t sinc;
	uint8_t sending;
	uint8_t uploading;
	data_reader read_data;
	uint32_t written_entries;
	uint32_t total_written_entries;
	uint32_t read_entries;
	uint32_t sent_entries;
	uint32_t failed_tx;
	time_t last_timestamp;
	time_t sinc_time;
	uint32_t tx_start;
	uint32_t tx_time;
	uint32_t tx_time_avg;
	clock_t reader_upload_start_time;
	uint32_t reader_upload_time;
	uint32_t reader_upload_time_avg;
}monitor_state_t;

typedef struct
{
	time_t time_started;
	uint8_t monitores_em_uso;
	uint8_t is_idle;
	uint8_t uploading;
	uint8_t running;	
	uint8_t is_connected;
}monitors_state_t;

typedef union
{
	uint8_t byte;
	struct{
		uint8_t num_mon_ok	:1;	/* num. de monitores ok */
		uint8_t server_ok	:1;	/* server ok */
		uint8_t ip_ok	    :1;	/* server ip ok */
		uint8_t	key_ok		:1;	/* Api Key ok */
		uint8_t	gprs_apn_ok :1;	/* GPRS access point ok */
		uint8_t	gprs_user_ok:1 ;/* GPRS user ok */
		uint8_t	gprs_pwd_ok :1 ;/* GPRS password ok */
	}bit;
}monitor_config_ok_t;

void test_logger(void);

uint8_t monitor_init(uint8_t monitor_num);
void monitor_sync(uint8_t monitor_num, const char*);

void monitor_makeheader(char monitor_header[], monitor_header_t * h);
uint8_t monitor_setheader(const char* filename, monitor_header_t * h);
uint8_t monitor_getheader(const char* filename, monitor_header_t * h);
uint8_t monitor_newheader(const char* filename, uint8_t monitor_id, uint16_t interval, uint16_t entry_size);
uint8_t monitor_validateheader(const char* filename, uint8_t monitor_id, uint16_t interval, uint16_t entry_size);

void monitor_createentry(char* string, uint16_t *dados, uint8_t len);
uint16_t monitor_writeentry(const char* filename, char* entry, uint8_t monitor_num);
uint32_t monitor_readentry(uint8_t monitor_num, const char* filename, monitor_entry_t* entry, uint8_t enable_send, uint8_t send_ok);

uint8_t monitor_gettimestamp(struct tm * ts, uint32_t time_elapsed_s);
void monitor_settimestamp(uint8_t monitor_num, const char* filename);

char* monitor_getfilename_to_write(uint8_t monitor_num);
char* monitor_getfilename_to_read(uint8_t monitor_num);

void main_monitor(void);
uint16_t monitor_reader(uint8_t monitor_num);
void monitor_writer(uint8_t monitor_num);
uint16_t monitor_reader_multiple(uint8_t monitor_num);

clock_t clock_time(void);

#endif /* LOGGER_H_ */

