/******************************************************************************/
/* data_types.h                                                               */
/******************************************************************************/

#ifndef __DATA_TYPES_H
#define __DATA_TYPES_H

#include "stdint.h"

#define _STDINT_H	1

#ifndef _STDINT_H
/******************************************************************************/
/*                            Data types                                      */
/******************************************************************************/
typedef signed char             int8_t;
typedef unsigned char           uint8_t;
typedef short                   int16_t;
typedef unsigned short          uint16_t;
typedef signed int              int32_t;
typedef unsigned int            uint32_t;
#endif

typedef signed char             sint8_t;
typedef signed short            sint16_t;
typedef unsigned int            bool_t;
typedef signed int              sint32_t;
typedef long                    long32_t;
typedef unsigned long           ulong32_t;
typedef signed long             sling32_t;
typedef float                   float32_t;
typedef double                  float64_t;
#define TRUE_T                  (1)
#define FALSE_T                 (0)

#ifndef NULL
#define NULL 					((void*)0L)
#endif


typedef union
{
    uint32_t  data32;
    sint32_t  sdata32;
    float32_t dataF;
    uint16_t  data16[2];
    uint8_t   data8[4];
} __UNION_DWORD;

#endif
