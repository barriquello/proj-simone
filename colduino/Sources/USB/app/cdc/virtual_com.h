/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file virtual_com.h
 *
 * @author 
 *
 * @version 
 *
 * @date May-28-2009
 *
 * @brief The file contains Macro's and functions required for Virtual COM  
 *        Loopback Application
 *
 *****************************************************************************/

#ifndef _VIRTUAL_COM_H
#define _VIRTUAL_COM_H

#include "types.h"
#include "BRTOS.h"


/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define  CONTROLLER_ID      (0)   /* ID to identify USB CONTROLLER */ 

#define  KBI_STAT_MASK      (0x0F)

/* 
   DATA_BUFF_SIZE should be greater than or equal to the endpoint buffer size, 
   otherwise there will be data loss. For MC9S08JS16, maximum DATA_BUFF_SIZE 
   supported is 16 Bytes
*/
#ifndef _MC9S08JS16_H
#define  DATA_BUFF_SIZE     (64+1)
#else
#define  DATA_BUFF_SIZE     (16)
#endif

/*****************************************************************************
 * Global variables
 *****************************************************************************/

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
extern void CDC_Init(void);
void cdc_process(void);
unsigned char cdc_putch(char c);
unsigned char GetStart_transactions(void);

void printf_usb(char *s);
void putchar_usb(char c);

// Declara um ponteiro para o bloco de controle da  USB
extern BRTOS_Queue *USB;

#endif 
