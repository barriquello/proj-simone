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
	uint8_t retries = 5;
	while(retries > 0)
	{
		if(modem->is_connected())
		{
			return TRUE;
		}
		DelayTask(100);
		retries--;
	}
	
	return FALSE;
}

uint8_t simon_get_time(struct tm * t)
{
	//char* get_time_request = "GET /time/local&apikey=%s";
	char* get_time_request = "GET /";
	
	SNPRINTF(message, 1024,
		     "%s HTTP/1.1\r\n"
		     "Host: %s\r\n"
		     "\r\n\r\n", get_time_request, hostname);
	
	PRINTF(message);
	
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
			return MODEM_ERR;
		}
		
		/* Add a NULL terminating character to make it a proper string */
		server_reply[recv_size] = '\0';
	
		/* set time */
		if(get_server_time(server_reply, t) == TRUE)
		{
			return MODEM_OK;
		}
	}while(recv_size);
	
	return MODEM_OK;
}

uint8_t simon_send_data(uint8_t *buf, uint16_t len, uint8_t mon_id, time_t time)
{
	char* send_monitor = "GET /monitor/set.json?monitorid=%d&time=%d&data=%s&apikey=%s";
	
	SNPRINTF(server_reply, 1024, send_monitor, mon_id, time, buf, (char*)simon_apikey);
	
	/// Form request
	SNPRINTF(message, 1024,
		     "%s HTTP/1.1\r\n"
		     "Host: %s\r\n"
		     "\r\n\r\n", server_reply, hostname);

	PRINTF(message);

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

	recv_size = SIZEARRAY(server_reply);
	if(in((uint8_t*)server_reply, (uint16_t*) &recv_size) != MODEM_OK)
	{
		return MODEM_ERR;
	}
	server_reply[recv_size] = '\0';
	
	return get_server_confirmation(server_reply);
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

#include "time_lib.h"

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



