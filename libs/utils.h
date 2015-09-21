/* The License
 * 
 * Copyright (c) 2015 Universidade Federal de Santa Maria
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.

*/
#ifndef _WIN32
#include "BRTOS.h"
#endif

#include "stdint.h"

#define NO_ALIGN    (INT8U)0
#define SPACE_ALIGN (INT8U)1
#define ZEROS_ALIGN (INT8U)2

void utils_tests(void);

void reverse(char s[]);
void IntToString(int n , char str[]);
uint32_t StringToInteger(char p[]);
char *ltoa(long N, char *str, int base);

#if 0
// string.h
int strlen(char str[]);
void strcat(char dest[],  char src[]);
void strcpy(char dest[], char src[]);
int strcmp (char s1[] , char s2[]);
#endif

void Print4Digits(unsigned short int number, unsigned char align, char *buff);
void Print3Digits(unsigned short int number, unsigned char align, char *buff);
void Print2Digits(unsigned char number, unsigned char align, char *buff);
void PrintDecimal(int16_t val, char *buff);

#ifndef _WIN32
void PrintDateTime(OSDateTime *dt, char *buff);
#endif

#define ByteSwap(A)     (A=(A<<8)+(A>>8))

uint32_t LWordSwap(uint32_t u32DataSwap);

char tohex(uint8_t val);
char tobcd(uint8_t val);
void u8tobcd(char *ret, uint8_t c);
uint8_t hex2val(char c);

void byte2hex(char *ret, uint8_t c);
void int2hex(char *ret, uint16_t c);
uint8_t hex2byte(char c1, char c2);
uint16_t byte2int(uint8_t c1, uint8_t c2);



/******************************************************************************/
/*                               Macros                                       */
/******************************************************************************/
#define BIT_SET(slovo, bit)     ((slovo) |= (1 << (bit)))
#define BIT_CLEAR(slovo, bit)   ((slovo) &= ~( 1 << (bit)))
#define BIT_TEST(slovo, bit)    ((slovo) & ( 1 << (bit)))
#define BIT_TOG(slovo, bit)     ((slovo) ^= (bit))
#define MAX(a, b)               (((a) > (b)) ? (a):(b))
#define MIN(a, b)               (((a) < (b)) ? (a):(b))
#define SIZEARRAY(a)            (sizeof(a) / sizeof(a[0]))
