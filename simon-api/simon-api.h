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
 * simon-api.h
 *
 *  Created on: Jul 22, 2015
 *      Author: Universidade Federal
 */

#ifndef SIMON_API_H_
#define SIMON_API_H_

#ifndef _WIN32
#include "BRTOS.h"
#endif

#include "time_lib.h"
#include "stdint.h"

#ifndef API_KEY
#define API_KEY  "90a004390f3530d0ba10199ac2b1ac3d"
#endif

#ifndef SERVER_NAME
#define SERVER_NAME "emon-gpsnetcms.rhcloud.com"
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE  1
#endif

#define MODEM_OK  (0)
#define MODEM_ERR (1)

#define MAX_HOSTNAME_LEN	 (32+1)
#define MAX_HOSTIP_LEN	 	 (15+1)
#define MAX_APIKEY_LEN	 	 (32+1)
#define MAX_GPRS_LEN		 (15+1)

typedef uint8_t (*initialize)(void);
typedef uint8_t (*input)(char *, uint16_t*);
typedef uint8_t (*output)(char *, uint16_t);
typedef uint8_t (*set_host)(char *);
typedef uint8_t (*set_ip)(char *);
typedef uint8_t (*get_connect)(void);
typedef uint8_t (*resolve_ip)(char * host, char *_ip);

typedef struct
{
	initialize init;
	input receive;
	output send;
	set_host sethost;
	set_ip   setip;
	get_connect  is_connected;
	resolve_ip  resolveip;
}modem_driver_t;

uint8_t simon_init(const modem_driver_t* modem);
uint8_t simon_get_time(struct tm * t);
uint8_t simon_send_data(uint8_t *buf, uint16_t len, uint8_t mon_id, time_t time);
uint8_t simon_send_multiple_data(uint8_t *buf, uint16_t length, time_t time);
char* simon_get_apikey(void);
char* simon_get_hostname(void);
char* simon_get_hostip(void);
void simon_set_apikey(const char*);
void simon_set_hostname(const char*);
void simon_set_hostip(const char*);
uint8_t simon_check_connection(void);
void simon_set_gprs_config(const char* gprs_cfg);


void simon_clock_update(void);
void simon_clock_set(time_t now);
time_t simon_clock_get(void);
uint8_t is_simon_clock_synched(void);
uint8_t get_server_time(char* server_reply, struct tm *ts);

#endif /* SIMON_API_H_ */
