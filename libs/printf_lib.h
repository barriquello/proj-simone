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
#define SNPRINTF(...) 	snprintf_lib(__VA_ARGS__)
#define VSPRINTF(...)	vsprintf_lib(__VA_ARGS__)
#define STRCPY(a,b)		strncpy(a,b, SIZEARRAY(a))
#define STRCPY_P(a,b)	strncpy(a,b, SIZEARRAY(a))
#else
#include "stdio.h"
#ifdef __AVR__
#include "hardware.h"
#define SNPRINTF(a,b,c,...) 	snprintf_P(a,b,(PGM_P)pgm_read_word(c),__VA_ARGS__)
#define VSPRINTF(...)			vsprintf_lib(__VA_ARGS__); //vsprintf_P(a,(PGM_P)pgm_read_word(b),__VA_ARGS__)
#define STRCPY(a,b)				strncpy_P(a,(PGM_P)pgm_read_word(b), SIZEARRAY(a))
#define STRCPY_P(a,b)			strncpy_P(a,b, SIZEARRAY(a))
#define PRINTF(...)			printf_lib(__VA_ARGS__);
#define PRINTS_P(s)			do{printf_terminal_P(s);}while(0);
#define PRINTC(c)			do{putchar_terminal(c);}while(0);
#define DPRINTS_P(s)		prints_P("debug.txt", s);
#define PRINT_ERRO(...)		print_R("erro.txt",__VA_ARGS__);
#define PRINT_ERRO_P(...)	print_P("erro.txt", __VA_ARGS__);
#define PRINT_ERRO_PP(s,...) prints_P("erro.txt",(PGM_P)pgm_read_word(&(s)), __VA_ARGS__);
#define PRINTS_ERRO(s)		prints_R("erro.txt",s);
#define PRINTS_ERRO_P(s)	prints_P("erro.txt",s); PRINTS_P(s);
#define PRINTS_ERRO_PP(s)	prints_P("erro.txt",(PGM_P)pgm_read_word(&(s))); PRINTS_P(s);
#else
#define SNPRINTF(...) 	snprintf(__VA_ARGS__)
#define VSPRINTF(...)	vsprintf(__VA_ARGS__)
#define STRCPY(a,b)		strncpy(a,b, SIZEARRAY(a))
#endif

#endif

#endif /* PRINTF_H_ */
