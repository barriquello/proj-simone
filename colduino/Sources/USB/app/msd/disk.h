/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file disk.h
 *
 * @author 
 *
 * @version 
 *
 * @date May-08-2009
 *
 * @brief The file contains Macro's and functions needed by the disk 
 *        application
 *
 *****************************************************************************/


#ifndef _DISK_H
#define _DISK_H  1

#include "user_config.h"

#if RAM_DISK_APP
  #include "usb_msc.h"
#elif SD_CARD_APP
 #ifdef __MCF52xxx_H__
  #include "SD_cfv2.h"
 #else 
	#if (defined __MK_xxx_H__)
		#include "SD_kinetis.h"
	#else
		#include "SD.h"
	#endif
 #endif 
#endif  

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define USB_CONTROLLER_ID       		(0)
#define LOGICAL_UNIT_SUPPORTED          (1)

/*****************************************************************************
 * Global variables
 *****************************************************************************/
 
/******************************************************************************
 * Types
 *****************************************************************************/
#pragma pack(1)

typedef struct _disk_variable_struct
{
	uint_8 app_controller_ID;
	boolean start_app;
	uint_8 disk_lock;
}DISK_GLOBAL_VARIABLE_STRUCT, *PTR_DISK_GLOBAL_VARIABLE_STRUCT; 

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
extern void MSD_Init(void);
extern void MSD_Task(void);
extern void Disk_App(void);

#endif


/* EOF */
