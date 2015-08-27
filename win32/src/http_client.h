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

uint8_t http_receive (uint8_t *, uint16_t*);
uint8_t http_send (uint8_t *, uint16_t);
uint8_t http_set_hostname (char *);
uint8_t http_set_ip(char *);

//extern const modem_driver_t win_http;

#endif /* HTTP_CLIENT_H_ */
