/*
 * http_client.h
 *
 *  Created on: Aug 12, 2015
 *      Author: Universidade Federal
 */

#ifndef HTTP_CLIENT_H_
#define HTTP_CLIENT_H_

#include <time.h>
#include <string.h>
#include "stdint.h"

uint8_t http_send_data(char *data, uint8_t len);
uint8_t http_get_time(struct tm *t);

#if _WIN32
uint8_t dns_get_ipaddress(char* ip, char *hostname);
#endif

#endif /* HTTP_CLIENT_H_ */
