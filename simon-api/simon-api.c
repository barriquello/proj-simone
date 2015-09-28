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
 * simon-api.c
 *
 *  Created on: Jul 22, 2015
 *      Author: UFSM
 */


#include "simon-api.h"
#include "printf_lib.h"
#include "stdlib.h"
#include "string.h"
#include "utils.h"

#define STDIO
#ifdef STDIO
#include <stdio.h>
#endif

#ifdef _WIN32
#include "stdint.h"
#endif

#include "time_lib.h"

uint8_t get_server_time(char* server_reply, struct tm *ts);
uint8_t get_server_confirmation(char* server_reply);

static input in = NULL;
static output out = NULL;

#define DEBUG_SIMON 1
#if DEBUG_SIMON
#ifndef _WIN32
#define PRINTF(...) printf_lib(__VA_ARGS__);
#else
#define PRINTF(...) printf(__VA_ARGS__);
#endif
#else
#define PRINTF(...)
#endif

char simon_hostname[MAX_HOSTNAME_LEN];
char simon_hostip[MAX_HOSTIP_LEN];
char simon_apikey[MAX_APIKEY_LEN];

static char message[1024];
static char server_reply[1024];
static char* hostname = simon_hostname;
uint16_t recv_size;

modem_driver_t* modem = NULL;

uint8_t simon_init(const modem_driver_t* _modem)
{
	if(_modem == NULL) return MODEM_ERR;
	modem = (modem_driver_t*)_modem;
	if(modem->init() == FALSE)
	{
		PRINTF("modem not ok");
	}
	in = modem->receive;
	out = modem->send;
	simon_set_apikey(API_KEY);		/* set a default key */
	simon_set_hostname(SERVER_NAME); /* set a default server */
	modem->sethost(hostname);
	modem->setip("54.173.137.93"); /* set a default ip */
	return MODEM_OK;
}

uint8_t simon_check_connection(void)
{

	if(modem->is_connected())
	{
		return TRUE;
	}
	
	return FALSE;
}

uint8_t simon_get_time(struct tm * t)
{
	char* get_time_request = "GET /time/local&apikey=%s";
	//char* get_time_request = "GET /";
	uint8_t ret = MODEM_ERR;
	
	SNPRINTF(server_reply, SIZEARRAY(message), get_time_request, (char*)simon_apikey);
	
	SNPRINTF(message, SIZEARRAY(message),
		     "%s HTTP/1.1\r\n"
		     "Host: %s\r\n"
		     "\r\n\r\n", server_reply, hostname);
	
	//PRINTF(message);
	
	if(out == NULL || in == NULL)
	{
		return MODEM_ERR;
	}
	if(out((uint8_t*)message , (uint16_t)strlen(message)) != MODEM_OK)
	{
		return MODEM_ERR;
	}
	
	do
	{
		recv_size = SIZEARRAY(server_reply);
		if(in((uint8_t*)server_reply, (uint16_t*) &recv_size) != MODEM_OK)
		{
			break;
		}
		
		/* Add a NULL terminating character to make it a proper string */
		server_reply[recv_size-1] = '\0';
	
		if(ret == MODEM_ERR)
		{
			/* set time */
			if(get_server_time(server_reply, t) == TRUE)
			{
				ret = MODEM_OK;
			}
		}
	}while(recv_size);
	
	return MODEM_OK;
}

uint8_t simon_send_data(uint8_t *buf, uint16_t len, uint8_t mon_id, time_t time)
{
	char* send_monitor = "GET /monitor/set.json?monitorid=%d&time=%d&data=%s&apikey=%s";
	
	uint8_t ret = MODEM_ERR;
	
	if(len > SIZEARRAY(message)) return MODEM_ERR;
	
	SNPRINTF(server_reply, SIZEARRAY(message), send_monitor, mon_id, time, buf, (char*)simon_apikey);
	
	/// Form request
	SNPRINTF(message, SIZEARRAY(message),
		     "%s HTTP/1.1\r\n"
		     "Host: %s\r\n"
		     "\r\n\r\n", server_reply, hostname);

#if 0	
	PRINTF(message);
#endif	

#define SIMON_SKIP_SEND 0
#if SIMON_SKIP_SEND
	return MODEM_OK;
#endif
	
	if(out == NULL || in == NULL)
	{
		return MODEM_ERR;
	}
	
	if(out((uint8_t*)message, (uint16_t)strlen(message)) != MODEM_OK)
	{
		return MODEM_ERR;
	}

	do
	{
		recv_size = SIZEARRAY(server_reply);
		if(in((uint8_t*)server_reply, (uint16_t*) &recv_size) != MODEM_OK)
		{
			break;
		}
		server_reply[recv_size-1] = '\0';	
	
		if(ret == MODEM_ERR)
		{
			ret = get_server_confirmation(server_reply);
		}
	}while(recv_size);
	
	return ret;
}

uint8_t get_server_confirmation(char* server_reply)
{
	/* search server confirmation: HTTP 200 OK */
	char *ret;
	ret = strstr(server_reply, "HTTP/1.1 200 OK");	
	if(ret == NULL)
	{
		return MODEM_ERR;
	}
	else
	{
		return MODEM_OK;
	}	
}

uint8_t get_server_time(char* server_reply, struct tm *ts)
{
	
	char *ret;
	char *token;
	int k = 0;
	char mon[4];
	struct tm t;
	char delim[2] = " ";
	
	ret = strstr(server_reply, "Date:");
	
	if(ret == NULL) return FALSE; 
	
	token = strtok(ret,(const char*) delim);	

	for (k=0; k<6;k++)
	{
		switch(k)
		{
		case 0:
		case 1:
			break;
		case 2: if (1 != sscanf(token,"%d", &t.tm_mday)){;} // day
			break;
		case 3:
			if (1 != sscanf(token,"%s",(char*) mon)){;} // month
			t.tm_mon = 0;
			while (strcmp (_months_abbrev[t.tm_mon],mon) != 0)
			{
				++t.tm_mon;
			}
			//t.tm_mon--;
			break;
		case 4:
			if (1 != sscanf(token,"%d", &t.tm_year)){;}
			t.tm_year -= 1900;
			break;
		case 5:
			 if (3 != sscanf(token,"%d:%d:%d", &t.tm_hour, &t.tm_min, &t.tm_sec)){;}
			break;
		default:
			break;
		}
		PRINTF( " %s\n", token );
		token = strtok(NULL, " ");
	}

	if (mktime(&t) < 0) {return FALSE; }
	
	(*ts) = t;	
	return TRUE; 
}

char* simon_get_apikey(void)
{
	simon_apikey[MAX_APIKEY_LEN-1] = '\0';
	return (char*)&simon_apikey;
}

void simon_set_apikey(const char* apikey)
{
	if(apikey != NULL)
	{
		strncpy(simon_apikey,apikey,MAX_APIKEY_LEN-1);
	}
}

char* simon_get_hostname(void)
{
	simon_hostname[MAX_HOSTNAME_LEN-1] = '\0';
	return (char*)&simon_hostname;
}

void simon_set_hostname(const char* hostname)
{
	if(hostname != NULL)
	{
		strncpy(simon_hostname,hostname,MAX_HOSTNAME_LEN-1);
	}
}

void simon_set_hostip(const char* ip)
{
	if(ip != NULL)
	{
		strncpy(simon_hostip,ip,MAX_HOSTIP_LEN-1);
	}
}



