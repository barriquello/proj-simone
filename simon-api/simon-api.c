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

#define STDIO
#ifdef STDIO
#include <stdio.h>
#endif

#ifdef _WIN32
#include "stdint.h"
#endif

void get_server_time(char* server_reply, struct tm *ts);
uint8_t get_server_confirmation(char* server_reply);

static input in = NULL;
static output out = NULL;

#if DEBUG_SIMON
#define PRINTF(...) printf(__VA_ARGS__);
#else
#define PRINTF(...)
#endif

char simon_hostname[MAX_HOSTNAME_LEN];
char simon_apikey[MAX_APIKEY_LEN];

static char message[1024];
static char server_reply[1024];
static char* hostname = SERVER_NAME;
uint16_t recv_size;

uint8_t simon_init(input _in, output _out, set_host sethost, set_ip setip)
{
	in = _in;
	out = _out;		
	simon_set_apikey(API_KEY);		/* set a default key */
	simon_set_hostname(SERVER_NAME); /* set a default server */
	sethost(hostname);
	setip("54.173.137.93"); /* set a default ip */
	return OK;
}

uint8_t simon_get_time(struct tm * t)
{
	char* get_time_request = "GET /time/local&apikey=%s";
	
	SNPRINTF(message, 1024,
		     "%s HTTP/1.1\r\n"
		     "Host: %s\r\n"
		     "\r\n\r\n", get_time_request, hostname);
	
	if(out == NULL || in == NULL)
	{
		return !OK;
	}
	if(out(message , (uint16_t)strlen(message)) != 0)
	{
		return !OK;
	}
	if(in(server_reply , (uint16_t)&recv_size) != 0)
	{
		return !OK;
	}
	
	/* Add a NULL terminating character to make it a proper string */
	server_reply[recv_size] = '\0';
	
	/* set time */
	get_server_time(server_reply, t);	
	return OK;	
}

uint8_t simon_send_data(uint8_t *buf, uint16_t len)
{
	char* send_monitor = "GET /monitor/set.json?monitorid=%d&data=%s&apikey=%s";
	
	SNPRINTF(server_reply, 1024, send_monitor, buf[0], &buf[1], API_KEY);
	
	/// Form request
	SNPRINTF(message, 1024,
		     "%s HTTP/1.1\r\n"
		     "Host: %s\r\n"
		     "\r\n\r\n", server_reply, hostname);
	
	if(out == NULL || in == NULL)
	{
		return !OK;
	}
	if(out(message, (uint16_t)strlen(message)) != 0)
	{
		return !OK;
	}
	if(in(server_reply , (uint16_t*) &recv_size) != 0)
	{
		return !OK;
	}
	server_reply[recv_size] = '\0';
	
	return get_server_confirmation(server_reply);
}

uint8_t get_server_confirmation(char* server_reply)
{
	/* search server confirmation: HTTP 200 OK */
	return OK;
}

#include "time_lib.h"

void get_server_time(char* server_reply, struct tm *ts)
{
	
	char *ret;
	char *token;
	int k = 0;
	char mon[4];
	struct tm t;
	
	ret = strstr(server_reply, "Date:");	
	token = strtok(ret, " ");	

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

	if (mktime(&t) < 0) {;}
	(*ts) = t;	
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

