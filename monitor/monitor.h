/*
 * logger.h
 *
 *  Created on: 15/04/2015
 *      Author: Universidade Federal
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

#define LOG_DIRTYPE                   DIR*
#define LOG_DIRINFO 				  struct dirent *
#define LOG_FILEINFO 				  struct stat
#define monitor_stat(filename, fileinfo)  (stat((filename), (fileinfo)) == -1)
#define monitor_opendir(dirname,dir)	  (((dir) = opendir(dirname)) != NULL)
#define monitor_closedir(dir)			  closedir(dir)
#define monitor_readdir(dirinfo,dir)  	  (((dirinfo) = readdir(dir)) != NULL)
#define monitor_chdir(dirname)			  chdir(dirname)
#define monitor_mkdir(dirname)			  _mkdir(dirname)
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

#define LOG_FILETYPE    			   FIL
#define monitor_openread(filename,file)   (f_open((file), (filename), FA_READ+FA_OPEN_EXISTING) == FR_OK)
#define monitor_openwrite(filename,file)  (f_open((file), (filename), FA_WRITE+FA_CREATE_ALWAYS) == FR_OK)
#define monitor_openappend(filename,file) (f_open((file), (filename), FA_WRITE) == FR_OK)
#define monitor_close(file)               (f_close(file) == FR_OK)
#define monitor_read(buffer,size,file)    f_gets((buffer), (size),(file))
#define monitor_write(buffer,file)        f_puts((buffer), (file))
#define monitor_remove(filename)          (f_unlink(filename) == FR_OK)

#define LOG_FILEPOS                   DWORD
#define monitor_tell(file,pos)            (*(pos) = f_tell((file)))
#define monitor_seek(file,pos)            (f_lseek((file), *(pos)) == FR_OK)

#include "string.h"
static int monitor_rename(TCHAR *source, const TCHAR *dest)
{
  /* Function f_rename() does not allow drive letters in the destination file */
  const char *drive = strchr(dest, ':');
  drive = (drive == NULL) ? dest : drive + 1;
  return (f_rename(source, drive) == FR_OK);
}

#define LOG_DIRTYPE                   DIR
#define LOG_DIRINFO 				  FILINFO
#define LOG_FILEINFO 				  FILINFO
#define monitor_stat(filename, fileinfo)  (f_stat((filename), (fileinfo)) == FR_OK)
#define monitor_opendir(dirname,dir)	  (f_opendir(&(dir),dirname) == FR_OK)
#define monitor_closedir(dir)			  f_closedir(&(dir))
#define monitor_readdir(dirinfo,dir)  	  (f_readdir(&(dir), &(dirinfo)) == FR_OK)
#define monitor_chdir(dirname)			  f_chdir(dirname)
#define monitor_mkdir(dirname)			  f_mkdir(dirname)

#endif



#ifndef NULL
#define NULL  (void*)0
#endif

void	print_erro(char *format, ...);

#define LOG_HEADER_LEN		 50
#define LOG_MAX_ENTRY_SIZE   256
#define FILENAME_MAX_LENGTH  13
#define LOG_FILENAME_START   "99123123.txt"
#define LOG_METAFILE   		 ".0.txt"
#define MAX_NUM_OF_ENTRIES   ((uint32_t)(-1))
#define MAX_NUM_OF_MONITORES 3
#define NUM_OF_FIELDS        4

//#define LOG_DIR_NAME 		 "./logs"
//#define TIME_INTERVAL 		 5
//#define ENTRY_SIZE_B  		 12

/* type verification code */
static union
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

#ifndef _WIN32
typedef unsigned long long clock_t;
#endif

typedef struct timer 
{ 
	clock_t start;
	clock_t interval; 
}mon_timer_t;
static clock_t  timer_expired(mon_timer_t *t);
static void timer_set(mon_timer_t *t, int usecs);

typedef struct pt pt_t;

typedef uint8_t (*data_reader)(uint8_t* buf, uint8_t max_len);

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
	char tipo;
	uint8_t codigo;
	data_reader read_data;
}monitor_state_t;

typedef union
{
	uint8_t byte;
	struct{
		uint8_t num_mon_ok	:1;	/* num. de monitores ok */
		uint8_t server_ok	:1;	/* server ok */
		uint8_t	key_ok		:1;	/* Api Key ok */
		uint8_t	gprs_apn_ok :1;	/* GPRS access point ok */
		uint8_t	gprs_user_ok:1 ;/* GPRS user ok */
		uint8_t	gprs_pwd_ok :1 ;/* GPRS password ok */
		uint8_t unused3:1 ; /* Unused */
	}bit;
}monitor_config_ok_t;

void test_logger(void);

uint8_t monitor_init(uint8_t monitor_num);
void monitor_sync(char*);

void monitor_makeheader(char monitor_header[], monitor_header_t * h);
void monitor_setheader(char* filename, monitor_header_t * h);
void monitor_getheader(char* filename, monitor_header_t * h);
void monitor_newheader(char* filename, uint8_t monitor_id, uint16_t interval, uint16_t entry_size);

void monitor_createentry(char* string, uint16_t *dados, uint16_t len);
uint16_t monitor_writeentry(char* filename, char* entry);
uint32_t monitor_readentry(uint8_t monitor_num, char* filename, monitor_entry_t* entry);

void monitor_gettimestamp(struct tm * ts, uint32_t time_elapsed_s);
void monitor_settimestamp(uint8_t monitor_num, char* filename);

char* monitor_getfilename_to_write(uint8_t monitor_num);
char* monitor_getfilename_to_read(uint8_t monitor_num);

void main_monitor(void);
void monitor_reader(uint8_t monitor_num);
void monitor_writer(uint8_t monitor_num);

#endif /* LOGGER_H_ */
