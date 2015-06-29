/*
 * printf.h
 *
 *  Created on: 06/10/2011
 *      Author: gustavo
 */

#ifndef PRINTF_COLDUINO_H_
#define PRINTF_COLDUINO_H_

int printf_colduino(const char *format, ...);
int sprintf_colduino(char *out, const char *format, ...);
int snprintf_colduino( char *buf, unsigned int count, const char *format, ... );

#endif /* PRINTF_H_ */
