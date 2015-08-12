#include "BRTOS.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>

#pragma warn_implicitconv off

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

#if 0

INT32U StringToInteger(char p[])
{
	INT32U k = 0;
	while (*p)
	{
		k = (k << 3) + (k << 1) + (*p) - '0';
		p++;
	}
	return k;
}

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

INT32U LWordSwap(INT32U u32DataSwap)
{
	INT32U u32Temp;
	u32Temp = (u32DataSwap & 0xFF000000) >> 24;
	u32Temp += (u32DataSwap & 0xFF0000) >> 8;
	u32Temp += (u32DataSwap & 0xFF00) << 8;
	u32Temp += (u32DataSwap & 0xFF) << 24;
	return (u32Temp);
}

#if 0
void PrintDecimal(INT16S val, CHAR8 *buff)
{
	INT16U backup;
	INT32U i = 0;
	CHAR8 s = ' ';

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

void Print4Digits(INT16U number, INT8U align, CHAR8 *buff)
{
	INT8U caracter = 0;
	INT8U mil, cent, dez;
	INT8U escreve_zero = FALSE;
	INT32U i = 0;

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

void Print3Digits(INT16U number, INT8U align, CHAR8 *buff)
{
	INT8U caracter = 0;
	INT8U cent, dez;
	INT8U escreve_zero = FALSE;
	INT32U i = 0;

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

void Print2Digits(INT8U number, INT8U align, CHAR8 *buff)
{
	INT8U caracter = 0;
	INT8U dez;
	INT8U escreve_zero = FALSE;
	INT32U i = 0;

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
void PrintDecimal(INT16S val, CHAR8 *buff)
{	
	snprintf(buff,5,"%d",val);
}

#define UNUSED(x)		(void)(x);
void Print2Digits(INT8U number, INT8U align, CHAR8 *buff)
{
	UNUSED(align);
	snprintf(buff,2,"%d",number);
}

void Print3Digits(unsigned short int number, unsigned char align, char *buff)
{
	UNUSED(align);
	snprintf(buff,3,"%d",number);
}

void Print4Digits(unsigned short int number, unsigned char align, char *buff)
{
	UNUSED(align);
	snprintf(buff,4,"%d",number);
}
#endif

// formato yyyymmddhhmmss
void PrintDateTime(OSDateTime *dt, CHAR8 *buff)
{
	Print4Digits(dt->date.RTC_Year,ZEROS_ALIGN, &buff[0]);
	Print2Digits(dt->date.RTC_Month,ZEROS_ALIGN, &buff[4]);
	Print2Digits(dt->date.RTC_Day,ZEROS_ALIGN, &buff[6]);
	Print2Digits(dt->time.RTC_Hour,ZEROS_ALIGN, &buff[8]);
	Print2Digits(dt->time.RTC_Minute,ZEROS_ALIGN, &buff[10]);
	Print2Digits(dt->time.RTC_Second,ZEROS_ALIGN, &buff[12]);
}

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
	INT8U i, j;
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
