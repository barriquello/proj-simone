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
void PrintDecimal(signed short int val, char *buff);

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
