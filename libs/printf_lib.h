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

#endif /* PRINTF_H_ */
