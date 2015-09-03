/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*-------------------------------------------*/

#ifndef _FF_INTEGER
#define _FF_INTEGER

#ifdef _WIN32	/* FatFs development platform */

#include <windows.h>
#include <tchar.h>

#else			/* Embedded platform */
#include "stdint.h"
/* This type MUST be 8 bit */
typedef uint8_t			BYTE;
typedef char			CHAR;
typedef unsigned char	UCHAR;

/* These types MUST be 16 bit */
typedef int16_t			SHORT;
typedef uint16_t		USHORT;
typedef uint16_t		WORD;
typedef uint16_t		WCHAR;

/* These types MUST be 16 bit or 32 bit */
typedef int				INT;
typedef unsigned int	UINT;

/* These types MUST be 32 bit */
typedef int32_t			LONG;
typedef uint32_t		DWORD;
typedef uint32_t		ULONG;

#endif

#endif
