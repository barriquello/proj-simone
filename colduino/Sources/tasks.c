/*********************************************************************************************************
 *                                               BRTOS
 *                                Brazilian Real-Time Operating System
 *                            Acronymous of Basic Real-Time Operating System
 *
 *                              
 *                                  Open Source RTOS under MIT License
 *
 *
 *
 *                                              OS Tasks
 *
 *
 *   Author:   Gustavo Weber Denardin
 *   Revision: 1.0
 *   Date:     20/03/2009
 *
 *********************************************************************************************************/

#include "BRTOS.h"
#include "drivers.h"
#include "tasks.h"
#include "AppConfig.h"
#include "virtual_com.h"
#include "usb_terminal.h"
#include "usb_terminal_commands.h"
#include "led_onboard.h"

#pragma warn_implicitconv off

void System_Time(void)
{
	// task setup
	INT16U milis = 0;
	INT16U segundos = 0;

	OSResetTime();

	led_onboard_init();
	
	led_onboard_on();
	
	#if RTC_PRESENTE
		while(Init_Calendar() == FALSE)
		{
			DelayTask(10);
			#if (WATCHDOG == 1)
				__RESET_WATCHDOG();
			#endif			
		}
	#endif	
	
	led_onboard_off();

	// task main loop
	for (;;)
	{
		#if (WATCHDOG == 1)
			__RESET_WATCHDOG();
		#endif     

		DelayTask(10);
		milis += 10;
		
		if (milis >= 1000)
		{
			milis = 0;
			
			OSUpdateUptime();
			OSUpdateCalendar();
			
			segundos++;
			if (segundos == 3600)
			{
				segundos = 0;
				
				#if RTC_PRESENTE				
					Resync_calendar();  // resync with RTC every 3600s = 60min = 1h
				#endif				
				
			}
		}

		///////////////////////////////////////////////////
		///   FatFS Timer Handler                       ///
		///////////////////////////////////////////////////
		disk_timerproc();
		///////////////////////////////////////////////////        
	}

}

#include "user_config.h"
#if (USB_CLASS_TYPE == BRTOS_USB_MSD)
void Mass_Storage_Device_Task(void)
{
	/* task setup */
	(void)MSD_Init(); /* Initialize the USB Test Application */

	while(1)
	{
		/* Call the application task */
		MSD_Task();
	}
}
#endif

#if (USB_CLASS_TYPE == BRTOS_USB_CDC)

#define TERM_UART1  1
#define TERM_UART2  1

#define TERM1_PINS   UART1_PTA1_PTA2
//#define TERM2_PINS   UART2_PTE5_PTE6
#define TERM2_PINS   UART2_PTF1_PTF2

void Terminal_Task(void)
{
	/* task setup */
	(void) CDC_Init(); /* Initialize the USB CDC Application */

	usb_terminal_init(cdc_putch);
	
#if TERM_UART1
	#define UART1_BUFSIZE	128
	#if UART1_MUTEX	
		uart_init(1,9600,UART1_BUFSIZE,TERM1_PINS,TRUE,UART1_MUTEX_PRIO);
	#else
		uart_init(1,9600,UART1_BUFSIZE,TERM1_PINS,FALSE,0);
	#endif
#endif		
	
#if TERM_UART2
	#define UART2_BUFSIZE	128
	#if UART2_MUTEX		
		uart_init(2,9600,UART2_BUFSIZE,TERM2_PINS,TRUE,UART2_MUTEX_PRIO);
	#else
		uart_init(2,9600,UART2_BUFSIZE,TERM2_PINS,FALSE,0);
	#endif	

#endif	

	(void) usb_terminal_add_cmd((command_t*) &usb_ver_cmd);
	(void) usb_terminal_add_cmd((command_t*) &usb_top_cmd);
	(void) usb_terminal_add_cmd((command_t*) &usb_rst_cmd);
	(void) usb_terminal_add_cmd((command_t*) &usb_temp_cmd);
	(void) usb_terminal_add_cmd((command_t*) &setget_time_cmd);
	(void) usb_terminal_add_cmd((command_t*) &cat_cmd);
	(void) usb_terminal_add_cmd((command_t*) &ls_cmd);
	(void) usb_terminal_add_cmd((command_t*) &cd_cmd);
	(void) usb_terminal_add_cmd((command_t*) &mount_cmd);
	(void) usb_terminal_add_cmd((command_t*) &sr_cmd);
	(void) usb_terminal_add_cmd((command_t*) &rm_cmd);
	(void) usb_terminal_add_cmd((command_t*) &rn_cmd);
	(void) usb_terminal_add_cmd((command_t*) &cr_cmd);
	(void) usb_terminal_add_cmd((command_t*) &mkdir_cmd);
	(void) usb_terminal_add_cmd((command_t*) &cp_cmd);
	(void) usb_terminal_add_cmd((command_t*) &wt_cmd);
	(void) usb_terminal_add_cmd((command_t*) &echo_cmd);
	(void) usb_terminal_add_cmd((command_t*) &echo_stdout_cmd);
	(void) usb_terminal_add_cmd((command_t*) &esp_cmd);	

	while (1)
	{
		/* Call the application task */
		usb_terminal_process();
	}
}
#endif

/*
 * registra modem GSM/GPRS
 * procura conectividade GPRS
 * 
 - se tem conectividade 

 mutex (RTC)
 - ajusta calendário e RTC
 - ajusta data e hora
 mutex (RTC)

 mutex(cartão SD)

 - busca arquivo ainda não enviado
 - se encontra, pede acesso ao arquivo, abre arquivo 
 - envia os dados 
 - aguarda timeout de resposta (max 20s)
 - se ok, altera status da linha enviada e salva
 - senão desiste
 - fecha arquivo

 mutex(cartão SD)
 - aguarda 1 segundo.
 
 senão 
 - aguarda TEMPO DE NOVA TENTATIVA.

 * 
 * 
 * */
#include "stdio.h"
#include "string.h"
#include "utils.h"
#include "esp8266_at.h"

#define modem_receive()		at_esp_getchar() 
#define modem_send(x)		esp_print(x)
#define modem_wait_reply()	DelayTask(1000); while((c=modem_receive()) != (CHAR8)-1){putchar_usb(c);};
#define NEWLINE() 			modem_send(("\r\n"));

char resp_server_ok[12];

void Tarefa_GPRS(void)
{
	/* task setup */	
	/* Tarefa do Logger para comunicacao com modem na UART2 a 9600 bps */
	#define SEND_STRING0 "AT+CIPSENDI=0,\"GET node/set.json?nodeid=10&data="
	#define SEND_STRING1 "}&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1\\r\\nHost: emon-gpsnetcms.rhcloud.com\\r\\n\\r\\n\\r\\n\""
	
	#define SEND_STRING2 "AT+CIPSENDI=0,\"GET /input/post.json?json={pow:"	
	//#define SEND_STRING3 ("}&" API_KEY " HTTP/1.1\r\nHost: " ESP_TCP_SERVER_NAME "\r\n\r\n\r\n")
	#define SEND_STRING3 "}&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1\\r\\nHost: emon-gpsnetcms.rhcloud.com\\r\\n\\r\\n\\r\\n\""

	
	const char resp_200_OK[] = "HTTP/1.1 200 OK";
	#define REPLY_LENGTH  (sizeof(resp_200_OK) + 2)

   char valor[] = "01";
   INT8U cnt = 1;
   volatile char c;
   static char resp_serv[REPLY_LENGTH];
   static INT8U resp_cnt = 0;  
   INT16U tentativas = 0;	
	
    /* init ESP_UART */
   	uart_init(ESP_UART,ESP_BAUD,ESP_UART_BUFSIZE,ESP_UART_PINS,ESP_MUTEX,ESP_MUTEX_PRIO);
   	
   	/* init modem */
	modem_send("AT\r\n");
	modem_wait_reply();
	
	modem_send("AT+CWMODE=3\r\n");
	modem_wait_reply();
	
	modem_send(("AT+CWJAP=\"" ESP_AP "\",\"" ESP_PWD "\"\r\n"));
	modem_wait_reply();
	
	modem_send("AT+CIPCREATE=\"TCP\",10201,2048\r\n");	
	modem_wait_reply();
	
	modem_send("AT+CIPCONNECT=0,\"54.160.189.224\",80\r\n");	
	modem_wait_reply();
   	
	/* task main loop */
	for (;;)
	{
		 
		 DelayTask(5000); /* delay de 5s */
		/*   
		  Comando de envio 
		  GET /input/post.json?json={campo:valor}&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1
		  Host:emon-gpsnetcms.rhcloud.com
		  
		  GET /node/set.json?nodeid=10&data=20,20,20,20&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1
		  Host:emon-gpsnetcms.rhcloud.com
		  */
		  tentativas++; 
		  modem_send(SEND_STRING2);
		  sprintf(valor,"%d", cnt);
		  modem_send(valor);
		  modem_send(SEND_STRING3);
		  NEWLINE();
		
		  //modem_wait_reply();
		  INT8U keep_data = 0;
		  
		  DelayTask(1000); /* delay de 1s */
		  
			resp_cnt = 0; 
			
			while((c=modem_receive()) != (CHAR8)-1)
			{
				putchar_usb(c);
				
				if (keep_data < 2){
					if (c=='+') 
					{
						keep_data++;
					}
				}else{
					resp_server_ok[resp_cnt++]=c;
					if(resp_cnt == 9) 
					{
						if(c=='1'){
							resp_cnt = 0;
							break;
						}
					}
				}
			}
			
			while((c=modem_receive()) != (CHAR8)-1)
			{
				putchar_usb(c);
			}
		
		  
		  modem_send("AT+CIPRD=0\r\n");
		  
		  DelayTask(10); /* delay de 10ms */
		  
		  /* resposta:
			 HTTP/1.1 200 OK
			.Date: Wed, 03 Dec 2014 18:43:17 GMT
			.Server: Apache/2.2.15 (Red Hat)
			.Content-Length: 2
			.Content-Type: application/json
			.Vary: Accept-Encoding
			.Accept-Ranges: none
			.
			.ok
		  */
			
			while((c=modem_receive()) != (CHAR8)-1)
			{
				putchar_usb(c);
			}
			
			cnt++;
		
		   /* TODO: timeout */
#if 0			
			while(1){
			  		  
			  c=modem_receive();
			  
			  if ((c != '\r') && (c != '\n') && ((resp_cnt < sizeof(resp_serv)-2))){
				 resp_serv[resp_cnt++]=c;      			
			  }else{
				resp_serv[resp_cnt++]='\0';
				if(strcmp (resp_serv,resp_200_OK) == 0){
					cnt = (++cnt)%100;	
				}
				resp_cnt = 0;
				break;
			  }
			}
#endif			
			


	}
}

#include "rs485.h"
#include "uart.h"

void Tarefa_RS485(void)
{

	CHAR8 c;
	
	rs485_init(9600,UART1_PTD6_PTD7,FALSE,0);
	for(;;)
	{
		rx_rs485(&c);
		putchar_rs485(c);
		DelayTask(10); /* 10 ms */
	}
}

INT16S CoreTemp = 0;

void Tarefa_termometro(void)
{
	/* task setup */
	INT16U digital_temp = 0;
	INT16U bandgap = 0;
	INT16S temperature = 0;

	ADSetup(NormalPower, HighSpeed, ShortSampleTime, 20, 12);

	/* task main loop */
	for (;;)
	{
		(void) DelayTask(30000); /* 30s */

		//////////////////////////////////////////////////////////////
		// Adquire temperatura do core
		//////////////////////////////////////////////////////////////
		UserEnterCritical();
		digital_temp = ADConvert(TEMP_SENSOR_CH);
		UserExitCritical();

		UserEnterCritical();
		bandgap = ADConvert(BANDGAP_CH);
		UserExitCritical();

		digital_temp = (1170 * digital_temp) / bandgap;

		if (digital_temp > 701)
		{
			temperature = 25 - (((digital_temp - 701) * 1000) / 1646);
		}
		else
		{
			temperature = 25 - (((digital_temp - 701) * 1000) / 1769);
		}

		UserEnterCritical();
		CoreTemp = temperature;
		UserExitCritical();
		//////////////////////////////////////////////////////////////         
	}
}



#if 0
// Declares a queue structure for the keyboard
OS_QUEUE KeyboardBuffer;
BRTOS_Queue *qKeyboard;
// 
void HMI(void)
{
	/* task setup */
	INT8U key = 0;

	/* task main loop */
	for (;;)
	{

		if (!OSQueuePend(qKeyboard, &key, 500))
		{

			switch (key)
			{

			case UP_KEY :
				break;

			case DOWN_KEY :
				break;
			}
		}
	}
}

void Keyboard_Handler(void)
{
	// task setup
	INT16U ADSample = 0;
	INT8U Key = NO_KEY;

	// Initialize ACM keyboard for channel 1  
	ACM_Keyb_Setup(Enable, Enable, Rising, ACM_CHANNEL1);

	if (OSSemCreate(0, &sKeyboard) != ALLOC_EVENT_OK)
	{
		while (1){};
	};

	if (OSQueueCreate(&KeyboardBuffer, 64, &qKeyboard) != ALLOC_EVENT_OK)
	{
		while (1){};
	};

	// task main loop
	for (;;)
	{
		// Wait for a keyboard interrupt
		OSSemPend(sKeyboard, 0);
		DelayTask(50);

		// Converts the value of AD to discover the pressed key
		UserEnterCritical();
		ADSample = ADConvert(KEYB_CHANNEL);
		UserExitCritical();

		UserEnterCritical();
		ADSample += ADConvert(KEYB_CHANNEL);
		UserExitCritical();

		ADSample = ADSample >> 1;

		// Find out which key was pressed
		Key = FindKey(ADSample);

		// Copy the key to the keyboard buffer
		if (Key != NO_KEY)
		{
			if (OSQueuePost(qKeyboard, Key) == BUFFER_UNDERRUN)
			{
				// Buffer overflow
				OSCleanQueue(qKeyboard);
			}
		}

		// Enable interrupt to the next key detection
		DelayTask(200);
		ACMEnable();
	}
}
#endif

void BRTOS_TimerHook(void)
{

}

