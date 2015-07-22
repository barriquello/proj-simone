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

typedef INT8U (*input)(INT8U *, INT16U *);
typedef INT8U (*output)(INT8U *, INT16U);		
typedef INT8U (*set_host)(CHAR8 *);

INT8U simon_init(input _in, output _out, set_host sethost);
INT8U simon_get_time(struct tm * t);
INT8U simon_send_data(INT8U *buf, INT16U len);

#endif /* SIMON_API_H_ */
