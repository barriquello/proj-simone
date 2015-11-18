/*
 * printf.h
 *
 *  Created on: 06/10/2011
 *      Author: gustavo
 */

#ifndef PRINTF_LIB_H_
#define PRINTF_LIB_H_

#include "AppConfig.h"

int printf_lib(const char *format, ...);
int sprintf_lib(char *out, const char *format, ...);
int snprintf_lib( char *buf, unsigned int count, const char *format, ... );
int vsprintf_lib(char *out, const char *format, ...);

#if COLDUINO
#define DISABLE_SNPRINTF 1
#else
#define DISABLE_SNPRINTF 0
#endif

#include <stdarg.h>
#if DISABLE_SNPRINTF
#include "terminal.h"
#include "string.h"
#define SNPRINTF(...) 		snprintf_lib(__VA_ARGS__)
#define SNPRINTF_P(...)		snprintf_lib(__VA_ARGS__)
#define VSPRINTF(...)		vsprintf_lib(__VA_ARGS__)
#define VSPRINTF_P(...)		vsprintf_lib(__VA_ARGS__)
#define VSNPRINTF(...)		vsprintf_lib(__VA_ARGS__)
#define VSNPRINTF_P(...)	vsprintf_lib(__VA_ARGS__)
#define STRCPY(a,b)		strncpy(a,b, SIZEARRAY(a))
#define STRCPY_P(a,b)	strncpy(a,b, SIZEARRAY(a))
#else
#include "stdio.h"
#ifdef __AVR__
#include "hardware.h"
#define SNPRINTF(a,b,c,...) 	snprintf(a,b,c,__VA_ARGS__)
#define SNPRINTF_P(a,b,c,...) 	snprintf_P(a,b,(PGM_P)pgm_read_word(c),__VA_ARGS__)
#define VSPRINTF(...)			vsprintf_lib(__VA_ARGS__);
#define VSPRINTF_P(...)			vsprintf_P(a,(PGM_P)pgm_read_word(b),__VA_ARGS__)
#define VSNPRINTF(a,b,c)		vsnprintf(a,sizeof(a)-1,b,c)
#define VSNPRINTF_P(a,b,c)		vsnprintf_P(a,sizeof(a)-1,b,c)
#define STRCPY(a,b)				strncpy_P(a,(PGM_P)pgm_read_word(b), SIZEARRAY(a))
#define STRCPY_P(a,b)			strncpy_P(a,b, SIZEARRAY(a))
#else
#define SNPRINTF(...) 	snprintf(__VA_ARGS__)
#define SNPRINTF_P(...) snprintf(__VA_ARGS__)
#define VSPRINTF(...)	vsprintf(__VA_ARGS__)
#define VSPRINTF_P(...)	vsprintf(__VA_ARGS__)
#define VSNPRINTF(...)	 vsprintf(__VA_ARGS__)
#define VSNPRINTF_P(...) vsprintf(__VA_ARGS__)
#define STRCPY(a,b)		strncpy(a,b, SIZEARRAY(a))
#define STRCPY_P(a,b)	strncpy(a,b, SIZEARRAY(a))
#endif

#endif

#endif /* PRINTF_H_ */
