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

uint8_t get_server_time(char* _server_reply, struct tm *ts);
uint8_t get_server_confirmation(char* _server_reply);

static input in_modem = NULL;
static output out_modem = NULL;

#define DEBUG_SIMON		1
#undef PRINTS_ENABLED

#if DEBUG_SIMON
#define PRINTS_ENABLED  1
#else
#define PRINTS_ENABLED  0
#endif

#include "prints_def.h"

char simon_hostname[MAX_HOSTNAME_LEN];
char simon_hostip[MAX_HOSTIP_LEN];
char simon_apikey[MAX_APIKEY_LEN];
char simon_gprs_server[MAX_GPRS_LEN];
char simon_gprs_user[MAX_GPRS_LEN];
char simon_gprs_password[MAX_GPRS_LEN];
static char server_reply[512];

static char* hostname = simon_hostname;
uint16_t recv_size;

modem_driver_t* modem = NULL;

extern uint8_t mon_verbosity;

uint8_t simon_init(const modem_driver_t* _modem)
{
	if(_modem == NULL) return MODEM_ERR;
	modem = (modem_driver_t*)_modem;	
	in_modem = modem->receive;
	out_modem = modem->send;
	modem->sethost(hostname); /* set simon server */
	
	if(modem->init() == MODEM_OK)
	{
	
		if(modem->resolveip != NULL && modem->resolveip(hostname, simon_hostip) == MODEM_OK)
		{
			PRINTS_P(PSTR("Hostname resolved to IP: "));			
		}else
		{
			PRINTS_P(PSTR("Hostname IP not resolved, using default IP: "));
		}
		
		PRINTF((char*)simon_hostip);
		modem->setip(simon_hostip); /* set a default ip */ //"54.173.137.93"
		
		PRINTS_P(PSTR("\r\n"));				
		return MODEM_OK;
	}	
	
	PRINTS_P(PSTR("modem not ok"));	
	return MODEM_ERR;
	
}

uint8_t simon_check_connection(void)
{
	return modem->is_connected();
}

uint8_t simon_get_time(struct tm * t)
{
	uint8_t ret = MODEM_ERR;
	
	SNPRINTF_P(server_reply, SIZEARRAY(server_reply),
		     PSTR("GET /time/local&apikey=%s HTTP/1.1\r\nHost: %s\r\n\r\n\r\n"), (char*)simon_apikey, hostname);
	
	server_reply[SIZEARRAY(server_reply)-1] = '\0';
	
	if(mon_verbosity > 2)	PRINTF(server_reply);
	
	if(out_modem == NULL || in_modem == NULL)
	{
		return MODEM_ERR;
	}
	if(out_modem(server_reply , (uint16_t)strlen(server_reply)) != MODEM_OK)
	{
		return MODEM_ERR;
	}
	
	do
	{
		recv_size = SIZEARRAY(server_reply);
		if(in_modem(server_reply, (uint16_t*) &recv_size) != MODEM_OK)
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
				return MODEM_OK;
			}
		}
	}while(recv_size);
	
	return ret;
}

uint8_t simon_send_data(uint8_t *buf, uint16_t length, uint8_t mon_id, time_t time)
{

	uint8_t ret = MODEM_ERR;
	uint8_t retries = 0;
	
	if(length > SIZEARRAY(server_reply))      return MODEM_ERR;
	if(out_modem == NULL || in_modem == NULL) return MODEM_ERR;
	
	/// Form request
	SNPRINTF_P(server_reply, SIZEARRAY(server_reply)-1,
			 PSTR("GET /monitor/set.json?monitorid=%u&time=%lu&data=%s&apikey=%s HTTP/1.1\r\nHost: %s\r\n\r\n\r\n"), 
			 mon_id, time, buf, (char*)simon_apikey, (char*)hostname);
	
	server_reply[SIZEARRAY(server_reply)-1] = '\0';
	if(mon_verbosity > 2 && is_terminal_idle()) PRINTF(server_reply);

#define SIMON_SKIP_SEND 0
#if SIMON_SKIP_SEND
	return MODEM_OK;
#endif

	#define MAX_RETRIES  0
	retries = 0;
    while(out_modem(server_reply, (uint16_t)strlen(server_reply)) != MODEM_OK)
	{
		if(++retries > MAX_RETRIES)
		{
			return MODEM_ERR;
		}		
	}

	do
	{
		recv_size = SIZEARRAY(server_reply);
		if(in_modem(server_reply, (uint16_t*) &recv_size) != MODEM_OK)
		{
			break;
		}
		server_reply[recv_size-1] = '\0';	
	
		if(mon_verbosity > 4 && is_terminal_idle()) PRINTF(server_reply);
		
		if(ret == MODEM_ERR)
		{
			ret = get_server_confirmation(server_reply);
		}
	}while(recv_size);
	
	if(ret == MODEM_ERR)
	{
		PRINTS_P("Server confirmation not received\r\n");
	}
	return ret;
}

uint8_t get_server_confirmation(char* _server_reply)
{
	/* search server confirmation: HTTP 200 OK */
	char *ret;
	ret = strstr(_server_reply, "HTTP/1.1 200 OK");	
	if(ret == NULL)
	{
		return MODEM_ERR;
	}
	else
	{
		return MODEM_OK;
	}	
}

uint8_t get_server_time(char* _server_reply, struct tm *ts)
{
	
	char *ret;
	char *token;
	int k = 0;
	char mon[4];
	struct tm server_time;
	char delim[2] = " ";
	
	ret = strstr(_server_reply, "Date:");
	
	if(ret == NULL) return FALSE; 
	
	token = strtok(ret,(const char*) delim);	

	for (k=0; k<6;k++)
	{
		switch(k)
		{
		case 0:
		case 1:
			break;
		case 2: if (1 != sscanf(token,"%d", &server_time.tm_mday)){;} // day
			break;
		case 3:
			if (1 != sscanf(token,"%s",(char*) mon)){;} // month
			server_time.tm_mon = 0;
			while (strcmp(_months_abbrev[server_time.tm_mon],mon) != 0)
			{
				++server_time.tm_mon;
			}
			//t.tm_mon--;
			break;
		case 4:
			if (1 != sscanf(token,"%d", &server_time.tm_year)){;}
			server_time.tm_year -= 1900;
			break;
		case 5:
			 if (3 != sscanf(token,"%d:%d:%d", &server_time.tm_hour, &server_time.tm_min, &server_time.tm_sec)){;}
			break;
		default:
			break;
		}
		PRINTF( " %s", token );
		token = strtok(NULL, " ");
	}

	PRINTF("\r\n");

	//if (mktime(&t) < 0) {return FALSE; }
	
	(*ts) = server_time;	
	return TRUE; 
}

char* simon_get_apikey(void)
{
	simon_apikey[MAX_APIKEY_LEN-1] = '\0';
	return (char*)&simon_apikey;
}

void simon_set_apikey(const char* apikey)
{
	if(apikey == NULL) return;
	strncpy(simon_apikey,apikey,MAX_APIKEY_LEN-1);

}

char* simon_get_hostname(void)
{
	simon_hostname[MAX_HOSTNAME_LEN-1] = '\0';
	return (char*)&simon_hostname;
}

char* simon_get_hostip(void)
{
	simon_hostip[MAX_HOSTNAME_LEN-1] = '\0';
	return (char*)&simon_hostip;
}

void simon_set_hostname(const char* hostname)
{
	if(hostname == NULL) return;
	strncpy(simon_hostname,hostname,MAX_HOSTNAME_LEN-1);

}

void simon_set_hostip(const char* ip)
{
	if(ip == NULL) return;
	strncpy(simon_hostip,ip,MAX_HOSTIP_LEN-1);

}

void simon_set_gprs_config(const char* gprs_cfg)
{
	char gprs_str[4*MAX_GPRS_LEN];	
	char *token;
	if(gprs_cfg == NULL) return;

	strncpy(gprs_str,gprs_cfg,sizeof(gprs_str)-1);	
			
	token = strtok(gprs_str,",");	
	strncpy(simon_gprs_server,token,MAX_GPRS_LEN-1);
	//PRINTF( " %s\r\n", token );
		
	token = strtok(NULL, ",");
	strncpy(simon_gprs_user,token,MAX_GPRS_LEN-1);
	//PRINTF( " %s\r\n", token );
		
	token = strtok(NULL, ",");
	strncpy(simon_gprs_password,token,MAX_GPRS_LEN-1);
	//PRINTF( " %s\r\n", token );
		

}

static time_t simon_clock = 0;
static uint8_t simon_clock_synched = 0;

void simon_clock_update(void)
{	
	OS_SR_SAVE_VAR;
	OSEnterCritical();
		simon_clock++;
	OSExitCritical();
}

void simon_clock_set(time_t now)
{
	OS_SR_SAVE_VAR;
	OSEnterCritical();
		simon_clock = now;
		simon_clock_synched = 1;
	OSExitCritical();
}

time_t simon_clock_get(void)
{	
	time_t clock_copy;
	
	OS_SR_SAVE_VAR;
	OSEnterCritical();
		clock_copy = simon_clock;
	OSExitCritical();
	
	return clock_copy;
}

uint8_t is_simon_clock_synched(void)
{	
	return simon_clock_synched;
}

