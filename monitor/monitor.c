/*
 * monitor.c
 *
 *  Created on: 15/04/2015
 *      Author: UFSM
 */

#include "monitor.h"
#include "printf_lib.h"
#include "utils.h"
#include "assert.h"
#include "simon-api.h"

#ifdef _WIN32
#include "http_client.h"
#define DEBUG_MONITOR 1
#endif

#if DEBUG_MONITOR
#define PRINTF(...) printf(__VA_ARGS__);
#else
#define PRINTF(...)
#endif

#define MONITOR_TESTS 0

extern log_state_t logger_state[MAX_NUM_OF_LOGGERS];

LOG_FILETYPE stderr_f;

char buffer_erro[256];

#define error_file		"erro.txt"
#include <stdarg.h>
/*-----------------------------------------------------------------------------------*/
void print_erro(char *format, ...)
{

#if 1
  va_list argptr;
  va_start(argptr, format);
  VSPRINTF(buffer_erro, format, argptr);  
  va_end(argptr);
#endif  

  if(log_openwrite(error_file,&stderr_f))
  {
	  (void)log_write(buffer_erro,&stderr_f);
	  (void)log_close(&stderr_f);
  }
}


void log_createentry(char* string, uint16_t *dados, uint16_t len)
{

	uint16_t dado = 0;
	do
	{
		dado=*dados;
		int2hex(string,dado);
		string+=4;
		dados++;
		len--;
	}while(len > 0);

	*string++='\r';
	*string++='\n';
	*string++='\0';
}

void log_makeheader(char log_header[], log_header_t * h)
{

   log_header[0] = 'V'; // vers�o
   byte2hex(&log_header[1],h->h1.version);
   log_header[3] = 'M'; // monitor ID
   byte2hex(&log_header[4],h->h1.mon_id);
   log_header[6] = 'B'; // tamanho da entrada de dados
   int2hex(&log_header[7],h->h1.entry_size);
   log_header[11] = 'I'; // intervalo de amostragem
   int2hex(&log_header[12],h->h1.time_interv);
   log_header[16] = '\r';
   log_header[17] = '\n';
   log_header[18] = 'T'; // estampa de tempo
   int2hex(&log_header[19],h->h2.year);
   byte2hex(&log_header[23],h->h2.mon);
   byte2hex(&log_header[25],h->h2.mday);
   byte2hex(&log_header[27],h->h2.hour);
   byte2hex(&log_header[29],h->h2.min);
   byte2hex(&log_header[31],h->h2.sec);
   log_header[33] = tohex(h->h2.synched);
   log_header[34] = '\r';
   log_header[35] = '\n';
   log_header[36] = 'P'; // �ndice da �ltima entrada enviada
   int2hex(&log_header[37],h->last_idx);
   log_header[41] = '\r';
   log_header[42] = '\n';
   log_header[43] = 'C'; // contador de entradas do log
   int2hex(&log_header[44],h->count);
   log_header[48] = '\r';
   log_header[49] = '\n';
   log_header[50] = '\0';
}

void log_setheader(char* filename, log_header_t * h)
{
   LOG_FILETYPE fp;
   char log_header[LOG_HEADER_LEN+1];

   if(log_openread(filename,&fp))
   {
	   log_makeheader(log_header,h);
	   (void)log_write(log_header,&fp);
	   (void)log_close(&fp);
   }

}

void log_getheader(char* filename, log_header_t * h)
{

	   LOG_FILETYPE fp;
	   char log_header[LOG_HEADER_LEN+1];
	   int idx = 0;
	   char hex1,hex2;
	   uint8_t b1,b2;

#define NEXT_2(res)	do{hex1 = log_header[idx++]; hex2 = log_header[idx++];} while(0); (res) = hex2byte(hex1,hex2);
#define NEXT_4(res) do{hex1 = log_header[idx++]; hex2 = log_header[idx++]; b1 = hex2byte(hex1,hex2); hex1 = log_header[idx++];hex2 = log_header[idx++]; b2 = hex2byte(hex1,hex2);}while(0); (res) = byte2int(b1,b2);

	   if(log_openread(filename,&fp))
	   {
		   if(log_read(log_header,LOG_HEADER_LEN,&fp))
		   {
			   if(log_header[idx++] == 'V')
			   {
				   NEXT_2(h->h1.version);
			   }
			   if(log_header[idx++]  == 'M')
			   {
				   NEXT_2(h->h1.mon_id);
			   }
			   if(log_header[idx++] == 'B')
			   {
				   NEXT_4(h->h1.entry_size);
			   }
			   if(log_header[idx++] == 'I')
			   {
				   NEXT_4(h->h1.time_interv);
			   }
			   assert (idx == 16);

		   }

		   // read next line
		   if(log_read(log_header,LOG_HEADER_LEN,&fp))
		   {
			   idx = 0;
			   if(log_header[idx++] == 'T')
			   {
				   NEXT_4(h->h2.year);
				   NEXT_2(h->h2.mon);
				   NEXT_2(h->h2.mday);
				   NEXT_2(h->h2.hour);
				   NEXT_2(h->h2.min);
				   NEXT_2(h->h2.sec);
				   h->h2.synched = hex2val(log_header[idx++]);
			   }
			   assert (idx == 16);
		   }

		   // read next line
		   if(log_read(log_header,LOG_HEADER_LEN,&fp))
		   {
			   idx = 0;
			   if(log_header[idx++] == 'P')
			   {
				   NEXT_4(h->last_idx);
			   }
			   assert (idx == 5);
		   }

		   // read next line
		   if(log_read(log_header,LOG_HEADER_LEN,&fp))
		   {
			   idx = 0;
			   if(log_header[idx++] == 'C')
			   {
				   NEXT_4(h->count);
			   }
			   assert (idx == 5);
		   }


		   (void)log_close(&fp);
	   }
}

void log_newheader(char* filename, uint8_t monitor_id, uint16_t interval, uint16_t entry_size)
{
	log_header_t h = {{0,0,0,0},{0,0,0,0,0,0,0},0,0};
	h.h1.mon_id = monitor_id;
	h.h1.time_interv = interval;
	h.h1.entry_size = entry_size;
	log_setheader(filename, &h);
}

#ifndef _WIN32
#include "time_lib.h"
#include "http_client.h"
#else
#include "time.h"
#endif

void log_gettimestamp(struct tm * timestamp, uint32_t time_elapsed_s)
{

	/* GET time/local */
	time_t time_now = 0;

#define SERVER_TIME 1
#if SERVER_TIME
	struct tm t;
	//http_get_time(&t);
	simon_get_time(&t);
	time_now = mktime(&t);
#else
	time_now = time(NULL);
#endif

	time_now = time_now - time_elapsed_s;
	(*timestamp) = *localtime(&(time_t){time_now});
}

#include "string.h"
void log_settimestamp(uint8_t logger_num, char* filename)
{
	uint32_t time_elapsed_s = 0;
	log_header_t h = {{0,0,0,0},{0,0,0,0,0,0,0},0,0};
	struct tm ts;
	char new_filename[8+5]={"00000000.txt"};
	uint8_t ret;

	log_getheader(filename, &h);

	/* check if already synched */
	if(h.h2.synched == 0)
	{
		time_elapsed_s = (h.h1.time_interv)*(h.count);
		log_gettimestamp(&ts, time_elapsed_s);

		#if 1
			h.h2.year = (uint16_t)(ts.tm_year + 1900);
			h.h2.mon = (uint8_t)(ts.tm_mon + 1);
			h.h2.mday = (uint8_t)ts.tm_mday;
			h.h2.hour = (uint8_t)ts.tm_hour;
			h.h2.min = (uint8_t)ts.tm_min;
			h.h2.sec = (uint8_t)ts.tm_sec;
		#else
			h.h2.year = (uint16_t)2015;
			h.h2.mon = (uint8_t)04;
			h.h2.mday = (uint8_t)21;
			h.h2.hour = (uint8_t)18;
			h.h2.min = (uint8_t)10;
			h.h2.sec = (uint8_t)33;
			PRINTF("\r\n%d%d%d%d%d%d\r\n", h.h2.year,h.h2.mon,h.h2.mday,h.h2.hour,h.h2.min,h.h2.sec);
		#endif

			h.h2.synched = 1;

#if 1
			do
			{
				char timestamp[20];
				strftime(timestamp,20,"T%Y%m%d%H%M%SS\r\n",&ts);
				PRINTF(timestamp);
			}while(0);
#endif

			log_setheader(filename, &h);

			/* rename file */
			strftime(new_filename,sizeof(new_filename),"%y%m%d%H.txt",&ts);

			PRINTF("\r\n %s will be renamed to %s \r\n", filename,new_filename);
			ret = log_rename(filename, new_filename);

			/* if rename failed, try other name */
			while(!ret)
			{
				PRINTF("\r\n rename failed \r\n");
				time_t time_now = mktime(&ts);
				time_now +=3600;
				ts = *localtime(&(time_t){time_now});
				strftime(new_filename,sizeof(new_filename),"%y%m%d%H.txt",&ts);

				PRINTF("\r\n %s will be renamed to %s \r\n", filename,new_filename);
				ret = log_rename(filename, new_filename);

			}

			/* log is reading the same file ? */
			if(strcmp(logger_state[logger_num].log_name_reading, logger_state[logger_num].log_name_writing) == 0)
			{
				PRINTF("\r\n reading the same file that we renamed! \r\n");

				strcpy(logger_state[logger_num].log_name_reading,new_filename);

				/* update meta file */
				LOG_FILETYPE fp;
				if(log_openwrite(LOG_METAFILE,&fp))
				{
				   if(log_write(logger_state[logger_num].log_name_reading,&fp)){;}
				   (void)log_close(&fp);
				}
			}
			strcpy(logger_state[logger_num].log_name_writing,new_filename);
	}
}


extern volatile uint8_t log_is_connected;

uint16_t log_writeentry(char* filename, char* entry)
{
	uint16_t ret;
	LOG_FILETYPE fp;
	log_header_t h = {{0,0,0,0},{0,0,0,0,0,0,0},0,0};

	log_getheader(filename, &h);

	if(log_openappend(filename,&fp))
	{
	   ret = log_write(entry,&fp);
	   (void)log_close(&fp);
	   assert(ret == 1);

	   h.count++; // incrementa contador de entradas
	   log_setheader(filename, &h);

	}else
	{
	   assert(0);
	}

	/* if file is not synched, try to synch */
	if(log_is_connected == 1 && h.h2.synched == 0)
	{
		log_sync(filename);
	}

	return h.count;

}

uint16_t build_entry_to_send(char* ptr_data, uint8_t *data, uint8_t len)
{
	uint16_t offset = 0;
	uint16_t max_len = 4*len;
	char hex1,hex2;
	uint8_t val;
	uint16_t cnt = 0;

	while(len > 0)
	{
		len-=2;
		hex1 = *data++;
		hex2 = *data++;
		val = hex2byte(hex1,hex2);

		offset = SNPRINTF(ptr_data, max_len,"%d,", val);
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

uint8_t log_entry_send(log_entry_t* entry, uint8_t len)
{

	char data_vector[256*4];
	uint16_t cnt = 0;
	cnt = build_entry_to_send(data_vector,entry->values,len);


	PRINTF("\r\n");
	PRINTF(data_vector);
	PRINTF("\r\n");
	
#ifdef _WIN32	
	fflush(stdout);
#endif	

	if(cnt > 0)
	{
#ifdef _WIN32			
		http_send_data(data_vector,cnt);
#endif			
	}

	return 1;
}

uint32_t log_readentry(uint8_t logger_num, char* filename, log_entry_t* entry)
{
	uint16_t entry_size;
	LOG_FILETYPE fp;
	LOG_FILEPOS  pos = LOG_HEADER_LEN;
	struct tm ts;

	log_header_t h = {{0,0,0,0},{0,0,0,0,0,0,0},0,0};

	log_getheader(filename, &h);

	if (h.h2.synched == 0) return (MAX_NUM_OF_ENTRIES); /* file not synched */

	entry_size = (h.h1.entry_size) + 2; // inclui \r\n

	if(h.last_idx < h.count)
	{
		ts.tm_year = h.h2.year - 1900;
		ts.tm_mon = h.h2.mon - 1;
		ts.tm_mday = h.h2.mday;
		ts.tm_hour = h.h2.hour;
		ts.tm_min = h.h2.min;
		ts.tm_sec = h.h2.sec;
		ts.tm_isdst = -1;

		time_t unix_time = mktime(&ts);

		if(unix_time > 0)
		{
			unix_time += (h.last_idx)*(h.h1.time_interv);
			entry->ts = unix_time;
		}

		/* le a proxima entrada */
		if(log_openread(filename,&fp))
		{
			pos = pos + (h.last_idx)*entry_size;

			if(log_seek(&fp,&pos))
			{
			   (void)log_read(entry->values,entry_size,&fp);
			   (void)log_close(&fp);

			   /* try to send */
			   if(log_entry_send(entry,entry_size-2) == 1) // ignore \r\n
			   {
				   /* if ok */
				   h.last_idx++; // incrementa indice da �ltima entrada lida
				   log_setheader(filename, &h);
			   }

			   return h.last_idx;
			}
		}
	}
	else
	{
		// if(h.last_idx == h.count)
		/* log is not writing in the same reading file ? */
		if(strcmp(logger_state[logger_num].log_name_reading, logger_state[logger_num].log_name_writing) != 0)
		{
			strcpy(logger_state[logger_num].log_name_reading,logger_state[logger_num].log_name_writing);
			/* update meta file */
			if(log_openwrite(LOG_METAFILE,&fp))
			{
			   if(log_write(logger_state[logger_num].log_name_reading,&fp)){;}
			   (void)log_close(&fp);
			}
		}
	}
	return 0;
}

void log_sync(char*log_fn)
{
	log_settimestamp(0, (char*)log_fn); // sincronizar
}

#if _WIN32
#include<windows.h>
#include <sys/stat.h>
#endif

/* open dir and try to open/create a new file */
uint8_t log_init(uint8_t logger_num)
{

	  LOG_DIRTYPE  d;
	  LOG_FILETYPE fp;
	  LOG_DIRINFO  dir;
	  LOG_FILEINFO fnfo;

	  strcpy(logger_state[logger_num].log_name_writing, LOG_FILENAME_START);

	  if (log_stat(logger_state[logger_num].log_dir_name, &fnfo))
	  {
		  log_mkdir(logger_state[logger_num].log_dir_name);
	  }

	  if (log_opendir(logger_state[logger_num].log_dir_name, d))
	  {
	    while (log_readdir(dir,d))
	    {
#if _WIN32
	    	PRINTF("%s\n", dir->d_name);
#else
	    	PRINTF("%s\n", (LOG_DIRINFO*)(&dir)->fname);
#endif
	    }
	    log_closedir(d);
	  }else
	  {
		  print_erro("Log init erro: %d", logger_num);
		  return 1;
	  }

	 /* change to log dir */
	 log_chdir(logger_state[logger_num].log_dir_name);

     /* try open log or create it now */
	 if(log_openread(logger_state[logger_num].log_name_writing,&fp))
	 {
	   (void)log_close(&fp);
	 }else
	 {
	   if(log_openwrite(logger_state[logger_num].log_name_writing,&fp))
	   {
		   log_newheader(logger_state[logger_num].log_name_writing,0,
				   logger_state[logger_num].config_h.time_interv,
				   logger_state[logger_num].config_h.entry_size);
		   (void)log_close(&fp);
	   }
	 }

     /* try open metalog or create a new one */
	 if(log_openread(LOG_METAFILE,&fp))
	 {
		 if(log_read(logger_state[logger_num].log_name_reading,FILENAME_MAX_LENGTH,&fp))
		 {
			 logger_state[logger_num].log_name_reading[FILENAME_MAX_LENGTH-1] = '\0'; // null terminate
			 (void)log_close(&fp);

			 // check if the file exists
			 if(log_openread(logger_state[logger_num].log_name_reading,&fp))
			 {
				 (void)log_close(&fp);
			 }
			 else
			 {
				 (void)log_close(&fp);
				 goto fail_to_open_log_reader;
			 }
		 }else
		 {
			 (void)log_close(&fp);
			 goto fail_to_open_log_reader;
		 }

	 }else
	 {
	   fail_to_open_log_reader:
	   if(log_openwrite(LOG_METAFILE,&fp))
	   {
		   strcpy(logger_state[logger_num].log_name_reading,logger_state[logger_num].log_name_writing);
		   if(log_write(logger_state[logger_num].log_name_writing,&fp)){;}
		   (void)log_close(&fp);
	   }
	 }

	 /* change to parent dir */
	 log_chdir("..");
	 return 0;
}

char* log_getfilename_to_write(uint8_t logger_num)
{
	return logger_state[logger_num].log_name_writing;
}

char* log_getfilename_to_read(uint8_t logger_num)
{
	return logger_state[logger_num].log_name_reading;
}

void monitor_writeentry(INT8U monitor_num)
{
	char string[20];
	uint16_t cnt = 0;
	
#if MONITOR_TESTS
	uint16_t vetor_dados[3]={0x1111,0x2222,0x3333};	
	log_createentry(string,vetor_dados,3);

	assert((string[0] == '1') && (string[1]== '1') && (string[2] == '1') && (string[3]== '1') &&
			(string[0+4] == '2') && (string[1+4]== '2') && (string[2+4] == '2') && (string[3+4]== '2') &&
			(string[0+2*4] == '3') && (string[1+2*4]== '3') && (string[2+2*4] == '3') && (string[3+2*4]== '3'));

#endif		

	/* change to log dir */
	log_chdir(logger_state[monitor_num].log_dir_name);
	cnt = log_writeentry(log_getfilename_to_write(monitor_num),string);

	/* change to parent dir */
	log_chdir("..");

	PRINTF("Entry written %d\r\n", cnt);
}

void monitor_readentry(INT8U monitor_num)
{
	log_entry_t entry;
	uint8_t string[20];
	uint32_t nread;
	char buffer[sizeof(long)*8+1];

	char* fname = log_getfilename_to_read(monitor_num);
	entry.values = string;

	/* change to log dir */
	log_chdir(logger_state[monitor_num].log_dir_name);

	if((nread = log_readentry(monitor_num, fname, &entry)) != 0)
	{
		if( nread < MAX_NUM_OF_ENTRIES)
		{
			PRINTF((char*)entry.values);
			PRINTF(ltoa((long)entry.ts,buffer,10));
		}
	}

	/* change to parent dir */
	log_chdir("..");

}




