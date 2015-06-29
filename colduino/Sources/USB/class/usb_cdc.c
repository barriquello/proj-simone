/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 ******************************************************************************
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************//*!
 *
 * @file usb_cdc.c
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief The file contains USB stack CDC layer implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_cdc.h"    /* USB CDC Class Header File */

#if (USB_CLASS_TYPE == BRTOS_USB_CDC)
/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/

/****************************************************************************
 * Global Variables
 ****************************************************************************/
#ifdef _MC9S08JS16_H
#pragma DATA_SEG APP_DATA
#endif

/* CDC Class Callback Function Pointer */
static USB_CLASS_CALLBACK g_cdc_class_callback = NULL;

/* CDC Class Vendor Callback Function Pointer */
static USB_REQ_FUNC g_vendor_req_callback = NULL;

/* CDC endpoint info array */
static USB_CLASS_CDC_ENDPOINT g_cdc_ep[CDC_DESC_ENDPOINT_COUNT];
/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
#if CIC_NOTIF_ELEM_SUPPORT
static void USB_Class_CDC_Service_Cic_Notify(PTR_USB_DEV_EVENT_STRUCT event);
#endif
#if !DIC_ISOCHRONOUS_SETTING
static void USB_Class_CDC_Service_Dic_Bulk_In(PTR_USB_DEV_EVENT_STRUCT event);
static void USB_Class_CDC_Service_Dic_Bulk_Out(PTR_USB_DEV_EVENT_STRUCT event);
#else
static void USB_Class_CDC_Service_Dic_Iso_In(PTR_USB_DEV_EVENT_STRUCT event);
static void USB_Class_CDC_Service_Dic_Iso_Out(PTR_USB_DEV_EVENT_STRUCT event);
#endif
static uint_8 USB_Other_Requests(
    uint_8 controller_ID,
    USB_SETUP_STRUCT * setup_packet,
    uint_8_ptr *data,
    USB_PACKET_SIZE *size);
static void USB_Class_CDC_Event(
    uint_8 controller_ID,
    uint_8 event,
    void* val);

/*****************************************************************************
 * Local Variables - None
 *****************************************************************************/

 /*****************************************************************************
 * Local Functions
 *****************************************************************************/
#if CIC_NOTIF_ELEM_SUPPORT
/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Service_Cic_Notify
 *
 * @brief The funtion is callback function of CIC Notification endpoint
 *
 * @param event : Pointer to USB Event Structure
 *
 * @return None
 *
 ******************************************************************************
 * Called by Lower layer when data on CIC Endpoint is sent
 *****************************************************************************/
static void USB_Class_CDC_Service_Cic_Notify (
    PTR_USB_DEV_EVENT_STRUCT event  /* [IN] Pointer to USB Event Structure */
)
{
#if IMPLEMENT_QUEUING
    uint_8 index;
    uint_8 producer, consumer;
    USB_ENDPOINTS *usb_ep_data = (USB_ENDPOINTS *)
        USB_Desc_Get_Endpoints(event->controller_ID);

    USB_CLASS_CDC_QUEUE queue;

    /* map the endpoint num to the index of the endpoint structure */
    for(index = 0; index < usb_ep_data->count; index++)
    {
        if(usb_ep_data->ep[index].ep_num == event->ep_num)
        break;
    }

    producer = g_cdc_ep[index].bin_producer;

    /* if there are no errors de-queue the queue and decrement the no. of
       transfers left, else send the same data again */
    if(event->errors == 0)
    {
        g_cdc_ep[index].bin_consumer++;
    }

    consumer = g_cdc_ep[index].bin_consumer;

    if(consumer != producer)
    {/*if bin is not empty */

        queue = g_cdc_ep[index].queue[consumer%MAX_QUEUE_ELEMS];

        (void)USB_Class_Send_Data(queue.controller_ID, queue.channel,
            queue.app_data.data_ptr, queue.app_data.data_size);
    }
#endif

    if(g_cdc_class_callback != NULL)
    {
        uint_8 event_type = USB_APP_SEND_COMPLETE;

        if(event->errors != 0)
        {
            event_type = USB_APP_ERROR;
        }
        g_cdc_class_callback(event->controller_ID, event_type,
            (uint_8*)(&(event->errors)));
    }
}
#endif

#if !DIC_ISOCHRONOUS_SETTING
/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Service_Dic_Bulk_In
 *
 * @brief The funtion is callback function of DIC Bulk In Endpoint
 *
 * @param event : Pointer to USB Event Structure
 *
 * @return None
 *
 ******************************************************************************
 * Called by Lower Layer when Data on DIC SEND Interface is sent
 *****************************************************************************/
static void USB_Class_CDC_Service_Dic_Bulk_In (
    PTR_USB_DEV_EVENT_STRUCT event /* [IN] Pointer to USB Event Structure */
)
{
    APP_DATA_STRUCT bulk_in_recv;

#if IMPLEMENT_QUEUING
    uint_8 index;
    uint_8 producer, consumer;
    USB_ENDPOINTS *usb_ep_data = (USB_ENDPOINTS *)
        USB_Desc_Get_Endpoints(event->controller_ID);

    USB_CLASS_CDC_QUEUE queue;

    bulk_in_recv.data_ptr = event->buffer_ptr;
    bulk_in_recv.data_size = event->len;

    /* map the endpoint num to the index of the endpoint structure */
    for(index = 0; index < usb_ep_data->count; index++)
    {
        if(usb_ep_data->ep[index].ep_num == event->ep_num)
        break;
    }

    producer = g_cdc_ep[index].bin_producer;

    /* if there are no errors de-queue the queue and decrement the no. of
       transfers left, else send the same data again */
    if(event->errors == 0)
    {
        g_cdc_ep[index].bin_consumer++;
    }

    consumer = g_cdc_ep[index].bin_consumer;

    if(consumer != producer)
    {/*if bin is not empty */

        queue = g_cdc_ep[index].queue[consumer%MAX_QUEUE_ELEMS];

        (void)USB_Class_Send_Data(queue.controller_ID, queue.channel,
            queue.app_data.data_ptr, queue.app_data.data_size);
    }
#endif
    if(g_cdc_class_callback != NULL)
    {
        if(event->errors != 0)
        {
            g_cdc_class_callback(event->controller_ID, USB_APP_ERROR,
                (uint_8*)(&(event->errors)));
        }
        else
        {
            g_cdc_class_callback(event->controller_ID, USB_APP_SEND_COMPLETE,
                (void*)&bulk_in_recv);
        }
    }
}

/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Service_Dic_Bulk_Out
 *
 * @brief The funtion is callback function of DIC Bulk Out Endpoint
 *
 * @param event : Pointer to USB Event Structure
 *
 * @return None
 *
 ******************************************************************************
 * Called by Lower Layer when Data on DIC RECV Interface is received
 *****************************************************************************/
static void USB_Class_CDC_Service_Dic_Bulk_Out (
    PTR_USB_DEV_EVENT_STRUCT event  /* [IN] Pointer to USB Event Structure */
)
{   APP_DATA_STRUCT bulk_out_recv;

    bulk_out_recv.data_ptr = event->buffer_ptr;
    bulk_out_recv.data_size = event->len;

    if(g_cdc_class_callback != NULL)
    {
        if(event->errors != 0)
        {
            g_cdc_class_callback(event->controller_ID, USB_APP_ERROR,
                (uint_8*)(&(event->errors)));
        }
        else
        {
            g_cdc_class_callback(event->controller_ID, USB_APP_DATA_RECEIVED,
                (void*)&bulk_out_recv);
        }
    }
}

#else
/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Service_Dic_Iso_In
 *
 * @brief The funtion is callback function of DIC Isochronous In Endpoint
 *
 * @param event : Pointer to USB Event Structure
 *
 * @return None
 *
 ******************************************************************************
 * Called by Lower Layer when Data on DIC SEND Interface is sent
 *****************************************************************************/
static void USB_Class_CDC_Service_Dic_Iso_In (
    PTR_USB_EVENT_STRUCT event   /* [IN] Pointer to USB Event Structure */
)
{
    APP_DATA_STRUCT iso_in_recv;

#if IMPLEMENT_QUEUING
    uint_8 index;
    uint_8 producer, consumer;
    USB_ENDPOINTS *usb_ep_data = (USB_ENDPOINTS *)
        USB_Desc_Get_Endpoints(event->controller_ID);

    USB_CLASS_CDC_QUEUE queue;

    /* map the endpoint num to the index of the endpoint structure */
    for(index = 0; index < usb_ep_data->count; index++)
    {
        if(usb_ep_data->ep[index].ep_num == event->ep_num)
        {
            break;
        }
    }

    producer = g_cdc_ep[index].bin_producer;

    /* if there are no errors de-queue the queue and decrement the no. of
       transfers left, else send the same data again */
    if(event->errors == 0)
    {
        g_cdc_ep[index].bin_consumer++;
    }

    consumer = g_cdc_ep[index].bin_consumer;

    if(consumer != producer)
    {/*if bin is not empty */

        queue = g_cdc_ep[index].queue[consumer%MAX_QUEUE_ELEMS];

        (void)USB_Class_Send_Data(queue.controller_ID, queue.channel,
            queue.app_data.data_ptr, queue.app_data.data_size);
    }
#endif

    iso_in_recv.data_ptr = event->buffer_ptr;
    iso_in_recv.data_size = event->len;

    if(g_cdc_class_callback != NULL)
    {
        if(event->errors != 0)
        {
            g_cdc_class_callback(event->controller_ID, USB_APP_ERROR,
                (uint_8*)(&(event->errors)));
        }
        else
        {
            g_cdc_class_callback(event->controller_ID, USB_APP_SEND_COMPLETE,
                (void*)&iso_in_recv);
        }
    }
}

/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Service_Dic_Iso_Out
 *
 * @brief This is a callback function of DIC Isochronous Out Endpoint
 *
 * @param event : Pointer to USB Event Structure
 *
 * @return None
 *
 ******************************************************************************
 * Called by Lower Layer when Data on DIC RECV Interface is received
 *****************************************************************************/
static void USB_Class_CDC_Service_Dic_Iso_Out (
    PTR_USB_EVENT_STRUCT event   /* [IN] Pointer to USB Event Structure */
)
{
    APP_DATA_STRUCT iso_out_recv;

    iso_out_recv.data_ptr = event->buffer_ptr;
    iso_out_recv.data_size = event->len;

    if(g_cdc_class_callback != NULL)
    {
        if(event->errors != 0)
        {
            g_cdc_class_callback(event->controller_ID, USB_APP_ERROR,
                (uint_8*)(&(event->errors)));
        }
        else
        {
            g_cdc_class_callback(event->controller_ID, USB_APP_DATA_RECEIVED,
                (void*)&iso_out_recv);
        }
    }
}
#endif
/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Event
 *
 * @brief The funtion initializes CDC endpoints
 *
 * @param controller_ID : Controller ID
 * @param event         : Event Type
 * @param val           : Pointer to configuration Value
 *
 * @return None
 *
 ******************************************************************************
 *
 *****************************************************************************/
static void USB_Class_CDC_Event (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 event,           /* [IN] Event Type */
    void* val               /* [OUT] Pointer to configuration Value */
)
{
    uint_8 index;
    USB_ENDPOINTS *usb_ep_data = (USB_ENDPOINTS *)
        USB_Desc_Get_Endpoints(controller_ID);

    if(event == USB_APP_ENUM_COMPLETE)
    {
		uint_8 count;
		count = usb_ep_data->count; 
		/* deinitialize all endpoints in case they were initialized */
		while(count > 0) 
		{   
			USB_EP_STRUCT_PTR ep_struct_ptr= 
				(USB_EP_STRUCT_PTR) (&usb_ep_data->ep[count - 1]);
			(void)_usb_device_deinit_endpoint(&controller_ID,
				ep_struct_ptr->ep_num, ep_struct_ptr->direction);
			 count--;   
		}
        
        /* intialize all non control endpoints */
        while(count < usb_ep_data->count)
        {
            USB_EP_STRUCT_PTR ep_struct=
                (USB_EP_STRUCT_PTR) (&usb_ep_data->ep[count]);

            (void)_usb_device_init_endpoint(&controller_ID, ep_struct->ep_num,
            		ep_struct->size, ep_struct->direction, ep_struct->type, FALSE);

            /* register callback service for Non Control EndPoints */
            switch(ep_struct->type)
            {
#if CIC_NOTIF_ELEM_SUPPORT
                case USB_INTERRUPT_PIPE :
                    (void)_usb_device_register_service(controller_ID,
                        (uint_8)(USB_SERVICE_EP0+ep_struct->ep_num),
                        USB_Class_CDC_Service_Cic_Notify);
                    break;
#endif
#if !DIC_ISOCHRONOUS_SETTING
                case USB_BULK_PIPE :
                    if(ep_struct->direction == USB_RECV)
                    {
                        (void)_usb_device_register_service(controller_ID,
                            (uint_8)(USB_SERVICE_EP0+ep_struct->ep_num),
                            USB_Class_CDC_Service_Dic_Bulk_Out);
                    }
                    else
                    {
                        (void)_usb_device_register_service(controller_ID,
                            (uint_8)(USB_SERVICE_EP0+ep_struct->ep_num),
                            USB_Class_CDC_Service_Dic_Bulk_In);
                    }
                    break;
#else
                case USB_ISOCHRONOUS_PIPE :
                    if(ep_struct->direction == USB_RECV)
                    {
                        (void)_usb_device_register_service(controller_ID,
                            (uint_8)(USB_SERVICE_EP0+ep_struct->ep_num),
                            USB_Class_CDC_Service_Dic_Iso_Out);
                    }
                    else
                    {
                        (void)_usb_device_register_service(controller_ID,
                            (uint_8)(USB_SERVICE_EP0+ep_struct->ep_num),
                            USB_Class_CDC_Service_Dic_Iso_In);
                    }
                    break;
#endif
                default: 
                    break;
            }
            /* set the EndPoint Status as Idle in the device layer */
            (void)_usb_device_set_status(&controller_ID,
                (uint_8)(USB_STATUS_ENDPOINT | ep_struct->ep_num |
                (ep_struct->direction << USB_COMPONENT_DIRECTION_SHIFT)),
                (uint_8)USB_STATUS_IDLE);
            count++;
        }
    }
    else if(event == USB_APP_BUS_RESET)
    {
#if IMPLEMENT_QUEUING
        for(index = 0; index < usb_ep_data->count; index++)
        {
            g_cdc_ep[index].bin_consumer = 0x00;
            g_cdc_ep[index].bin_producer = 0x00;
        }
#endif
    }
    if(g_cdc_class_callback != NULL)
    {
        g_cdc_class_callback(controller_ID, event, val);
    }
}

/**************************************************************************//*!
 *
 * @name  USB_Other_Requests
 *
 * @brief The funtion provides flexibilty to add class and vendor specific
 *        requests
 *
 * @param controller_ID : Controller ID
 * @param setup_packet  : Setup packet received
 * @param data:         : Data to be send back
 * @param size:         : Size to be returned
 *
 * @return status:
 *                        USB_OK : When Successfull
 *                        Others : When Error
 *
 ******************************************************************************
 * Handles CDC Class requests and forwards vendor specific request to the
 * application
 *****************************************************************************/
static uint_8 USB_Other_Requests (
    uint_8 controller_ID,           /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,/* [IN] Pointer to Setup Packet Received */
    uint_8_ptr *data,           /* [OUT] Pointer to Data Buffer to be sent */
    USB_PACKET_SIZE *size           /* [OUT] Size of Data buffer */
)
{
    uint_8 status = USBERR_INVALID_REQ_TYPE;
    if((setup_packet->request_type & USB_REQUEST_CLASS_MASK) ==
        USB_REQUEST_CLASS_CLASS)
    {  
        /* class request so handle it here */
        status=USB_OK;

        /* call for class/subclass specific requests */
        switch(setup_packet->request)
        {
            case SEND_ENCAPSULATED_COMMAND :
                /* Add code to transfer Request and Acknowledgement */
                *size=0;
                break;
            case GET_ENCAPSULATED_RESPONSE :
                /* 
                   Add code for handling Transfer Response/Requests and
                   Notification 
                */
                *size=0;
                break;
            case SET_COMM_FEATURE :
                status = USB_Class_CDC_PSTN_Set_Comm_Feature(controller_ID, 
                    setup_packet, data, size);
                break;
            case GET_COMM_FEATURE :
                status = USB_Class_CDC_PSTN_Get_Comm_Feature(controller_ID,
                    setup_packet, data, size);
                break;
            case CLEAR_COMM_FEATURE : /* Verify this implementation */
                *size = COMM_FEATURE_DATA_SIZE;
                **data = 0x00; *(++(*data)) = 0x00;/* clear both feature bytes */
                status = USB_Class_CDC_PSTN_Set_Comm_Feature(controller_ID,
                    setup_packet, data, size);
              break;
            case GET_LINE_CODING :
                status = USB_Class_CDC_PSTN_Get_Line_Coding(controller_ID,
                    setup_packet, data, size);
                break;
            case SET_LINE_CODING :
                status = USB_Class_CDC_PSTN_Set_Line_Coding(controller_ID,
                    setup_packet, data, size);
                break;
            case SET_CONTROL_LINE_STATE :
                status = USB_Class_CDC_PSTN_Set_Ctrl_Line_State(controller_ID,
                    setup_packet, data, size);
                break;
            case SEND_BREAK :
                status = USB_Class_CDC_PSTN_Send_Break(controller_ID,
                    setup_packet, data, size);
                break;
            default:  
                *size=0;
                break;
        }
    }
    else if((setup_packet->request_type & USB_REQUEST_CLASS_MASK) ==
        USB_REQUEST_CLASS_VENDOR)
    {
        /* vendor specific request  */
        if(g_vendor_req_callback != NULL)
        {
            status = g_vendor_req_callback(controller_ID, setup_packet, data,
            size);
        }
    }
    return status;
}


/*****************************************************************************
 * Global Functions
 *****************************************************************************/
/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Init
 *
 * @brief The funtion initializes the Device and Controller layer
 *
 * @param controller_ID:        Controller ID
 * @param cdc_class_callback:   CDC Class Callback
 * @param vendor_req_callback:  vendor specific class request callback
 * @param param_callback:       PSTN Callback
 *
 * @return status
 *         USB_OK           : When Successfull
 *         Others           : Errors
 ******************************************************************************
 * This function initializes the CDC Class layer and layers it is dependent upon
 *****************************************************************************/
uint_8 USB_Class_CDC_Init (
    uint_8    controller_ID,                /* [IN] Controller ID */
    USB_CLASS_CALLBACK cdc_class_callback,  /* [IN] CDC Class Callback */
    USB_REQ_FUNC       vendor_req_callback, /* [IN] Vendor Request Callback */
    USB_CLASS_CALLBACK pstn_callback        /* [IN] PSTN Callback */
)
{
    uint_8 index;
    USB_ENDPOINTS *usb_ep_data =
        (USB_ENDPOINTS *)USB_Desc_Get_Endpoints(controller_ID);
    /* Initialize the device layer*/
    uint_8 status = _usb_device_init(controller_ID, NULL,
        (uint_8)(usb_ep_data->count+1));
    /* +1 is for Control Endpoint */

    if(status == USB_OK)
    {
        /* Initialize the generic class functions */
        status = USB_Class_Init(controller_ID,USB_Class_CDC_Event,
            USB_Other_Requests);
#if IMPLEMENT_QUEUING
            for(index = 0; index < usb_ep_data->count; index++)
            {
                g_cdc_ep[index].endpoint = usb_ep_data->ep[index].ep_num;
                g_cdc_ep[index].type = usb_ep_data->ep[index].type;
                g_cdc_ep[index].bin_consumer = 0x00;
                g_cdc_ep[index].bin_producer = 0x00;
            }
#endif
#if PSTN_SUBCLASS_NOTIF_SUPPORT
        /* Initialize the pstn subclass functions */
        status = USB_Class_CDC_Pstn_Init(controller_ID,pstn_callback);
#endif
        if(status == USB_OK)
        {
           /* save the callback pointer */
           g_cdc_class_callback = cdc_class_callback;

           /* save the callback pointer */
           g_vendor_req_callback = vendor_req_callback;
        }
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_DeInit
 *
 * @brief   The funtion de-initializes the Device and Controller layer
 *
 * @param   controller_ID               : Controller ID
 *
 * @return status:
 *                        USB_OK        : When Successfull
 *                        Others        : When Error
 *
 ******************************************************************************
 *This function de-initializes the CDC Class layer
 *****************************************************************************/
uint_8 USB_Class_CDC_DeInit 
(
    uint_8 controller_ID              /* [IN] Controller ID */
) 
{
    uint_8 status;
    
    /* save the callback pointer */
    g_cdc_class_callback = NULL;
    
    /* free the vendor request callback pointer */
    g_vendor_req_callback = NULL;
    
    /* call common class deinit function */
    status = USB_Class_DeInit(controller_ID);
    
    if(status == USB_OK)
    /* Call device deinit function */
    	status = _usb_device_deinit();
    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Send_Data
 *
 * @brief This function is used to send data from CDC Class over send endpoints
 *
 * @param controller_ID : Controller ID
 * @param ep_num        : Endpoint number
 * @param app_buff      : Buffer to send
 * @param size          : Length of the transfer
 *
 * @return status
 *         USB_OK           : When Successfull
 *         Others           : Errors
 ******************************************************************************
 * Helper function. Sends DATA over CIC and DIC Interfaces to Host
 *****************************************************************************/
uint_8 USB_Class_CDC_Send_Data (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 ep_num,          /* [IN] Endpoint Number */
    uint_8_ptr app_buff,    /* Pointer to Application Buffer */
    USB_PACKET_SIZE size    /* Size of Application Buffer */
)
{
    uint_8 status = USB_OK;

#if IMPLEMENT_QUEUING
    uint_8 index;
    uint_8 producer, consumer;

    USB_ENDPOINTS *usb_ep_data = (USB_ENDPOINTS *)
                                    USB_Desc_Get_Endpoints(controller_ID);

    /* map the endpoint num to the index of the endpoint structure */
    for(index = 0; index < usb_ep_data->count; index++)
    {
        if(usb_ep_data->ep[index].ep_num == ep_num)
        {
            break;
        }
    }

    producer = g_cdc_ep[index].bin_producer;
    consumer = g_cdc_ep[index].bin_consumer;

    if(((uint_8)(producer - consumer)) != (uint_8)(MAX_QUEUE_ELEMS))
    {
        /* the bin is not full*/

        uint_8 queue_num = (uint_8)(producer % MAX_QUEUE_ELEMS);

        /* put all send request parameters in the endpoint data structure */
        g_cdc_ep[index].queue[queue_num].controller_ID = controller_ID;
        g_cdc_ep[index].queue[queue_num].channel = ep_num;
        g_cdc_ep[index].queue[queue_num].app_data.data_ptr = app_buff;
        g_cdc_ep[index].queue[queue_num].app_data.data_size = size;

        /* increment producer bin by 1*/
        g_cdc_ep[index].bin_producer = ++producer;

        if((uint_8)(producer - consumer) == (uint_8)1)
        {
#endif
            status = USB_Class_Send_Data(controller_ID, ep_num, app_buff,size);
#if IMPLEMENT_QUEUING
        }
    }
    else /* bin is full */
    {
        status = USBERR_DEVICE_BUSY;
    }
#endif
    return status;
}

#endif
/* EOF */
