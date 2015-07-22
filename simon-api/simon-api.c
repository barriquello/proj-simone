/*
 * simon-api.c
 *
 *  Created on: Jul 22, 2015
 *      Author: Universidade Federal
 */


#include "simon-api.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

void get_server_time(char* server_reply, struct tm *ts);
INT8U get_server_confirmation(char* server_reply);

#define API_KEY  "90a004390f3530d0ba10199ac2b1ac3d"
#define SERVER_NAME "emon-gpsnetcms.rhcloud.com"

static input in = NULL;
static output out = NULL;

//static unsigned char (*putch)(char);

static char message[1024];
static char server_reply[1024];
int recv_size;
static char* hostname = SERVER_NAME;

INT8U simon_init(input _in, output _out, set_host sethost)
{
	in = _in;
	out = _out;
	sethost(hostname);	
	return OK;
}

INT8U simon_get_time(struct tm * t)
{
	char* get_time_request = "GET /time/local&apikey=%s";
	
	snprintf(message, 1024,
		     "%s HTTP/1.1\r\n"
		     "Host: %s\r\n"
		     "\r\n\r\n", get_time_request, hostname);
	
	if(out == NULL || in == NULL)
	{
		return !OK;
	}
	if(out(message , strlen(message)) != 0)
	{
		return !OK;
	}
	if(in(server_reply , &recv_size) != 0)
	{
		return !OK;
	}
	
	/* Add a NULL terminating character to make it a proper string */
	server_reply[recv_size] = '\0';
	
	/* set time */
	get_server_time(server_reply, t);	
	return OK;	
}

INT8U simon_send_data(INT8U *buf, INT16U len)
{
	char* send_monitor = "GET /monitor/set.json?monitorid=%d&data=%s&apikey=%s";
	
	snprintf(server_reply, 1024, send_monitor, buf[0], &buf[1], API_KEY);
	
	/// Form request
	snprintf(message, 1024,
		     "%s HTTP/1.1\r\n"
		     "Host: %s\r\n"
		     "\r\n\r\n", server_reply, hostname);
	
	if(out == NULL || in == NULL)
	{
		return !OK;
	}
	if(out(message , strlen(message)) != 0)
	{
		return !OK;
	}
	if(in(server_reply , &recv_size) != 0)
	{
		return !OK;
	}
	server_reply[recv_size] = '\0';
	
	return get_server_confirmation(server_reply);
}

INT8U get_server_confirmation(char* server_reply)
{
	/* search server confirmation: HTTP 200 OK */
	return OK;
}

static const char *abmon[12] =
{
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

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
			while (strcmp (abmon[t.tm_mon],mon) != 0)
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
		printf( " %s\n", token );
		token = strtok(NULL, " ");
	}

	if (mktime(&t) < 0) {;}
	(*ts) = t;

	
}
