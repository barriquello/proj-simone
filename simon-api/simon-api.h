/*
 * simon-api.h
 *
 *  Created on: Jul 22, 2015
 *      Author: Universidade Federal
 */

#ifndef SIMON_API_H_
#define SIMON_API_H_

#include "BRTOS.h"
#include "time_lib.h"

#define API_KEY  "90a004390f3530d0ba10199ac2b1ac3d"
#define SERVER_NAME "emon-gpsnetcms.rhcloud.com"

#define MAX_HOSTNAME_LEN	 (32+1)
#define MAX_APIKEY_LEN	 	 (32+1)

typedef INT8U (*input)(INT8U *, INT16U *);
typedef INT8U (*output)(INT8U *, INT16U);		
typedef INT8U (*set_host)(CHAR8 *);

INT8U simon_init(input _in, output _out, set_host sethost);
INT8U simon_get_time(struct tm * t);
INT8U simon_send_data(INT8U *buf, INT16U len);
char* simon_get_apikey(void);
char* simon_get_hostname(void);
void simon_set_apikey(char*);
void simon_set_hostname(char*);

#endif /* SIMON_API_H_ */
