/* The License
 * 
 * Copyright (c) 2015 Universidade Federal de Santa Maria
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.

*/
/*
 ============================================================================
 \file   monitor_main.c
 \author Carlos H. Barriquello
 \brief  Datalogger monitor
 ============================================================================

 - Arquivo de log local

1) um arquivo para cada monitor. Monitor é entendido como um conjunto de dados estruturados,
geralmente, associado a um único equipamento. Ex.: medidas elétricas associdas ao um
medidor de grandezas elétricas.

2) Dados devem guardados na forma de séries temporais ordenadas.
Uma série temporal é um conjunto de dados associados a uma estampa de tempo.

3) As séries são armazenadas no formato ASCII hexadecimal como um conjunto de bytes finalizados
por "nova linha e retorno" (\r\n), correspondendo cada linha a uma entrada de dados com
estampa de tempo.

4) As estampas de tempo podem estar nas entradas de dados, ou serem calculados a partir de uma
estampa inicial (ex. data e hora da criação do arquivo), quando estiverem separadas por um
intervalo constante. O formato da estampa é determinada pela versão do log. V00 - com estampas calculadas a partir da estampa inicial. As configurações são
guardadas no cabeçalho, V01 - com estampas incluídas

5) Cada arquivo inicia com um cabeçalho contendo (3 linhas com até 16 caracteres cada):
L1: Versao e Monitor ID, Bytes por linha e intervalo entre medições.
L2: data e hora inicial, flag de sincronização do arquivo,
L3: indice da última linha enviada (4 bytes).
L4: contador de entradas (linhas) (4 bytes)

Ex.: .
V00M00B0080I0030\r\n
TaaaammddhhmmssN\r\n
P0000\r\n
C0000\r\n
00
01
02
03
04


6) Os arquivos do logger são nomeados com a data/hora de sua criação no formato "AAMMDDHH.txt". Ao iniciar o logger, ele ordena os arquivos por data e tenta abrir o último arquivo salvo.
Caso ele não esteja sincronizado, os dados são armazenados no arquivo "99123123.txt". Este arquivo deverá ser renomeado com a data/hora de sua criação, quando houver a sincronização do relógio do logger.
A data/hora de criação será obtida a partir da data atual retrocedida de acordo com a quantidade de entradas de dados no arquivo.
Caso já haja um arquivo com o mesmo nome, o mesmo deverá ser renomeado para a data/ hora logo posterior.

Ex.:

15010107.txt >
...I0030...
T20150101073000S
...
00
01
02
03


99123123.txt >
...
T00000000000000N
...
00
01
02

sincronização em T20150101073400S

-> renomear para:

15010108.txt >
...
T20150101073300S ->
...
00 -> 3300
01 -> 3330
02 -> 3400


7) Caso o contador de entradas seja igual a FFFF (65535). Fecha-se o arquivo e inicia-se um arquivo novo.
8) Caso o indice da última linha enviada seja igual a FFFE (65534), o arquivo deverá ser renomeado com alteração da extensão (.txt -> .txd).
9) OS arquivos de log de cada monitor são guardados em diretórios separados nomeados com a ID do monitor.

 */

#include "AppConfig.h"
#include <stdlib.h>
#include <string.h>

#if PLATAFORMA == ARDUINO
//#include "time_lib.h"
#else
#include <time.h>
#endif



#ifdef _WIN32
#include <stdio.h>
#include "http_client.h"
#else
//#include "SD_API.h"
#endif

#if COLDUINO
#include "printf_lib.h"
#endif

#include "minIni.h"
#include "assert.h"
#include "monitor.h"
#include "simon-api.h"

static uint8_t 	num_monitores;
static uint8_t 	monitores_em_uso = 0;
monitor_state_t monitor_state[MAX_NUM_OF_MONITORES];
monitor_config_ok_t config_check;


#define DEBUG_MONITOR 1

#if DEBUG_MONITOR
#ifdef _WIN32
#define PRINTF(...) printf(__VA_ARGS__);
#define DPRINTF(...) printf(__VA_ARGS__);
#else
#define PRINTF(...) printf_lib(__VA_ARGS__);
#define DPRINTF(...) print_debug(__VA_ARGS__);
#endif
#else
#define PRINTF(...)
#define DPRINTF(...)
#endif

#ifndef CONST
#define CONST const
#endif

const char* monitor_error_msg[] =
{
	"\r\nConfig erro: faltando ",
	"\r\nMonitor erro: %d "
};
/*---------------------------------------------------------------------------*/
/*
 * Timer library
 */

#ifdef _WIN32
#include <windows.h>
#include <time.h>
#include <sys\timeb.h>
#else
#include "time_lib.h"
#include "utils.h"
#endif

#ifdef _WIN32

static clock_t clock_time(void)
{ return (clock_t)GetTickCount(); }

#else /* _WIN32 */

static clock_t clock = 0;

clock_t clock_time(void)
{
  clock_t local;
  
  OS_SR_SAVE_VAR;
  
  OSEnterCritical();
  	  local = clock;
  OSExitCritical();
  return local;
}

void BRTOS_TimerHook(void)
{
	clock++;
}
#endif /* _WIN32 */

static clock_t timer_expired(mon_timer_t *t)
{ return (clock_t)(clock_time() - t->start) >= (clock_t)t->interval; }

static void timer_set(mon_timer_t *t, uint32_t interval)
{ t->interval = interval; t->start = clock_time(); }

static uint16_t timer_elapsed(mon_timer_t *t)
{ return (uint16_t)(clock_time() - t->start - (clock_t)t->interval);}
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
void sleep_forever(void);


#if _WIN32
void wait (unsigned int secs) {
	unsigned int retTime = time(0) + secs;     // Get finishing time.
    while (time(0) < retTime);    // Loop until it arrives.
}


#include "conio.h"
static char getchar_timeout(int timeout)
{

   int timer = 0 ;
   while(!kbhit() && timeout > timer)
   {
      wait(1);
      timer++;
   }

   if(kbhit())
   {
      return(getch());
   }
   else
   {
      return(0);
   }
}
#else
static char getchar_timeout(int timeout)
{(void)timeout;}
#endif

static struct pt monitor_input_pt;
mon_timer_t input_timer;

volatile uint8_t monitor_running = 1;
volatile uint8_t monitor_uploading = 1;
volatile uint8_t monitor_is_connected = 1;

static char set_input = 0;

#define sizearray(a)  (sizeof(a) / sizeof((a)[0]))
CONST char config_inifile[] = "config.ini";

/*---------------------------------------------------------------------------*/

#ifdef _WIN32
static
PT_THREAD(monitor_set_input(struct pt *pt))
{

  PT_BEGIN(pt);
  while(1)
  {
	  timer_set(&input_timer, 30*1000); // 30s
	  PT_WAIT_UNTIL(pt, timer_expired(&input_timer));
	  set_input = 's';
  }
  PT_END(pt);
}
#endif

#define MASK32  ((uint32_t)(-1))

static
PT_THREAD(monitor_write_thread(struct pt *pt, uint8_t _monitor))
{

  clock_t time_before, time_now;
    
  uint32_t time_elapsed = 0;
  uint32_t period = (uint32_t)monitor_state[_monitor].config_h.time_interv*1000;
  mon_timer_t* timer = &monitor_state[_monitor].write_timer;
	  
  PT_BEGIN(pt);
  
  time_elapsed = (uint32_t)(clock_time()%period);  
  timer_set(timer, (uint32_t)(period - time_elapsed));
  
  while(1)
  {		
		PT_WAIT_UNTIL(pt, monitor_running && timer_expired(timer));
		
		time_elapsed = (uint16_t)timer_elapsed(timer);	
		
		// wait only the remaining time
		if(time_elapsed < period)
		{
			timer_set(timer, (uint32_t)(period - time_elapsed));
		}else
		{
			timer_set(timer, (uint32_t)period/10);
		}
		time_before = clock_time();
		PRINTF("M %d W start @%d\r\n", _monitor, (uint32_t)(time_before & MASK32));
		
		monitor_writer(_monitor);
		
		time_now = clock_time();
		time_elapsed = (uint32_t)(time_now-time_before);
		PRINTF("M %d W end @%d, diff %d\r\n", _monitor, (uint32_t)(time_now & MASK32), time_elapsed);
  }
  PT_END(pt);
}

static
PT_THREAD(monitor_read_thread(struct pt *pt, uint8_t _monitor))
{

#define TIMER_READER_MS  1000	

  clock_t time_before, time_now;
  mon_timer_t* timer = &monitor_state[_monitor].read_timer;
  uint32_t time_elapsed = 0;
  
  PT_BEGIN(pt);  

  while(1)
  {		
	  	timer_set(timer, TIMER_READER_MS);
		PT_WAIT_UNTIL(pt, monitor_uploading && timer_expired(timer));
		
		time_before = clock_time();
		PRINTF("M %d R start @%d\r\n", _monitor, (uint32_t)(time_before & MASK32));
		
		monitor_reader(_monitor);
		
		time_now = clock_time();
		
		time_elapsed = (uint32_t)(time_now-time_before);
		PRINTF("M %d R end @%d, diff %d\r\n", _monitor, (uint32_t)(time_now & MASK32), time_elapsed);
  }
  PT_END(pt);
}

#include <string.h> /* memcpy, memset */
#ifdef _WIN32
#include <stdio.h> /* SNPRINTF */
#endif


//#define API_KEY  "90a004390f3530d0ba10199ac2b1ac3d"
//#define SERVER_NAME "emon-gpsnetcms.rhcloud.com"

#if 0
#define END_STRING "HTTP/1.1\r\nHost: emon-gpsnetcms.rhcloud.com\r\n\r\n\r\n"
#define SEND_STRING "GET /input/post.json?json={p:3}&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1\r\nHost: emon-gpsnetcms.rhcloud.com\r\n\r\n\r\n"
#define SEND_STRING1 "GET /input/post.json?json={"
#define SEND_STRING2 ("}&apikey=" API_KEY " HTTP/1.1\r\nHost: " SERVER_NAME "\r\n\r\n\r\n")
#define SEND_STRING3 "}&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1\r\nHost: emon-gpsnetcms.rhcloud.com\r\n\r\n\r\n"
#endif

//#define DEBUG
#if DEBUG == 1 
#define dprintf(...)	printf(__VA_ARGS__)
#else
#define dprintf(...)
#endif

#if 0
uint8_t build_data_vector(char* ptr_data, uint8_t *data, uint8_t len)
{
	uint16_t offset = 0;
	uint16_t max_len = 4*len;

	while(len > 0)
	{
		len--;
		offset = SNPRINTF(ptr_data, max_len,"%d,", *data);
		if(offset < 0 || offset >= max_len)
		{
			return 1;
		}
		data++;
		ptr_data+= offset;
	}
	*(--ptr_data) = '\0'; // null terminate string
	return 0;
}
#endif


#define StringToInteger(value) strtoul(value,NULL,0);

static int mon_cnt = 0;
static int field_cnt = 0;

static int callback_inifile(const char *section, const char *key, const char *value, const void *userdata)
{
     
    (void)userdata;

    /* configura monitores */
    if(strcmp(section,"Config") == 0)
    {

		if(strcmp(key,"num_monitores") == 0)
		{
			//num_monitores = (uint8_t)strtoul(value,NULL,0);
			num_monitores = (uint8_t)StringToInteger((char*)value);
			
			if(num_monitores > MAX_NUM_OF_MONITORES)
			{
				print_erro(monitor_error_msg[0]);
				print_erro("num_monitores superior ao suportado\n\r.");
			}else
			{
				config_check.bit.num_mon_ok=1;
			}
		}

		if(strcmp(key,"simon_server") == 0)
		{
			simon_set_hostname(value);
			config_check.bit.server_ok = 1;
		}

		if(strcmp(key,"simon_ip") == 0)
		{
			simon_set_hostip(value);
			config_check.bit.ip_ok = 1;
		}
		if(strcmp(key,"api_key") == 0)
		{
			simon_set_apikey(value);
			config_check.bit.key_ok = 1;
		}
		if(strcmp(key,"gprs_apn") == 0)
		{
			//simon_set_apikey(value);
			config_check.bit.gprs_apn_ok = 1;
		}
    }

  	if(strcmp(section,"Monitor") == 0)
	{
  	    if(mon_cnt >= num_monitores)
  	    {
  	    	return FALSE;
  	    }

  	   /* configura monitores */
  	   if(strcmp(key,"slave") == 0)
  	   {
  	  			monitor_state[mon_cnt].slave_addr =  (uint8_t)StringToInteger((char*)value); //strtoul(value,NULL,0);
  	  			++field_cnt;
  	    }
  	  		
		if(strcmp(key,"codigo") == 0)
		{
			monitor_state[mon_cnt].codigo =  (uint8_t)StringToInteger((char*)value); //strtoul(value,NULL,0);
			monitor_state[mon_cnt].config_h.mon_id = monitor_state[mon_cnt].codigo;
			++field_cnt;
		}
		if(strcmp(key,"nome") == 0)
		{
			strncpy(monitor_state[mon_cnt].monitor_dir_name, value, sizearray(monitor_state[mon_cnt].monitor_dir_name));
			++field_cnt;
		}
		if(strcmp(key,"intervalo") == 0)
		{
			monitor_state[mon_cnt].config_h.time_interv = (uint16_t)StringToInteger((char*)value); //strtoul(value,NULL,0);
			++field_cnt;
		}

		if(strcmp(key,"tamanho") == 0)
		{
			monitor_state[mon_cnt].config_h.entry_size = (uint16_t)StringToInteger((char*)value); //strtoul(value,NULL,0);
			++field_cnt;
		}
		if(field_cnt == NUM_OF_FIELDS)
		{
			field_cnt = 0;
			monitor_state[mon_cnt].state = IN_USE;
			++mon_cnt;
		}
		return TRUE;

	}
  	return TRUE;
}

static void config_check_erro(void)
{
	int erro = 0;
	if(config_check.bit.num_mon_ok == 0)
	{
		print_erro(monitor_error_msg[0]);
		print_erro("num_monitores ou maior que %d \n\r.", MAX_NUM_OF_MONITORES);
		erro++;
	}
	if(config_check.bit.server_ok == 0)
	{
		
		print_erro(monitor_error_msg[0]);
		print_erro("simon server \n\r.");
		erro++;
	}
	if(config_check.bit.ip_ok == 0)
	{
		print_erro(monitor_error_msg[0]);
		print_erro("simon ip \n\r.");
	}
	if(config_check.bit.key_ok == 0)
	{
		print_erro(monitor_error_msg[0]);
		print_erro("apikey \n\r.");
		erro++;
	}
	if(config_check.bit.gprs_apn_ok == 0)
	{
		print_erro(monitor_error_msg[0]);
		print_erro("gprs server\n\r.");		
	}
	if (erro)
	{
		sleep_forever();
	}
}

#ifdef _WIN32
void main_monitor(void);

int main(void)
{
	main_monitor();
	return 0;
}
#endif

#include "modbus_slaves.h"
extern CONST modbus_slave_t * modbus_slaves_all[];

#include "simon-api.h"

void main_monitor(void)
{

	uint8_t monitor_num = 0;
	
#define TESTES 0	
#if TESTES		
	struct tm ts;
	char server_reply[]="Date: Wed, 02 Sep 2015 19:01:30 GMT";
	get_server_time(server_reply, &ts);
#endif
	
#ifdef _WIN32
	struct timeb start, end;
	uint16_t diff;
#else
	uint8_t status = 0;
#endif	
	  
#if _WIN32
	extern const modem_driver_t win_http;
	if(simon_init(&win_http) != MODEM_OK)
	{
		print_erro ("Simon init error\r\n");
	}
#else
	/* modem gprs driver */
	extern const modem_driver_t m590_driver;
	if(simon_init(&m590_driver) != MODEM_OK)
	{
		print_erro ("Simon init error\r\n");
	}
#endif

#if _WIN32	
	PT_INIT(&monitor_input_pt);
	PRINTF("help:\r\nq-quit\r\np-stop logger\r\nc-continue logger\r\ns-synch\r\nu-start upload\r\nv-stop upload\r\n");
	ftime(&start);

	struct tm t;
	simon_get_time(&t);
	printf ("Current local time and date: %s", asctime(&t));
	fflush(stdout);
#endif

#ifndef _WIN32		
		/* Detect and init the SD card */
		while(SDCard_ResourceInit(SDCARD_MUTEX_PRIORITY) == NULL)
		{
			DelayTask(1000);
		}
		do
		{
			status = SDCard_Init(VERBOSE_OFF);
			DelayTask(1000);
		} while (status != SD_OK);
#endif		
		
	/* Read config.ini file and check configuration */
	config_check.byte = 0;
	ini_browse(callback_inifile, NULL, config_inifile);
	config_check_erro();

	print_debug("Config OK\r\n");
	
#if COLDUINO || ARDUINO
	DelayTask(5000);	
#endif

	/* init monitors */
	monitores_em_uso = 0;
	for (monitor_num = 0; monitor_num < num_monitores; monitor_num++)
	{		
		if(monitor_state[monitor_num].state != IN_USE			
			|| monitor_init(monitor_num) != TRUE)
		{
			print_erro(monitor_error_msg[1], monitor_num);
			sleep_forever();
		}
		
		/* monitor MODBUS? */
	
		if(monitor_state[monitor_num].codigo < MODBUS_NUM_SLAVES)
		{
			if(modbus_slaves_all[monitor_state[monitor_num].codigo] == NULL) goto modbus_slave_erro;
			if(modbus_slaves_all[monitor_state[monitor_num].codigo]->slave_reader == NULL) goto modbus_slave_erro;			
			monitor_state[monitor_num].read_data = modbus_slaves_all[monitor_state[monitor_num].codigo]->slave_reader;			
		}else
		{
			modbus_slave_erro:				
			print_erro(monitor_error_msg[1], monitor_num);
			print_erro("modbus slave não suportado \r\n");
			sleep_forever();
		}		
		
		monitores_em_uso++;
		
		/* Inicializa as threads deste monitor */
		PT_INIT(&monitor_state[monitor_num].read_pt);
		PT_INIT(&monitor_state[monitor_num].write_pt);
				
		monitor_state[monitor_num].time_to_send = 0;
		monitor_state[monitor_num].avg_time_to_send = 0;
	}
	
#ifdef _WIN32	
	fflush(stdout);
#else
	DelayTask(5000);
#endif	


	while(1)
	{

		for (monitor_num = 0; monitor_num < monitores_em_uso; monitor_num++)
		{
			monitor_write_thread(&monitor_state[monitor_num].write_pt, monitor_num);
			monitor_read_thread(&monitor_state[monitor_num].read_pt, monitor_num);
		}

#ifdef _WIN32			
		monitor_set_input(&monitor_input_pt);
#endif		

#if 0
		char c;
		
		c=getchar_timeout(1);
		
		if(c == 0 && set_input != 0)
		{
			c=set_input;
		}

		switch(c)
		{
			case 'q': 				// parar
				goto out;
			case 's': monitor_is_connected = 1;
					break;
			case 'c': monitor_running = 1; // iniciar ou continuar
				break;
			case 'p': monitor_running = 0; // parar
				break;
			case 'u': monitor_uploading = 1; // iniciar ou continuar upload
				break;
			case 'v': monitor_uploading = 0; // parar upload
				break;
		}
#endif		
		
		#ifndef _WIN32
			DelayTask(1000); // executa a cada 1000ms
		#endif
		
	}

	out:

#ifdef _WIN32
	ftime(&end);
	diff = (uint16_t) (1000.0 * (end.time - start.time)
		+ (end.millitm - start.millitm));

	printf("\nOperation took %u milliseconds\n", diff);
	getchar();
#else
	sleep_forever:
	sleep_forever();
#endif

	return;

}

#ifdef _WIN32
void sleep_forever(void)
{
	exit(0);
}
#endif
