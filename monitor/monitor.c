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
 * monitor.c
 *
 *  Created on: 15/04/2015
 *      Author: UFSM
 */

#include "monitor.h"
#include "utils.h"
#include "assert.h"
#include "simon-api.h"
#include "printf_lib.h"

#ifdef _WIN32
#include "stdio.h"
#include "http_client.h"
#else
#include "AppConfig.h"
#endif

#define DEBUG_MONITOR		1
#undef PRINTS_ENABLED

#if DEBUG_MONITOR
#define PRINTS_ENABLED  1
char BufferText[32];
#else
#define PRINTS_ENABLED  0
#endif
#include "prints_def.h"

#define MONITOR_TESTS	0
#define ASSERT(x)	//assert

extern monitor_state_t monitor_state[MAX_NUM_OF_MONITORES];
extern uint8_t mon_verbosity;
extern volatile uint8_t monitor_is_connected;

#define LOG_MAX_DATA_BUF_SIZE  (LOG_MAX_ENTRY_SIZE/2)
uint16_t monitor_data_buffer[LOG_MAX_DATA_BUF_SIZE];
char monitor_char_buffer[LOG_MAX_ENTRY_SIZE + 1];

char data_vector[LOG_MAX_ENTRY_SIZE*3];
char monitor_header[LOG_HEADER_LEN+2];

#define CONST const

#include "modbus_slaves.h"
extern CONST modbus_slave_t slave_NULL;
extern CONST modbus_slave_t slave_PM210;
extern CONST modbus_slave_t slave_TS;
extern CONST modbus_slave_t slave_T500;

CONST modbus_slave_t * modbus_slaves_all[MODBUS_NUM_SLAVES] =
{
		&slave_NULL,
		&slave_PM210,
		&slave_TS,	
		&slave_T500,
};

#if FATFS_ENABLE
#include "string.h"
static int monitor_rename(TCHAR *source, const TCHAR *dest)
{
	/* Function f_rename() does not allow drive letters in the destination file */
	const char *drive = strchr(dest, ':');
	drive = (drive == NULL) ? dest : drive + 1;
	return (f_rename(source, drive) == FR_OK);
}
#endif

void monitor_createentry(char* const ptr_buffer, uint16_t * const ptr_dados, uint8_t length)
{

	uint16_t dado = 0;
	uint16_t * dados = ptr_dados;
	char* buffer = ptr_buffer;
	uint16_t len = length;	
	do
	{
		dado=*dados;
		int2hex(buffer,dado);
		buffer+=4;
		dados++;
		len--; 
	}while(len > 0);
	
	*buffer++='\r';
	*buffer++='\n';
	*buffer++='\0';
}

void monitor_makeheader(char monitor_header[], monitor_header_t * h)
{

   monitor_header[0] = 'V'; // versão
   byte2hex(&monitor_header[1],h->h1.version);
   monitor_header[3] = 'M'; // monitor ID
   byte2hex(&monitor_header[4],h->h1.mon_id);
   monitor_header[6] = 'B'; // tamanho da entrada de dados
   int2hex(&monitor_header[7],h->h1.entry_size);
   monitor_header[11] = 'I'; // intervalo de amostragem
   int2hex(&monitor_header[12],h->h1.time_interv);
   monitor_header[16] = '\r';
   monitor_header[17] = '\n';
   monitor_header[18] = 'T'; // estampa de tempo
   int2hex(&monitor_header[19],h->h2.year);
   byte2hex(&monitor_header[23],h->h2.mon);
   byte2hex(&monitor_header[25],h->h2.mday);
   byte2hex(&monitor_header[27],h->h2.hour);
   byte2hex(&monitor_header[29],h->h2.min);
   byte2hex(&monitor_header[31],h->h2.sec);
   monitor_header[33] = tohex(h->h2.synched);
   monitor_header[34] = '\r';
   monitor_header[35] = '\n';
   monitor_header[36] = 'P'; // índice da última entrada enviada
   int2hex(&monitor_header[37],h->last_idx);
   monitor_header[41] = '\r';
   monitor_header[42] = '\n';
   monitor_header[43] = 'C'; // contador de entradas do log
   int2hex(&monitor_header[44],h->count);
   monitor_header[48] = '\r';
   monitor_header[49] = '\n';
   monitor_header[50] = '\0';
}

uint8_t monitor_setheader(const char* filename, monitor_header_t * h)
{
   LOG_FILETYPE fp;  

#ifndef _WIN32
   if(monitor_openappend(filename,&fp))
   {
	   monitor_makeheader(monitor_header,h);
	   (void)monitor_write(monitor_header,&fp);
	   (void)monitor_close(&fp);
	   return TRUE;
   }   
#else
   if(monitor_openread(filename,&fp))
   {
	   monitor_makeheader(monitor_header,h);
	   (void)monitor_write(monitor_header,&fp);
	   (void)monitor_close(&fp);
	   return TRUE;
   }
#endif
   
   return FALSE;

}

uint8_t monitor_getheader(const char* filename, monitor_header_t * h)
{

	   LOG_FILETYPE fp;
	   int idx = 0;
	   char hex1,hex2;
	   uint8_t b1,b2;
	   uint8_t ok = FALSE;

#define NEXT_2(res)	do{hex1 = monitor_header[idx++]; hex2 = monitor_header[idx++];} while(0); (res) = hex2byte(hex1,hex2);
#define NEXT_4(res) do{hex1 = monitor_header[idx++]; hex2 = monitor_header[idx++]; b1 = hex2byte(hex1,hex2); hex1 = monitor_header[idx++];hex2 = monitor_header[idx++]; b2 = hex2byte(hex1,hex2);}while(0); (res) = byte2int(b1,b2);
	   	   
	   if(!monitor_openread(filename,&fp))
	   {
		   return FALSE;
	   }

	   /* process first header line */
	   if(!monitor_read(monitor_header,LOG_HEADER_LEN,&fp))
	   {		   		  
		   goto exit_read_error;
	   }
	   
	   if(monitor_header[idx++] != 'V') goto exit_read_error;
	   {
		   NEXT_2(h->h1.version);
	   }
	   if(monitor_header[idx++]  != 'M') goto exit_read_error;
	   {
		   NEXT_2(h->h1.mon_id);
	   }
	   if(monitor_header[idx++] != 'B') goto exit_read_error;
	   {
		   NEXT_4(h->h1.entry_size);
	   }
	   if(monitor_header[idx++] != 'I') goto exit_read_error;
	   {
		   NEXT_4(h->h1.time_interv);
	   }
	   ASSERT (idx == 16);

	   /* process second header line */
	   if(!monitor_read(monitor_header,LOG_HEADER_LEN,&fp))
	   {
		   goto exit_read_error;
	   }			   
	   idx = 0;
	   if(monitor_header[idx++] != 'T') goto exit_read_error;
	   {
		   NEXT_4(h->h2.year);
		   NEXT_2(h->h2.mon);
		   NEXT_2(h->h2.mday);
		   NEXT_2(h->h2.hour);
		   NEXT_2(h->h2.min);
		   NEXT_2(h->h2.sec);
		   h->h2.synched = hex2val(monitor_header[idx++]);
	   }
	   ASSERT (idx == 16);
	
	   /* process third header line */
	   if(!monitor_read(monitor_header,LOG_HEADER_LEN,&fp))
	   {
		   goto exit_read_error;
	   }
	   idx = 0;
	   if(monitor_header[idx++] != 'P') goto exit_read_error;
	   {
		   NEXT_4(h->last_idx);
	   }
	   ASSERT (idx == 5);

	   /* process fourth header line */
	   if(!monitor_read(monitor_header,LOG_HEADER_LEN,&fp))
	   {
		   goto exit_read_error;
	   }
	   idx = 0;
	   if(monitor_header[idx++] != 'C') goto exit_read_error;
	   {
		   NEXT_4(h->count);
	   }
	   ASSERT (idx == 5);

	   ok = TRUE; /* succes */

	   exit_read_error:
	   (void)monitor_close(&fp);
	   
	   return  ok;

}

uint8_t monitor_newheader(const char* filename, uint8_t monitor_id, uint16_t interval, uint16_t entry_size)
{
	monitor_header_t h = {{0,0,0,0},{0,0,0,0,0,0,0},0,0};
	h.h1.mon_id = monitor_id;
	h.h1.time_interv = interval;
	h.h1.entry_size = entry_size;
	if(monitor_setheader(filename, &h) == FALSE)
	{
		return FALSE;
	}
	return monitor_getheader(filename, &h);
}

uint8_t monitor_validateheader(const char* filename, uint8_t monitor_id, uint16_t interval, uint16_t entry_size)
{
	monitor_header_t h = {{0,0,0,0},{0,0,0,0,0,0,0},0,0};
	if(monitor_getheader(filename, &h))
	{
		if( h.h1.mon_id == monitor_id && 
			h.h1.time_interv == interval &&
			h.h1.entry_size == entry_size)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}	
	return FALSE;
}

#ifndef _WIN32
#include "time_lib.h"
#else
#include "http_client.h"
#include "time.h"
#endif

uint8_t monitor_gettimestamp(struct tm * timestamp, uint32_t time_elapsed_s)
{

	/* GET time/local */
	time_t time_now = 0;

#define SERVER_TIME 1
#if SERVER_TIME
	struct tm serv_time;

    if(!is_simon_clock_synched())
	{
		if(simon_get_time(&serv_time) == MODEM_ERR)
		{
			return MODEM_ERR;
		}
		time_now = mktime(&serv_time);
		simon_clock_set(time_now);
	}else
	{		
		time_now = simon_clock_get();
	}
	
#else
	time_now = time(NULL);
#endif

	time_now = time_now - time_elapsed_s;
	(*timestamp) = *((struct tm *)localtime(&(time_t){time_now}));	
	return MODEM_OK;
}

#include "string.h"
void monitor_settimestamp(uint8_t monitor_num, const char* filename)
{
	uint32_t time_elapsed_s = 0;
	monitor_header_t h = {{0,0,0,0},{0,0,0,0,0,0,0},0,0};
	struct tm ts;
	char new_filename[8+5]={"00000000.txt"};
	int ret;
	LOG_FILETYPE fp;

	if(!monitor_getheader((const char*)filename, &h)) return;

	/* check if already synched */
	if(h.h2.synched == 0)
	{
		time_elapsed_s = (uint32_t)((h.h1.time_interv)*(h.count));
		
		
		PRINTF_P(PSTR("\r\n Mon %d will be synched \r\n"), monitor_num );
		if( monitor_gettimestamp(&ts, time_elapsed_s) == MODEM_ERR)
		{
			PRINTS_P(PSTR("\r\n Synch failed, will try again later \r\n"));
			return;
		}		

		h.h2.year = (uint16_t)(ts.tm_year + 1900);
		h.h2.mon = (uint8_t)(ts.tm_mon + 1);
		h.h2.mday = (uint8_t)ts.tm_mday;
		h.h2.hour = (uint8_t)ts.tm_hour;
		h.h2.min = (uint8_t)ts.tm_min;
		h.h2.sec = (uint8_t)ts.tm_sec;
		h.h2.synched = 1;

		monitor_state[monitor_num].sinc = 1;
		monitor_state[monitor_num].sinc_time = simon_clock_get() - time_elapsed_s;
		

#if 0
#if _WIN32
			fflush(stdout);
#endif

			do
			{
				char timestamp[20];
				strftime(timestamp,20,"T%Y%m%d%H%M%SS\r\n",&ts);
				PRINTF(timestamp);
			}while(0);
#endif

			monitor_setheader((const char*)filename, &h);
			
			PRINTF_P(PSTR("\r\n Mon %d is synched \r\n"), monitor_num );

			/* rename file */
			strftime(new_filename,sizeof(new_filename),"%y%m%d%H.txt",&ts);	

			if(is_terminal_idle() && mon_verbosity > 3)
			{
				PRINTF_P(PSTR("\r\n %s will be renamed to %s \r\n"), filename,new_filename);
			}
			
			ret = monitor_rename((char*)filename, (const char*)new_filename);

			/* if rename failed, try other name */
			while(!ret)
			{
				PRINTS_ERRO_P(PSTR("\r\n rename failed \r\n"));
				time_t time_now = mktime(&ts);
				time_now +=3600;
				ts = *localtime(&(time_t){time_now});
				strftime(new_filename,sizeof(new_filename),"%y%m%d%H.txt",&ts);

				monitor_setheader((const char*)filename, &h);

				if(is_terminal_idle() && mon_verbosity > 3)
				{
					PRINTS_P(PSTR("\r\n rename failed \r\n"));
					PRINTF_P(PSTR("\r\n %s will be renamed to %s \r\n"), filename,new_filename);
				}
				
				ret = monitor_rename((char*)filename, (const char*)new_filename);

			}

			/* log is reading the same file ? */
			if(strcmp(monitor_state[monitor_num].monitor_name_reading, monitor_state[monitor_num].monitor_name_writing) == 0)
			{
				if(is_terminal_idle() && mon_verbosity > 3)
				{
					PRINTS_P(PSTR("\r\n reading the same file that we renamed! \r\n"));
				}				

				strcpy(monitor_state[monitor_num].monitor_name_reading,new_filename);

				/* update meta file */
				if(monitor_openwrite(LOG_METAFILE,&fp))
				{
				   if(monitor_write(monitor_state[monitor_num].monitor_name_reading,&fp)){;}
				   (void)monitor_close(&fp);
				}
			}
			strcpy(monitor_state[monitor_num].monitor_name_writing,new_filename);
	}
}

uint16_t monitor_writeentry(const char* filename, char* entry, uint8_t monitor_num)
{

	LOG_FILETYPE fp;
	monitor_header_t h = {{0,0,0,0},{0,0,0,0,0,0,0},0,0};	
	
	try_write_again:
	if(monitor_getheader(filename, &h))
	{
		if(monitor_openappend(filename,&fp))
		{
		   (void)monitor_seek_end(&fp);
		   (void)monitor_write(entry,&fp);
		   (void)monitor_close(&fp);

		   h.count++; // incrementa contador de entradas 
		   monitor_setheader(filename, &h);
		   
		   monitor_state[monitor_num].total_written_entries++;
		   
		}else
		{
			PRINT_ERRO_P(PSTR("Erro: open file %s\r\n"), filename);
			return 0; // tratar este erro!!!
		}
		
		
		/* if file is not synched, try to synch */
		if(h.h2.synched == 0)
		{
			monitor_sync(monitor_num, filename);
		}
	
	}else
	{
		 // cria novo arquivo e header
		 if(monitor_openwrite(monitor_state[monitor_num].monitor_name_writing,&fp))
		 {
			 if(monitor_newheader(monitor_state[monitor_num].monitor_name_writing,
									   monitor_state[monitor_num].config_h.mon_id,
									   monitor_state[monitor_num].config_h.time_interv,
									   monitor_state[monitor_num].config_h.entry_size) == TRUE)
			 {
				 
				 goto try_write_again;
			 }		
		 }
		 
		 PRINT_ERRO_P(PSTR("Erro: new header"), monitor_num);
		
	}

	return h.count;

}

static uint16_t build_entry_to_send(char* const ptr_out, uint8_t * const data_in, uint16_t len)
{
	int offset = 0;
	uint16_t max_len = len/3;
	char hex1,hex2;
	uint8_t val;
	uint16_t cnt = 0;
	char* ptr_data = ptr_out;
	uint8_t * data = data_in;
	
	while(len > 0)
	{
		len-=2;
		hex1 = *data++;
		hex2 = *data++;
		val = hex2byte(hex1,hex2);

		offset = SNPRINTF(ptr_data, max_len,"%u,", val);
		if(offset < 0 || offset >= max_len)
		{
			return 0;
		}
		ptr_data+= offset;
		cnt+=offset;
	}
	*(--ptr_data) = '\0'; // null terminate string
	return cnt;
}

static int monitor_entry_send(uint8_t mon_id, monitor_entry_t* entry, uint16_t len)
{
	
	uint16_t cnt = 0;
	cnt = build_entry_to_send(data_vector,entry->values,len);

	if(mon_verbosity > 4 && is_terminal_idle())
	{
		PRINTF_P(PSTR("\r\n"));
		PRINTF(data_vector);
		PRINTF_P(PSTR("\r\n"));
	}

	
#ifdef _WIN32	
	fflush(stdout);
#endif	

	if(cnt > 0)
	{
		if(simon_send_data((uint8_t*)data_vector,cnt,mon_id,entry->ts) == MODEM_OK)
		{
			return TRUE;
		}
	}else
	{
		PRINTS_ERRO_P(PSTR("Erro: building data vector\r\n"));
	}

	return FALSE;
}

uint32_t monitor_readentry(uint8_t monitor_num, const char* filename, monitor_entry_t* entry)
{
	uint32_t entry_size;
	LOG_FILETYPE fp;
	uint32_t  pos;
	struct tm ts;	
	clock_t  time_init;	
	uint8_t  send_ok = 0;
	time_t unix_time;
	uint32_t idx = 0;

	monitor_header_t h = {{0,0,0,0},{0,0,0,0,0,0,0},0,0};

	if(!monitor_getheader(filename, &h)) return (MAX_NUM_OF_ENTRIES); /* header format error */

	if (h.h2.synched == 0) return (MAX_NUM_OF_ENTRIES); /* file not synched */

	entry_size = (h.h1.entry_size)*2 + 2; // x2 pois cada byte está com 2 char, +2 pois inclui "\r\n"

	/* se o arquivo não terminou !!! */
	if(h.last_idx < h.count)
	{
		ts.tm_year = h.h2.year - 1900;
		ts.tm_mon = h.h2.mon - 1;
		ts.tm_mday = h.h2.mday;
		ts.tm_hour = h.h2.hour;
		ts.tm_min = h.h2.min;
		ts.tm_sec = h.h2.sec;
		ts.tm_isdst = -1;

		unix_time = mktime(&ts);

		if(unix_time > 0)
		{
			unix_time += (h.last_idx)*(h.h1.time_interv);
			entry->ts = unix_time;
		}

		/* le a proxima entrada */
		if(monitor_openread(filename,&fp))
		{
			idx = ((uint32_t)(h.last_idx));
			idx = idx*entry_size;
			idx += LOG_HEADER_LEN;
			
			pos = (uint32_t)idx;

			if(monitor_seek(&fp,&pos))
			{
			   (void)monitor_read((char*)entry->values,entry_size,&fp);
			   (void)monitor_close(&fp);

			   /* try to send */
			   time_init = clock_time();			   
			   send_ok = 0;
			   
			   if(h.last_idx == 0)
			   {
				   monitor_state[monitor_num].time_to_send = 0;
				   monitor_state[monitor_num].avg_time_to_send = 0;
				   monitor_state[monitor_num].written_entries= 0;
				   monitor_state[monitor_num].read_entries = 0;
				   monitor_state[monitor_num].sent_entries= 0;
			   }
			   
			   monitor_state[monitor_num].read_entries++;
			   
			   monitor_state[monitor_num].sending = 1;

			   if(mon_verbosity > 4 && is_terminal_idle())  
			   { 
				   PRINTF_P(PSTR("\r\nThread R %u, read file pos %lu, "), monitor_num, pos);
				   PRINTF_P(PSTR("entry index %u, size: %u, will send now: \r\n"), h.last_idx, entry_size);
				   PRINTF("%s\r\n", (char*)entry->values);
			   }
			   
			   if(monitor_entry_send(monitor_num,entry,entry_size-2) == TRUE) // ignore \r\n
			   {
				   /* if ok */
				   h.last_idx++; // incrementa indice da última entrada lida
				   monitor_setheader(filename, &h);	
				   send_ok = 1;
			   }
			   
			   monitor_state[monitor_num].time_to_send += (uint32_t)(clock_time()-time_init);
			   
			   if(send_ok == 1)
			   {
				   monitor_state[monitor_num].sent_entries++;
				   monitor_state[monitor_num].avg_time_to_send = ((monitor_state[monitor_num].avg_time_to_send*7) + monitor_state[monitor_num].time_to_send)/8;
				   monitor_state[monitor_num].last_timestamp = unix_time;				  
				   monitor_state[monitor_num].sending = 0;
				   
				   if (mon_verbosity > 1 && is_terminal_idle())
				   {
					   PRINTF_P(PSTR("Mon %u, entry: %u of %u, delay: %lu - avg: %lu"),
							   monitor_num,
							   h.last_idx, h.count,
							   monitor_state[monitor_num].time_to_send,
							   monitor_state[monitor_num].avg_time_to_send);

						char timestamp[32];
						ts = *localtime(&(time_t){unix_time});
						strftime(timestamp,SIZEARRAY(timestamp)," @%Y|%m|%d %H:%M:%S\r\n",&ts);
						PRINTF(timestamp);
				   }
				   
				   monitor_state[monitor_num].time_to_send = 0;
			   }			   

			   return h.last_idx;
			}
		}
	}
	else
	{
		// if(h.last_idx == h.count)
		/* monitor is not writing in the same reading file ? */
		if(strcmp(monitor_state[monitor_num].monitor_name_reading, monitor_state[monitor_num].monitor_name_writing) != 0)
		{
			strcpy(monitor_state[monitor_num].monitor_name_reading,monitor_state[monitor_num].monitor_name_writing);
			
			/* update meta file */
			if(monitor_openwrite(LOG_METAFILE,&fp))
			{
			   if(monitor_write(monitor_state[monitor_num].monitor_name_reading,&fp)){;}
			   (void)monitor_close(&fp);
			}
		}
	}
	return (MAX_NUM_OF_ENTRIES);
}

void monitor_sync(uint8_t monitor_num, const char* monitor_fn)
{
	monitor_settimestamp(monitor_num, monitor_fn); // sincronizar
}

#if _WIN32
#include<windows.h>
#include <sys/stat.h>
#endif

/* open dir and try to open/create a new file */
uint8_t monitor_init(uint8_t monitor_num)
{

	  LOG_DIRTYPE  d;
	  LOG_FILETYPE fp;
	  LOG_DIRINFO  dir;
	  LOG_FILEINFO fnfo;

	  strcpy(monitor_state[monitor_num].monitor_name_writing, LOG_FILENAME_START);

	  if (!(monitor_stat(monitor_state[monitor_num].monitor_dir_name, &fnfo)))
	  {
		  if(!(monitor_mkdir(monitor_state[monitor_num].monitor_dir_name)))
		  {
			  return FALSE;
		  }
	  }

	  if (monitor_opendir(monitor_state[monitor_num].monitor_dir_name, d))
	  {
#if 1		  
	    while (monitor_readdir(dir,d))
	    {
#if _WIN32
	    	PRINTF("%s\r\n", dir->d_name);
#else
	    	PRINTF("%s\r\n", (LOG_DIRINFO*)(&dir)->fname);
#endif
	    }
#endif
	    
	    monitor_closedir(d);
	  }else
	  {
		  print_erro_and_exit:
		  PRINT_ERRO_P(PSTR("Log init erro: %d"), monitor_num);
		  PRINTS_P(PSTR("Log init erro")); PRINTC(monitor_num + '0');
		  return FALSE;
	  }
	  
	 /* check buffer size */
	if(monitor_state[monitor_num].config_h.entry_size > LOG_MAX_DATA_BUF_SIZE)
	{		
		PRINTS_ERRO_P(PSTR("buffer too small \r\n"));
		goto print_erro_and_exit;
	}

	 /* change to log dir */
	 monitor_chdir(monitor_state[monitor_num].monitor_dir_name);

     /* try open log or create it now */
	 if(!(monitor_openappend(monitor_state[monitor_num].monitor_name_writing,&fp)))
	 {
	   if(monitor_openwrite(monitor_state[monitor_num].monitor_name_writing,&fp))
	   {
		   goto make_new_header;
	   }else
	   {
		   goto print_erro_and_exit;
	   }
	 }
	 
	 /* validate header */
	 if(monitor_validateheader(monitor_state[monitor_num].monitor_name_writing,
			   monitor_state[monitor_num].config_h.mon_id,
			   monitor_state[monitor_num].config_h.time_interv,
			   monitor_state[monitor_num].config_h.entry_size) == FALSE)
	 {
		 make_new_header:
		 if(monitor_newheader(monitor_state[monitor_num].monitor_name_writing,
		 				   monitor_state[monitor_num].config_h.mon_id,
		 				   monitor_state[monitor_num].config_h.time_interv,
		 				   monitor_state[monitor_num].config_h.entry_size) == FALSE)
		   {
			 goto print_erro_and_exit;
		   }		   
	 }
	 (void)monitor_close(&fp);

     /* try open metalog or create a new one */
	 if(monitor_openread(LOG_METAFILE,&fp))
	 {
		 if(monitor_read(monitor_state[monitor_num].monitor_name_reading,FILENAME_MAX_LENGTH,&fp))
		 {
			 monitor_state[monitor_num].monitor_name_reading[FILENAME_MAX_LENGTH-1] = '\0'; // null terminate
			 (void)monitor_close(&fp);

			 // check if the file exists
			 if(monitor_openread(monitor_state[monitor_num].monitor_name_reading,&fp))
			 {
				 (void)monitor_close(&fp);
			 }
			 else
			 {
				 (void)monitor_close(&fp);
				 goto fail_to_open_monitor_reader;
			 }
		 }else
		 {
			 (void)monitor_close(&fp);
			 goto fail_to_open_monitor_reader;
		 }

	 }else
	 {
	   fail_to_open_monitor_reader:
	   if(monitor_openwrite(LOG_METAFILE,&fp))
	   {
		   strcpy(monitor_state[monitor_num].monitor_name_reading,monitor_state[monitor_num].monitor_name_writing);
		   if(monitor_write(monitor_state[monitor_num].monitor_name_writing,&fp)){;}
		   (void)monitor_close(&fp);
	   }else
	   {
		   goto print_erro_and_exit;
	   }
	 }

	 /* change to parent dir */
	 monitor_chdir("..");
	 return TRUE;
}

char* monitor_getfilename_to_write(uint8_t monitor_num)
{
	return (char*)monitor_state[monitor_num].monitor_name_writing;
}

char* monitor_getfilename_to_read(uint8_t monitor_num)
{
	return (char*)monitor_state[monitor_num].monitor_name_reading;
}

void monitor_writer(uint8_t monitor_num)
{	
	uint16_t cnt = 0;
	extern const char* monitor_error_msg[];
	
	static uint32_t missing_entries = 0;

#if 0  /* check modem connection */
	if(simon_check_connection() == MODEM_OK)
	{
		monitor_is_connected = 1;
	}else
	{
		monitor_is_connected = 0;
	}
#endif
	
#if MONITOR_TESTS
	uint16_t vetor_dados[3]={0x1111,0x2222,0x3333};	
	monitor_createentry(monitor_char_buffer,vetor_dados,3);

	assert((monitor_char_buffer[0] == '1') && (monitor_char_buffer[1]== '1') && 
			(monitor_char_buffer[2] == '1') && (monitor_char_buffer[3]== '1') &&
			(monitor_char_buffer[0+4] == '2') && (monitor_char_buffer[1+4]== '2') && 
			(monitor_char_buffer[2+4] == '2') && (monitor_char_buffer[3+4]== '2') &&
			(monitor_char_buffer[0+2*4] == '3') && (monitor_char_buffer[1+2*4]== '3') && 
			(monitor_char_buffer[2+2*4] == '3') && (monitor_char_buffer[3+2*4]== '3'));

#else	
	
#if 0
		PRINTF_P(PSTR("Slave %d reading\r\n"), monitor_state[monitor_num].slave_addr);
#endif
		
	/* read data */
	if(monitor_state[monitor_num].read_data(monitor_state[monitor_num].slave_addr,(uint8_t*)monitor_data_buffer,(uint8_t)monitor_state[monitor_num].config_h.entry_size) == 0)
	{
		PRINT_ERRO_PP(monitor_error_msg[1], monitor_num);
		PRINT_ERRO_P(PSTR("read slave %d failed\r\n"), monitor_state[monitor_num].slave_addr);
		return;
	}
	
	if(is_terminal_idle() && mon_verbosity > 3)
	{
		PRINTF_PP(monitor_error_msg[2], monitor_num);
		PRINTF_P(PSTR(" read slave %d ok\r\n"), monitor_state[monitor_num].slave_addr);
	}

	
	/* convert data to hex char */
	monitor_createentry(monitor_char_buffer,(uint16_t*)monitor_data_buffer,(uint8_t)(monitor_state[monitor_num].config_h.entry_size/2));

#endif		

	/* change to log dir */
	monitor_chdir(monitor_state[monitor_num].monitor_dir_name);
	
	/* write data (hex char) to file  */
	cnt = monitor_writeentry(monitor_getfilename_to_write(monitor_num),monitor_char_buffer, monitor_num);
	
	if(cnt == 0)
	{
		missing_entries++; /* count missing entries */
		PRINT_ERRO_PP(monitor_error_msg[1], (uint8_t) monitor_num);		
		PRINTS_ERRO_P(PSTR("write failed\r\n"));
		PRINT_ERRO_P(PSTR("\r\nMissed entries %d\r\n"), missing_entries);
	}else
	{
		monitor_state[monitor_num].written_entries++;
		
		if(is_terminal_idle() && mon_verbosity > 2)
		{
			PRINTF_P(PSTR("\r\nM %d, Size: %u, Entry %u: "), monitor_num, strlen(monitor_char_buffer), cnt);
			PRINTF(monitor_char_buffer);
			PRINTS_P(PSTR("\r\n"));		
		}
	}

	/* change to parent dir */
	monitor_chdir("..");
	
}

uint16_t monitor_reader(uint8_t monitor_num)
{
	monitor_entry_t entry;
	uint16_t nread;

	char* fname = (char *)monitor_getfilename_to_read(monitor_num);
	
	if(*fname == '\0') return 0;
	
	memset(monitor_char_buffer,0x00,sizeof(monitor_char_buffer));
	entry.values = (uint8_t*)monitor_char_buffer;

	/* change to log dir */
	monitor_chdir(monitor_state[monitor_num].monitor_dir_name);

	if(mon_verbosity > 4 && is_terminal_idle())  PRINTF_P(PSTR("\r\nThread R %u, read file: %s \r\n"), monitor_num, (char*)fname);
	
	if((nread = monitor_readentry(monitor_num, fname, &entry)) != 0)
	{
#if 0		
		char buffer[sizeof(long)*8+1];
		if( nread < MAX_NUM_OF_ENTRIES)
		{			
			PRINTF((char*)entry.values);
			PRINTF(ltoa((long)entry.ts,buffer,10));
		}
#endif		
	}

	/* change to parent dir */
	monitor_chdir("..");
	
	return nread;

}




