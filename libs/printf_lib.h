/*
 * printf.h
 *
 *  Created on: 06/10/2011
 *      Author: gustavo
 */

#ifndef PRINTF_LIB_H_
#define PRINTF_LIB_H_

int printf_lib(const char *format, ...);
int sprintf_lib(char *out, const char *format, ...);
int snprintf_lib( char *buf, unsigned int count, const char *format, ... );
int vsprintf_lib(char *out, const char *format, ...);

#include <stdarg.h>
#ifndef _WIN32
#define SNPRINTF(...) 	snprintf_lib(__VA_ARGS__)
#define VSPRINTF(...)	vsprintf_lib(__VA_ARGS__)
#else
#include "stdio.h"
#define SNPRINTF(...) 	snprintf(__VA_ARGS__)
#define VSPRINTF(...)	vsprintf(__VA_ARGS__)
#endif

#endif /* PRINTF_H_ */
