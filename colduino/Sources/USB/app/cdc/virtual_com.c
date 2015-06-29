/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file virtual_com.c
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief  The file emulates a USB PORT as Loopback Serial Port.
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "BRTOS.h"
#include "hidef.h"          		/* for EnableInterrupts macro */
#include "derivative.h"     		/* include peripheral declarations */
#include "types.h"          		/* Contains User Defined Data Types */
#include "usb_cdc.h"        		/* USB CDC Class Header File */
#include "usb_terminal.h"			/* Informs the size of the terminal buffer */
#include "usb_terminal_commands.h"	/* USB terminal commands - functions */
#include "virtual_com.h"    		/* Virtual COM Application Header File */
#include <stdio.h>

#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H) || (defined _MCF51JE128_H)
#include "exceptions.h"
#endif

#if (USB_CLASS_TYPE == BRTOS_USB_CDC)

/* skip the inclusion in dependency state */
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

/****************************************************************************
 * Global Variables
 ****************************************************************************/
/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
static void USB_App_Callback(uint_8 controller_ID,
                        uint_8 event_type, void* val);
static void USB_Notify_Callback(uint_8 controller_ID,
                        uint_8 event_type, void* val);
static void Virtual_Com_App(void);
/*****************************************************************************
 * Local Variables
 *****************************************************************************/
#ifdef _MC9S08JS16_H
#pragma DATA_SEG APP_DATA
#endif
/* Virtual COM Application start Init Flag */
static volatile boolean start_app = FALSE;
/* Virtual COM Application Carrier Activate Flag */
static volatile boolean start_transactions = FALSE;


static INT8U 	is_message_sent = 0;
BRTOS_Sem   	*USB_Sem;

// Declara uma estrutura de fila
OS_QUEUE 		USBRXBuffer;
// Declara um ponteiro para o bloco de controle da Porta Serial
BRTOS_Queue 	*USB;

/* Send Buffer */
static uint_8 g_curr_send_buf[DATA_BUFF_SIZE];
/* Send Data Size */
static uint_8 g_send_size;
/*****************************************************************************
 * Local Functions
 *****************************************************************************/
 /******************************************************************************
 *
 *   @name        TestApp_Init
 *
 *   @brief       This function is the entry for the Virtual COM Loopback app
 *
 *   @param       None
 *
 *   @return      None
 *****************************************************************************
 * This function starts the Virtual COM Loopback application
 *****************************************************************************/

void CDC_Init(void)
{
	uint_8   error;
    g_send_size = 0;
    
  	// Create USB semaphore
  	if (OSSemCreate(0,&USB_Sem) != ALLOC_EVENT_OK)
    {
        while(1){};
     };
  	
  	// Cria uma fila de recepcao para a porta serial
  	if (OSQueueCreate(&USBRXBuffer,CONSOLE_BUFFER_SIZE, &USB) != ALLOC_EVENT_OK)
  	{
  		while(1){};
  	};	    
    
    UserEnterCritical();	
    #if (defined _MCF51MM256_H) || (defined _MCF51JE256_H) || (defined _MCF51JE128_H)
     usb_int_dis();
    #endif
    
    /* Initialize the USB interface */
    SCGC2 |= SCGC2_USB_MASK;     /* Enables usb clock */
    
    error = USB_Class_CDC_Init(CONTROLLER_ID,USB_App_Callback,
                                NULL,USB_Notify_Callback);
    //if(error != USB_OK)
    /* Error initializing USB-CDC Class */
    
    UserExitCritical();
	#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H) || (defined _MCF51JE128_H)
     usb_int_en();
    #endif
}


/******************************************************************************
 *
 *    @name       Virtual_Com_App
 *
 *    @brief      Implements Loopback COM Port
 *
 *    @param      None
 *
 *    @return     None
 *
 *****************************************************************************
 * Receives data from USB Host and transmits back to the Host
 *****************************************************************************/
void cdc_process(void)
{
    static uint_8 status 	 = 0;
    uint_8 		  sem_status = 0;
	uint_8 size = g_send_size;
	
    /*check whether enumeration is complete or not */
     if((start_app==TRUE) && (start_transactions==TRUE))
     {	
		g_send_size = 0;
		
		UserEnterCritical();
		is_message_sent = 1;
		UserExitCritical();
		
		status = USB_Class_CDC_Interface_DIC_Send_Data(CONTROLLER_ID, g_curr_send_buf,size);
		sem_status = OSSemPend(USB_Sem,500);	   
		
		if (sem_status != OK)
		{
			UserEnterCritical();
			is_message_sent = 0;
			UserExitCritical();
		}
		
        if(status != USB_OK)
        {
            /* Send Data Error Handling Code goes here */
        	status = 0;
        }		
     }else
     {
    	  while(GetStart_transactions() == FALSE)
    	  {
    		  DelayTask(100);
    	  }
     }
}

unsigned char GetStart_transactions(void)
{
	return (start_transactions);
}


/*****************************************************************************
* Name:
*    cdc_putch
* In:
*    c: character to be sent
* Out:
*    0: output is busy, character dropped
*    1: character buffered and will be sent later.
*
* Description:
*    Put one character into tx_buffer.
*
* Assumptions:
*    --
*****************************************************************************/
unsigned char cdc_putch(char c)
{
  uint_8 r=(unsigned char)c;
  /* Store character into current buffer. */
  if (g_send_size < sizeof(g_curr_send_buf))
  {
	g_curr_send_buf[g_send_size++]=(unsigned char)c;
    if (c == '\r')
    {
      cdc_process();
    }	
  }
  else
  {
    cdc_process();
    r++;
  }
  return((uint_8)r);
}

/******************************************************************************
 *
 *    @name        USB_App_Callback
 *
 *    @brief       This function handles Class callback
 *
 *    @param       controller_ID    : Controller ID
 *    @param       event_type       : Value of the event
 *    @param       val              : gives the configuration value
 *
 *    @return      None
 *
 *****************************************************************************
 * This function is called from the class layer whenever reset occurs or enum
 * is complete. After the enum is complete this function sets a variable so
 * that the application can start.
 * This function also receives DATA Send and RECEIVED Events
 *****************************************************************************/

static void USB_App_Callback (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 event_type,      /* [IN] value of the event */
    void* val               /* [IN] gives the configuration value */
)
{
    UNUSED (controller_ID)
    UNUSED (val)
    if(event_type == USB_APP_BUS_RESET)
    {
        start_app=FALSE;
    }
    else if(event_type == USB_APP_ENUM_COMPLETE)
    {
        start_app=TRUE;
    }
    else if((event_type == USB_APP_DATA_RECEIVED)&&
            (start_transactions == TRUE))
    {
        /* Copy Received Data buffer to Application Buffer */
        USB_PACKET_SIZE BytesToBeCopied;
        APP_DATA_STRUCT* dp_rcv = (APP_DATA_STRUCT*)val;
        uint_8 index;
        BytesToBeCopied = (USB_PACKET_SIZE)((dp_rcv->data_size > DATA_BUFF_SIZE) ?
                                      DATA_BUFF_SIZE:dp_rcv->data_size);
        
        if (BytesToBeCopied <= DATA_BUFF_SIZE)
        {
			for(index = 0; index<BytesToBeCopied ; index++)
			{            
				if (dp_rcv->data_ptr[index] != 0)
				{
					if (OSQueuePost(USB, dp_rcv->data_ptr[index]) == BUFFER_UNDERRUN)
					{
					  // Buffer overflow 					
					   while(1){
						   __RESET_WATCHDOG();
					   }
					}
				}
			}
			/* Previous Send is complete. Queue next receive */
			(void)USB_Class_CDC_Interface_DIC_Recv_Data(CONTROLLER_ID, NULL, 0);
        }
    }
    else if((event_type == USB_APP_SEND_COMPLETE) && (start_transactions == TRUE))
    {
		if (is_message_sent)
		{
			  is_message_sent = 0;
			  OSSemPost(USB_Sem);
		}		
    }

    return;
}

/******************************************************************************
 *
 *    @name        USB_Notify_Callback
 *
 *    @brief       This function handles PSTN Sub Class callbacks
 *
 *    @param       controller_ID    : Controller ID
 *    @param       event_type       : PSTN Event Type
 *    @param       val              : gives the configuration value
 *
 *    @return      None
 *
 *****************************************************************************
 * This function handles USB_APP_CDC_CARRIER_ACTIVATED and
 * USB_APP_CDC_CARRIER_DEACTIVATED PSTN Events
 *****************************************************************************/

static void USB_Notify_Callback (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 event_type,      /* [IN] PSTN Event Type */
    void* val               /* [IN] gives the configuration value */
)
{
    UNUSED (controller_ID)
    UNUSED (val)
    if(start_app == TRUE)
    {
        if(event_type == USB_APP_CDC_CARRIER_ACTIVATED)
        {
            start_transactions = TRUE;
            echo (">> BRTOS Started!", FALSE);
        }
        else if(event_type == USB_APP_CDC_CARRIER_DEACTIVATED)
        {
            start_transactions = FALSE;
        }
    }
    return;
}

#endif
/* EOF */
