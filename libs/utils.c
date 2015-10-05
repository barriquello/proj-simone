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

#include "AppConfig.h"

#ifndef _WIN32
#include "BRTOS.h"
#endif

#include "utils.h"

#include "printf_lib.h"
#include <stdlib.h>
#include <string.h>


#if !__GNUC__
#pragma warn_implicitconv off
#endif

/* reverse:  reverse string s in place */
void reverse(char s[])
{
	int i, j;
	char c;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}


uint32_t StringToInteger(char p[])
{
	uint32_t k = 0;
	while (*p)
	{
		k = (k << 3) + (k << 1) + (*p) - '0';
		p++;
	}
	return k;
}

#if 0
/* conv inteiro n para string s */
void IntToString(int n, char s[])
{
	int i;
	i = 0;
	do
	{
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	s[i] = '\0';
	reverse(s);
}
#endif

#if COLDUINO
char *ltoa(long N, char *str, int base)
{
	  #define BUFSIZE (sizeof(long) * 8 + 1)
 	  register int i = 2;
      long uarg;
      char *tail, *head = str, buf[BUFSIZE];

      if (36 < base || 2 > base)
            base = 10;                    /* can only use 0-9, A-Z        */
      tail = &buf[BUFSIZE - 1];           /* last character position      */
      *tail-- = '\0';

      if (10 == base && N < 0L)
      {
            *head++ = '-';
            uarg    = -N;
      }
      else  uarg = N;

      if (uarg)
      {
            for (i = 1; uarg; ++i)
            {
                  register ldiv_t r;

                  r       = ldiv(uarg, base);
                  *tail-- = (char)(r.rem + ((9L < r.rem) ?
                                  ('A' - 10L) : '0'));
                  uarg    = r.quot;
            }
      }
      else  *tail-- = '0';

      memcpy(head, ++tail, i);
      return str;
}
#endif

uint32_t LWordSwap(uint32_t u32DataSwap)
{
	uint32_t u32Temp;
	u32Temp = (u32DataSwap & 0xFF000000) >> 24;
	u32Temp += (u32DataSwap & 0xFF0000) >> 8;
	u32Temp += (u32DataSwap & 0xFF00) << 8;
	u32Temp += (u32DataSwap & 0xFF) << 24;
	return (u32Temp);
}

#if 0
void PrintDecimal(INT16S val, char *buff)
{
	uint16_t backup;
	uint32_t i = 0;
	char s = ' ';

	// Fill buffer with spaces
	for (i = 0; i < 6; i++)
	{
		*(buff + i) = ' ';
	}

	// Null termination for data
	*(buff + i) = 0;

	if (val < 0)
	{
		val = -val;
		s = '-';
	}

	// Convert binary value to decimal ASCII
	for (i = 5; i > 0;)
	{
		backup = val;
		val /= 10;
		*(buff + i) = (backup - (val * 10)) + '0';
		i--;

		if (val == 0)
			break;
	}

	// Completes the string for sign information
	*(buff + i) = s;  // Sign character
}

void Print4Digits(uint16_t number, uint8_t align, char *buff)
{
	uint8_t caracter = 0;
	uint8_t mil, cent, dez;
	uint8_t escreve_zero = FALSE;
	uint32_t i = 0;

	if (number < 10000)
	{
		if (align == ZEROS_ALIGN)
		{
			escreve_zero = TRUE;
		}

		mil = (number / 1000);

		caracter = mil + '0';

		if (caracter != '0')
		{
			*(buff + i) = caracter;
			i++;
			escreve_zero = TRUE;
		}
		else
		{
			if (escreve_zero == TRUE)
			{
				*(buff + i) = caracter;
				i++;
			}
			else
			{
				if (align == SPACE_ALIGN)
				{
					*(buff + i) = ' ';
					i++;
				}
			}
		}

		cent = ((number - mil * 1000) / 100);
		caracter = cent + '0';
		if (caracter != '0')
		{
			*(buff + i) = caracter;
			i++;
			escreve_zero = TRUE;
		}
		else
		{
			if (escreve_zero == TRUE)
			{
				*(buff + i) = caracter;
				i++;
			}
			else
			{
				if (align == SPACE_ALIGN)
				{
					*(buff + i) = ' ';
					i++;
				}
			}
		}

		dez = ((number - 1000 * mil - cent * 100) / 10);
		caracter = dez + '0';
		if (caracter != '0')
		{
			*(buff + i) = caracter;
			i++;
		}
		else
		{
			if (escreve_zero == TRUE)
			{
				*(buff + i) = caracter;
				i++;
			}
			else
			{
				if (align == SPACE_ALIGN)
				{
					*(buff + i) = ' ';
					i++;
				}
			}
		}

		caracter = (number % 10) + '0';
		*(buff + i) = caracter;
		i++;
		*(buff + i) = 0;
	}
}

void Print3Digits(uint16_t number, uint8_t align, char *buff)
{
	uint8_t caracter = 0;
	uint8_t cent, dez;
	uint8_t escreve_zero = FALSE;
	uint32_t i = 0;

	if (number < 1000)
	{
		if (align == ZEROS_ALIGN)
		{
			escreve_zero = TRUE;
		}

		cent = (number / 100);
		caracter = cent + '0';

		if (caracter != '0')
		{
			*(buff + i) = caracter;
			i++;
			escreve_zero = TRUE;
		}
		else
		{
			if (escreve_zero == TRUE)
			{
				*(buff + i) = caracter;
				i++;
			}
			else
			{
				if (align == SPACE_ALIGN)
				{
					*(buff + i) = ' ';
					i++;
				}
			}
		}

		dez = ((number - cent * 100) / 10);
		caracter = dez + '0';

		if (caracter != '0')
		{
			*(buff + i) = caracter;
			i++;
			escreve_zero = TRUE;
		}
		else
		{
			if (escreve_zero == TRUE)
			{
				*(buff + i) = caracter;
				i++;
			}
			else
			{
				if (align == SPACE_ALIGN)
				{
					*(buff + i) = ' ';
					i++;
				}
			}
		}

		caracter = (number % 10) + '0';
		*(buff + i) = caracter;
		i++;
		*(buff + i) = 0;
	}
}

void Print2Digits(uint8_t number, uint8_t align, char *buff)
{
	uint8_t caracter = 0;
	uint8_t dez;
	uint8_t escreve_zero = FALSE;
	uint32_t i = 0;

	if (number < 100)
	{
		if (align == ZEROS_ALIGN)
		{
			escreve_zero = TRUE;
		}

		dez = number / 10;
		caracter = dez + '0';

		if (caracter != '0')
		{
			*(buff + i) = caracter;
			i++;
			escreve_zero = TRUE;
		}
		else
		{
			if (escreve_zero == TRUE)
			{
				*(buff + i) = caracter;
				i++;
			}
			else
			{
				if (align == SPACE_ALIGN)
				{
					*(buff + i) = ' ';
					i++;
				}
			}
		}

		caracter = (number % 10) + '0';
		*(buff + i) = caracter;
		i++;
		*(buff + i) = 0;
	}
}
#else
#include "stdio.h"
void PrintDecimal(int16_t val, char *buff)
{	
	SNPRINTF(buff,5,"%d",val);
}

#ifndef UNUSED
#define UNUSED(x)		(void)(x);
#endif

void Print2Digits(uint8_t number, uint8_t align, char *buff)
{
	UNUSED(align);
	SNPRINTF(buff,2,"%d",number);
}

void Print3Digits(unsigned short int number, unsigned char align, char *buff)
{
	UNUSED(align);
	SNPRINTF(buff,3,"%d",number);
}

void Print4Digits(unsigned short int number, unsigned char align, char *buff)
{
	UNUSED(align);
	SNPRINTF(buff,4,"%d",number);
}
#endif

#ifndef _WIN32
// formato yyyymmddhhmmss
void PrintDateTime(OSDateTime *dt, char *buff)
{
	Print4Digits(dt->date.RTC_Year,ZEROS_ALIGN, &buff[0]);
	Print2Digits(dt->date.RTC_Month,ZEROS_ALIGN, &buff[4]);
	Print2Digits(dt->date.RTC_Day,ZEROS_ALIGN, &buff[6]);
	Print2Digits(dt->time.RTC_Hour,ZEROS_ALIGN, &buff[8]);
	Print2Digits(dt->time.RTC_Minute,ZEROS_ALIGN, &buff[10]);
	Print2Digits(dt->time.RTC_Second,ZEROS_ALIGN, &buff[12]);
}
#endif

#if 0
int strcmp(char s1[], char s2[])
{
	for (; *s1 == *s2; s1++, s2++)
	{
		if (*s1 == '\0')
		{
			return 0;
		}
	}
	return *s1 - *s2;
}

void strcpy(char dest[], char src[])
{
	unsigned i;
	for (i = 0; src[i] != '\0'; ++i)
		dest[i] = src[i];
	dest[i] = '\0';
}

void strcat(char dest[], char src[])
{
	uint8_t i, j;
	for (i = 0; dest[i] != '\0'; i++);
	for (j = 0; src[j] != '\0'; j++)
		dest[i + j] = src[j];
	dest[i + j] = '\0';
}

int strlen(char *str)
{
	char *s;
	for (s = str; *s; ++s);
	return (s - str);
}

#include <stddef.h>
#include <string.h>

char * strtok_r(char *s, const char *delim, char **last)
{
    char *spanp;
    int c, sc;
    char *tok;

    if (s == NULL && (s = *last) == NULL)
    {
        return NULL;
    }

    /*
     * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
     */
cont:
    c = *s++;
    for (spanp = (char *)delim; (sc = *spanp++) != 0; )
    {
        if (c == sc)
        {
            goto cont;
        }
    }

    if (c == 0)		/* no non-delimiter characters */
    {
        *last = NULL;
        return NULL;
    }
    tok = s - 1;

    /*
     * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
     * Note that delim must have one NUL; we stop if we see that, too.
     */
    for (;;)
    {
        c = *s++;
        spanp = (char *)delim;
        do
        {
            if ((sc = *spanp++) == c)
            {
                if (c == 0)
                {
                    s = NULL;
                }
                else
                {
                    char *w = s - 1;
                    *w = '\0';
                }
                *last = s;
                return tok;
            }
        }
        while (sc != 0);
    }
    /* NOTREACHED */
}


char * strtok(char *s, const char *delim)
{
    static char *last;

    return strtok_r(s, delim, &last);
}
#endif


char tohex(uint8_t val)
{
	if(val>15) val = 15;

	if(val>9)
	{
		return ((val-10) + 'A');
	}else
	{
		return (val + '0');
	}
}

char tobcd(uint8_t val)
{
	if(val>9) val = 9;
	return (val + '0');
}

void byte2hex(char *ret, uint8_t c)
{
	ret[0] = tohex((c>>4)&0x0F);
	ret[1] = tohex(c&0x0F);
}

void int2hex(char *ret, uint16_t c)
{
	byte2hex(ret,(uint8_t)(c>>8)&0xFF);
	byte2hex(ret+2,(uint8_t)(c)&0xFF);
}

void u8tobcd(char *ret, uint8_t c)
{
	uint8_t d;
	while(c>100){c-=100;} // keep below 99
	d = (c/10);
	ret[0] = tobcd(d);
	ret[1] = tobcd(c-d*10);
}


uint8_t hex2val(char c)
{
	if(c >= 'A' && c <= 'F') return (c - 'A' + 10);
	if(c >= '0' && c <= '9') return (c - '0');
	return 0; // 0 for any other case
}

uint8_t hex2byte(char c1, char c2)
{
	return (hex2val(c1)*16 + hex2val(c2));
}

uint16_t byte2int(uint8_t c1, uint8_t c2)
{
	return (uint16_t)(c1*256 + c2);
}
