#include "BRTOS.h"

#define NO_ALIGN    (INT8U)0
#define SPACE_ALIGN (INT8U)1
#define ZEROS_ALIGN (INT8U)2

#define USE_UART1	0
#define USE_UART2	1
#define USE_USB		2

void printSer(INT8U SerialPort, CHAR8 *string);
void putcharSer(INT8U SerialPort, CHAR8 caracter);

void reverse(char s[]);
void IntToString(int n , char str[]);
INT32U StringToInteger(char p[]);
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
void PrintDecimal(signed short int val, char *buff);
void PrintDateTime(OSDateTime *dt, CHAR8 *buff);

#define ByteSwap(A)     (A=(A<<8)+(A>>8))
INT32U LWordSwap(INT32U u32DataSwap);

