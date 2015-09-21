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

extern monitor_state_t monitor_state[MAX_NUM_OF_MONITORES];

static void test_openlog(uint8_t logger)
{

   LOG_FILETYPE fp;
   char* filename = monitor_getfilename_to_write(logger);

   if(monitor_openread(filename,&fp))
   {
	   (void)monitor_close(&fp);
   }else
   {
	   if(monitor_openwrite(filename,&fp))
	   {
		   monitor_newheader(filename,0,
				   monitor_state[logger].config_h.time_interv,
				   monitor_state[logger].config_h.entry_size);

		   (void)monitor_close(&fp);
	   }
   }

}

static void test_writelogts(uint8_t logger)
{

	LOG_FILETYPE fp;
	char timestamp[20];
	int ret;

#if _WIN32	
    struct tm ts = *localtime(&(time_t){time(NULL)});
    strftime(timestamp,80,"T%Y%m%d%H%M%SS\r\n",&ts);    
    puts(timestamp);
#endif    

   if(monitor_openread(monitor_getfilename_to_write(logger),&fp))
   {
	   ret = monitor_write(timestamp,&fp);
	   (void)monitor_close(&fp);
	   assert(ret == 1);
   }else
   {
	   assert(0);
   }
}


static void test_createentry(void)
{

	uint16_t vetor_dados[3]={0x1111,0x2222,0x3333};
	char string[20];

	monitor_createentry(string,vetor_dados,3);

	assert((string[0] == '1') && (string[1]== '1') && (string[2] == '1') && (string[3]== '1') &&
			(string[0+4] == '2') && (string[1+4]== '2') && (string[2+4] == '2') && (string[3+4]== '2') &&
			(string[0+2*4] == '3') && (string[1+2*4]== '3') && (string[2+2*4] == '3') && (string[3+2*4]== '3'));

}

static void test_setheader(uint8_t logger)
{
	monitor_header_t h = {{0,0,0,0},{0,0,0,0,0,0,0},0,0};
	h.h1.version = 0;
	h.h1.mon_id = 0;
	h.h1.time_interv = 30;
	h.h1.entry_size = 32;
	monitor_setheader(monitor_getfilename_to_write(logger), &h);
}

static void test_getheader(uint8_t logger)
{
	monitor_header_t h = {{0,0,0,0},{0,0,0,0,0,0,0},0,0};
	monitor_getheader(monitor_getfilename_to_write(logger), &h);
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






