/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file disk.c
 *
 * @author 
 *
 * @version 
 *
 * @date May-08-2009
 *
 * @brief  RAM Disk has been emulated via this Mass Storage Demo
 *****************************************************************************/
 
/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"          /* User Defined Data Types */
#include "hidef.h"          /* for EnableInterrupts macro */
#include "derivative.h"     /* include peripheral declarations */
#include "usb_msc.h"		/* USB MSC Class Header File */
#include "disk.h"			/* Disk Application Header File */
#include "usb_class.h"
#include "sd.h"
#include "SD_API.h"

#if (USB_CLASS_TYPE == BRTOS_USB_MSD)

#ifdef __MCF52xxx_H__
 #include "Wdt_cfv2.h"
#endif 

#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H) || (defined _MCF51JE128_H)
#include "exceptions.h"
#endif

/* skip the inclusion in dependency statge */
#ifndef __NO_SETJMP
   #include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>	

/*****************************************************************************
 * Constant and Macro's - None
 *****************************************************************************/
 
/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/
void TestApp_Init(void);
extern void Watchdog_Reset(void);

/****************************************************************************
 * Global Variables
 ****************************************************************************/ 
 /* Add all the variables needed for disk.c to this structure */
DISK_GLOBAL_VARIABLE_STRUCT g_disk;
/*****************************************************************************
 * Local Types - None
 *****************************************************************************/
 
/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
void USB_App_Callback(uint_8 controller_ID,  uint_8 event_type, void* val);
void MSD_Event_Callback(uint_8 controller_ID, uint_8 event_type, void* val);
void Disk_App(void);
/*****************************************************************************
 * Local Variables 
 *****************************************************************************/

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
/******************************************************************************
 * 
 *    @name       Disk_App
 *    
 *    @brief      
 *                  
 *    @param      None
 * 
 *    @return     None
 *    
 *****************************************************************************/
void Disk_App(void)
{
    /* User Code */
	DelayTask(1000);
    return;
}

/******************************************************************************
 * 
 *    @name        USB_App_Callback
 *    
 *    @brief       This function handles the callback  
 *                  
 *    @param       controller_ID : To Identify the controller
 *    @param       event_type : value of the event
 *    @param       val : gives the configuration value 
 * 
 *    @return      None
 *
 *****************************************************************************/
void USB_App_Callback(uint_8 controller_ID, uint_8 event_type, void* val) 
{
    UNUSED (controller_ID)
    UNUSED (val)    
    if(event_type == USB_APP_BUS_RESET) 
    {
        g_disk.start_app=FALSE;    
    }
    else if(event_type == USB_APP_ENUM_COMPLETE) 
    {
        g_disk.start_app=TRUE;        
    }
    else if(event_type == USB_APP_ERROR)
    {
    	/* add user code for error handling */
    }
    
    return;
}

/******************************************************************************
 * 
 *    @name        MSD_Event_Callback
 *    
 *    @brief       This function handles the callback  
 *                  
 *    @param       controller_ID : To Identify the controller
 *    @param       event_type : value of the event
 *    @param       val : gives the configuration value 
 * 
 *    @return      None
 *
 *****************************************************************************/
void MSD_Event_Callback(uint_8 controller_ID, 
							   uint_8 event_type, 
							   void* val) 
{
	PTR_LBA_APP_STRUCT lba_data_ptr;
	uint_8_ptr prevent_removal_ptr, load_eject_start_ptr;	
	PTR_DEVICE_LBA_INFO_STRUCT device_lba_info_ptr;
    UNUSED (controller_ID)
    switch(event_type)
    {
    	case USB_APP_DATA_RECEIVED :
    		break;
    	case USB_APP_SEND_COMPLETE :
    		break;
      case USB_MSC_START_STOP_EJECT_MEDIA :
        load_eject_start_ptr = (uint_8_ptr)val;
        /* Code to be added by user for starting, stopping or 
           ejecting the disk drive. e.g. starting/stopping the motor in 
           case of CD/DVD*/
        break;
    	case USB_MSC_DEVICE_READ_REQUEST :     		
    		/* copy data from storage device before sending it on USB Bus 
    		   (Called before calling send_data on BULK IN endpoints)*/
    		lba_data_ptr = (PTR_LBA_APP_STRUCT)val;
    		/* read data from mass storage device to driver buffer */
#if RAM_DISK_APP
    		USB_memcopy(g_disk.storage_disk + lba_data_ptr->offset,
    			lba_data_ptr->buff_ptr, 
    			lba_data_ptr->size);
#elif SD_CARD_APP        
        SD_Read_Block(lba_data_ptr);
#endif         
    		break;
    	case USB_MSC_DEVICE_WRITE_REQUEST :
    		/* copy data from USb buffer to Storage device 
   		   	   (Called before after recv_data on BULK OUT endpoints)*/
    		lba_data_ptr = (PTR_LBA_APP_STRUCT)val;
    		/* read data from driver buffer to mass storage device */
#if RAM_DISK_APP
    		USB_memcopy(lba_data_ptr->buff_ptr,
    			g_disk.storage_disk + lba_data_ptr->offset,
    			lba_data_ptr->size);
#elif SD_CARD_APP
          SD_Write_Block(lba_data_ptr);
#endif          
    		break;
    	case USB_MSC_DEVICE_FORMAT_COMPLETE :
    		break;
    	case USB_MSC_DEVICE_REMOVAL_REQUEST :
    		prevent_removal_ptr = (uint_8_ptr) val;
    		if(SUPPORT_DISK_LOCKING_MECHANISM)
    		{    			 
    			g_disk.disk_lock = *prevent_removal_ptr;
    		}
    		else if((!SUPPORT_DISK_LOCKING_MECHANISM)&&(!(*prevent_removal_ptr)))
    		{
    			/*there is no support for disk locking and removal of medium is enabled*/
				/* code to be added here for this condition, if required */ 
    		}
    		break;
    	case USB_MSC_DEVICE_GET_INFO :
    		device_lba_info_ptr = (PTR_DEVICE_LBA_INFO_STRUCT)val;
#if RAM_DISK_APP
    		device_lba_info_ptr->total_lba_device_supports = TOTAL_LOGICAL_BLOCKS_ADDRESS;	
    		device_lba_info_ptr->length_of_each_lba_of_device = LENGTH_OF_EACH_LBA; 
#elif SD_CARD_APP
    		SD_Card_Info(&device_lba_info_ptr->total_lba_device_supports,
    		    &device_lba_info_ptr->length_of_each_lba_of_device);
#endif
    		device_lba_info_ptr->num_lun_supported = LOGICAL_UNIT_SUPPORTED;
    		break;    		
    	default : 
    		break;
    }
        
    return;
}

 /******************************************************************************
 *  
 *   @name        TestApp_Init
 * 
 *   @brief       This function is the entry for mouse (or other usuage)
 * 
 *   @param       None
 * 
 *   @return      None
 **                
 *****************************************************************************/
 
void MSD_Init(void)
{       
    uint_8   error;
    uint_8   status = 0;
    
    
    /* initialize the Global Variable Structure */
	  USB_memzero(&g_disk, sizeof(DISK_GLOBAL_VARIABLE_STRUCT));
    g_disk.app_controller_ID = USB_CONTROLLER_ID;

    UserEnterCritical();
    #if (defined _MCF51MM256_H) || (defined _MCF51JE256_H) || (defined _MCF51JE128_H)
     usb_int_dis();
    #endif
	
#if SD_CARD_APP 
	PTGDD_PTGDD0 = 0;           /* PTG0 is input*/
	PTGPE_PTGPE0 = 1;           /* internal pullup for PTG0 */
	
	_SD_PRESENT = 0;                 /* Card detection */
	SD_PRESENT_PULLUP = 1;
	
	_SD_WP = 0;                 /* Write protect */
	SD_WP_PULLUP = 1;

    do
    {
    	status = InitSD(VERBOSE_OFF); /* Initialize SD_CARD and SPI Interface */    	
    }while(status != SD_OK);
#endif
    /* Initialize the USB interface */
    error = USB_Class_MSC_Init(g_disk.app_controller_ID,
      USB_App_Callback,NULL, MSD_Event_Callback);
	
    UserExitCritical();
    #if (defined _MCF51MM256_H) || (defined _MCF51JE256_H) || (defined _MCF51JE128_H)
     usb_int_en();
    #endif    
} 

/******************************************************************************
 *
 *   @name        TestApp_Task
 *
 *   @brief       Application task function. It is called from the main loop
 *
 *   @param       None
 *
 *   @return      None
 *
 *****************************************************************************
 * Application task function. It is called from the main loop
 *****************************************************************************/
void MSD_Task(void)
{
        /* call the periodic task function */      
        USB_MSC_Periodic_Task(); 
       /*check whether enumeration is complete or not */
        if(g_disk.start_app==TRUE)
        {        
            Disk_App(); 
        }
}

#endif
/* EOF */
