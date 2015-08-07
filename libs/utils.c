#include "BRTOS.h"
#include "utils.h"
#include "usb_terminal.h"
#include "uart.h"

#include <stdlib.h>
#include <string.h>

#pragma warn_implicitconv off


void printSer(INT8U SerialPort, CHAR8 *string)
{
	switch(SerialPort)
	{
	  case USE_UART1:
	    #if (ENABLE_UART1 == TRUE)
	    printf_uart1(string);
	    #endif
	    break;
	  case USE_UART2:
	    #if (ENABLE_UART2 == TRUE)
	    printf_uart2(string);
	    #endif	  
	    break;
	  case USE_USB:
	    printf_usb(string);
	    break;	    	    
	  default:
	    break;
	}
}


void putcharSer(INT8U SerialPort, CHAR8 caracter)
{
	switch(SerialPort) 
	{
	  case USE_UART1:
	    #if (ENABLE_UART1 == TRUE)
	    putchar_uart1(caracter);
	    #endif
	    break;
	  case USE_UART2:
	    #if (ENABLE_UART2 == TRUE)
	    putchar_uart2(caracter);
	    #endif	  
	    break;
	  case USE_USB:
	    putchar_usb(caracter);
	    break;	    	    
	  default:
	    break;
	}	
}

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

#if 1
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
#endif

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
