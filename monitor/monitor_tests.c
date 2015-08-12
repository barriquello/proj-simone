
#include "monitor.h"
#include "string.h"
#include "assert.h"

#ifdef _WIN32
#define DEBUG_MONITOR 1
#endif

#if DEBUG_MONITOR
#define PRINTF(...) printf(__VA_ARGS__);
#else
#define PRINTF(...)
#endif

extern log_state_t logger_state[MAX_NUM_OF_LOGGERS];

void test_openlog(INT8U logger)
{

   LOG_FILETYPE fp;
   char* filename = log_getfilename_to_write(logger);

   if(log_openread(filename,&fp))
   {
	   (void)log_close(&fp);
   }else
   {
	   if(log_openwrite(filename,&fp))
	   {
		   log_newheader(filename,0,
				   logger_state[logger].config_h.time_interv,
				   logger_state[logger].config_h.entry_size);

		   (void)log_close(&fp);
	   }
   }

}

void test_writelogts(INT8U logger)
{

	LOG_FILETYPE fp;
	char timestamp[20];
	uint16_t ret;

#if _WIN32	
    struct tm ts = *localtime(&(time_t){time(NULL)});
    strftime(timestamp,80,"T%Y%m%d%H%M%SS\r\n",&ts);
#endif
    
    puts(timestamp);

   if(log_openread(log_getfilename_to_write(logger),&fp))
   {
	   ret = log_write(timestamp,&fp);
	   (void)log_close(&fp);
	   assert(ret == 1);
   }else
   {
	   assert(0);
   }
}


void test_createentry(void)
{

	uint16_t vetor_dados[3]={0x1111,0x2222,0x3333};
	char string[20];

	log_createentry(string,vetor_dados,3);

	assert((string[0] == '1') && (string[1]== '1') && (string[2] == '1') && (string[3]== '1') &&
			(string[0+4] == '2') && (string[1+4]== '2') && (string[2+4] == '2') && (string[3+4]== '2') &&
			(string[0+2*4] == '3') && (string[1+2*4]== '3') && (string[2+2*4] == '3') && (string[3+2*4]== '3'));

}

void test_setheader(INT8U logger)
{
	log_header_t h = {{0,0,0,0},{0,0,0,0,0,0,0},0,0};
	h.h1.version = 0;
	h.h1.mon_id = 0;
	h.h1.time_interv = 30;
	h.h1.entry_size = 32;
	log_setheader(log_getfilename_to_write(logger), &h);
}

void test_getheader(INT8U logger)
{
	log_header_t h = {{0,0,0,0},{0,0,0,0,0,0,0},0,0};
	log_getheader(log_getfilename_to_write(logger), &h);
}


#if 0
void test_build_data_vector(void)
{
	char data_vector[1024];
	uint8_t vetor[]={1,2,3,11,12,23};
	build_data_vector(data_vector,vetor,6);
	puts(data_vector);
}
#endif






