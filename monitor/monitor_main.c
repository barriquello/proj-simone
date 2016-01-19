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

#ifdef _WIN32
#include <stdio.h>
#include "http_client.h"
#endif

#if COLDUINO || ARDUINO
#include "printf_lib.h"
#endif

#include "minIni.h"
#include "assert.h"
#include "monitor.h"
#include "simon-api.h"

static int8_t 	num_monitores;
static uint8_t 	monitores_em_uso = 0;
monitor_state_t monitor_state[MAX_NUM_OF_MONITORES];
monitor_config_ok_t config_check;

#define VERBOSE_INIT_VALUE			0
uint8_t mon_verbosity = VERBOSE_INIT_VALUE;

#define MS2TICKS(x)	(x)


/* print output */
#define DEBUG_MONITOR		1
#undef PRINTS_ENABLED

#if DEBUG_MONITOR
#define PRINTS_ENABLED  1
char BufferText[32];
#else
#define PRINTS_ENABLED  0
#endif
#include "prints_def.h"

#ifndef CONST
#define CONST const
#endif

/* Debug strings */
#define monitor_error_msg0_def		"\r\nConfig erro: faltando "
#define monitor_error_msg1_def		"\r\nMon erro: %d "
#define monitor_error_msg2_def		"\r\nMon %d"

#if ARDUINO
char BufferText[32];
const char monitor_error_msg0[] PROGMEM = monitor_error_msg0_def;
const char monitor_error_msg1[] PROGMEM = monitor_error_msg1_def;
const char monitor_error_msg2[] PROGMEM = monitor_error_msg2_def;
PGM_P CONST monitor_error_msg[] PROGMEM =
{
	monitor_error_msg0,
	monitor_error_msg1,
	monitor_error_msg2	
};
#else
const char* monitor_error_msg[] =
{
	monitor_error_msg0_def,
	monitor_error_msg1_def,
	monitor_error_msg2_def
};
#endif
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

static clock_t my_clock = 0;

clock_t clock_time(void)
{
  clock_t local;
  
  OS_SR_SAVE_VAR;
  
  OSEnterCritical();
  	  local = my_clock;
  OSExitCritical();
  //PRINTF_P(PSTR("\r\nClock now: %d \r\n"), local);
  return local;
}

void BRTOS_TimerHook(void)
{
	my_clock++;
}
#endif /* _WIN32 */

static uint8_t timer_expired(mon_timer_t *t)
{ return (uint8_t)((clock_time() - t->start) >= (clock_t)t->interval);}

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
#endif

volatile uint8_t monitor_running = 1;
volatile uint8_t monitor_uploading = 1;
volatile uint8_t monitor_is_connected = 1;
volatile uint8_t monitor_is_idle = 0;
volatile uint8_t monitor_modem_null = 0;

monitors_state_t  monitors_state = {0};

CONST char config_inifile[] = "config.ini";

/*---------------------------------------------------------------------------*/

#ifdef _WIN32
static struct pt monitor_input_pt;
static char set_input = 0;
mon_timer_t input_timer;

/* Input thread */
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

/* Monitor writer thread */
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
		if(mon_verbosity > 6 && is_terminal_idle()) PRINTF_P(PSTR("\r\nThread W %u, timer: %u \r\n"), _monitor, period);
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
		if(mon_verbosity > 6 && is_terminal_idle()) PRINTF_P(PSTR("\r\nThread W %u, time now: %lu \r\n"), _monitor, time_before);
		
		monitor_writer(_monitor);	
			
		time_now = clock_time();		
		time_elapsed = (uint16_t)(time_now-time_before);
		
		if(is_terminal_idle() && mon_verbosity > 3)
		{
			PRINTF_P(PSTR("M %u W start @%lu\r\n"), _monitor, (uint32_t)(time_before & MASK32));
			PRINTF_P(PSTR("M %u W end @%lu, diff %lu\r\n"), _monitor, (uint32_t)(time_now & MASK32), time_elapsed);
		}
  }
  PT_END(pt);
}

/* Monitor reader thread */
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
		
		if(mon_verbosity > 6 && is_terminal_idle()) PRINTF_P(PSTR("\r\nThread R %u \r\n"), _monitor);
		PT_WAIT_UNTIL(pt, monitor_uploading && monitor_state[_monitor].uploading && timer_expired(timer));
		
		time_before = clock_time();		
		if(monitor_state[_monitor].sending == 0)
		{
			monitor_state[_monitor].reader_upload_start_time = time_before;
		}
		
		if(mon_verbosity > 6 && is_terminal_idle()) PRINTF_P(PSTR("\r\nThread R %u, time now: %lu \r\n"), _monitor, time_before);
		
		if(monitor_reader(_monitor) < MAX_NUM_OF_ENTRIES)
		{			
			time_now = clock_time();			
			time_elapsed = (uint32_t)(time_now-time_before);
			
			if(is_terminal_idle() && mon_verbosity > 3)
			{
				PRINTF_P(PSTR("M %u R start @%lu\r\n"), _monitor, (uint32_t)(time_before & MASK32));
				PRINTF_P(PSTR("M %u R end @%lu, diff %lu\r\n"), _monitor, (uint32_t)(time_now & MASK32), time_elapsed);
			}
			
			/* log stats */
			time_before = monitor_state[_monitor].reader_upload_start_time;
			time_elapsed = (uint32_t)(time_now-time_before);
			monitor_state[_monitor].reader_upload_time = time_elapsed;
			monitor_state[_monitor].reader_upload_time_avg = ((monitor_state[_monitor].reader_upload_time_avg*7) + time_elapsed)/8;
			
		}				
  }
  PT_END(pt);
}

#include <string.h> /* memcpy, memset */
#ifdef _WIN32
#include <stdio.h> /* SNPRINTF */
#endif

#define StringToInteger(value) strtoul(value,NULL,0);

static int mon_cnt = 0;
static int field_cnt = 0;

static int callback_inifile(const char *section, const char *key, const char *value, const void *userdata)
{
     
    (void)userdata;

    /* configura monitores */
    if(strcmp_P(section,PSTR("Config")) == 0)
    {

		if(strcmp_P(key,PSTR("num_monitores")) == 0)
		{
			num_monitores = (uint8_t)StringToInteger((char*)value);
			
			if(num_monitores > MAX_NUM_OF_MONITORES)
			{
				PRINTS_ERRO_PP(monitor_error_msg[0]);
				PRINTS_ERRO_P(PSTR("num_monitores superior ao suportado\n\r."));
					
			}else
			{
				config_check.bit.num_mon_ok=1;
				PRINTS_P(PSTR("num_monitores: "));
				PRINTF(value);
			}
		}

		if(strcmp_P(key,PSTR("simon_server")) == 0)
		{
			simon_set_hostname(value);
			config_check.bit.server_ok = 1;
			PRINTS_P(PSTR("simon_server: "));
			PRINTF(value);
		}

		if(strcmp_P(key,PSTR("simon_ip")) == 0)
		{
			simon_set_hostip(value);
			config_check.bit.ip_ok = 1;
			PRINTS_P(PSTR("simon_ip: "));
			PRINTF(value);
		}
		if(strcmp_P(key,PSTR("api_key")) == 0)
		{
			simon_set_apikey(value);
			config_check.bit.key_ok = 1;
			PRINTS_P(PSTR("api_key: "));
			PRINTF(value);
		}
		if(strcmp_P(key,PSTR("gprs_apn")) == 0)
		{
			simon_set_gprs_config(value);
			config_check.bit.gprs_apn_ok = 1;
			PRINTS_P(PSTR("gprs_apn: "));
			PRINTF(value);
		}
		PRINTS_P(PSTR("\r\n"));
    }

  	if(strcmp_P(section,PSTR("Monitor")) == 0)
	{
  	    if(mon_cnt >= num_monitores)
  	    {
  	    	return FALSE;
  	    }

  	   /* configura monitores */
  	   if(strcmp_P(key,PSTR("slave")) == 0)
  	   {
  	  			monitor_state[mon_cnt].slave_addr =  (uint8_t)StringToInteger((char*)value);
  	  			++field_cnt;
  	    }
  	  		
		if(strcmp_P(key,PSTR("codigo")) == 0)
		{
			monitor_state[mon_cnt].codigo =  (uint8_t)StringToInteger((char*)value);
			monitor_state[mon_cnt].config_h.mon_id = monitor_state[mon_cnt].codigo;
			++field_cnt;
		}
		if(strcmp_P(key,PSTR("nome")) == 0)
		{
			strncpy(monitor_state[mon_cnt].monitor_dir_name, value, SIZEARRAY(monitor_state[mon_cnt].monitor_dir_name));
			++field_cnt;
		}
		if(strcmp_P(key,PSTR("intervalo")) == 0)
		{
			monitor_state[mon_cnt].config_h.time_interv = (uint16_t)StringToInteger((char*)value);
			++field_cnt;
		}

		if(strcmp_P(key,PSTR("tamanho")) == 0)
		{
			monitor_state[mon_cnt].config_h.entry_size = (uint16_t)StringToInteger((char*)value);
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
		PRINTS_ERRO_PP(monitor_error_msg[0]);
		PRINT_ERRO_P(PSTR("num_monitores ou maior que %d \n\r."), MAX_NUM_OF_MONITORES);
		erro++;
	}
	if(config_check.bit.server_ok == 0)
	{
		PRINTS_ERRO_PP(monitor_error_msg[0]);
		PRINTS_ERRO_P(PSTR("simon server \n\r."));
		erro++;
	}
	if(config_check.bit.ip_ok == 0)
	{
		PRINTS_ERRO_PP(monitor_error_msg[0]);
		PRINTS_ERRO_P(PSTR("simon ip \n\r."));		
	}
	if(config_check.bit.key_ok == 0)
	{

		PRINTS_ERRO_PP(monitor_error_msg[0]);
		PRINTS_ERRO_P(PSTR("apikey \n\r."));		
		erro++;
	}
	if(config_check.bit.gprs_apn_ok == 0)
	{
		PRINTS_ERRO_PP(monitor_error_msg[0]);
		PRINTS_ERRO_P(PSTR("gprs server\n\r."));
		erro++;			
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

#include "simon-api.h"
#include "modbus_slaves.h"
extern CONST modbus_slave_t * modbus_slaves_all[];

void main_monitor(void)
{

	int8_t monitor_num = 0;
	
	#define TESTES 0
	#if TESTES
		#include "time_lib.h"
		#include "simon-api.h"
		struct tm ts;
		static struct tm timestamp;
		time_t time_now;
		char server_reply_test[]="Date: Wed, 02 Sep 2015 19:01:30 GMT";
		get_server_time(server_reply_test, &ts);
		time_now = mktime(&ts);
		timestamp = *((struct tm *)localtime(&(time_t){time_now}));
	#endif
	
#ifdef _WIN32
	struct timeb start, end;
	uint16_t diff;
#else
	uint8_t status = 0;
#endif	  

	DelayTask(MS2TICKS(1000));
	
	#if (COLDUINO || ARDUINO) && !SIMULATION
	/* Detect and init the SD card */
	while(SDCard_ResourceInit(SDCARD_MUTEX_PRIORITY) == NULL)
	{
		DelayTask(MS2TICKS(1000));
	}
	do
	{
		status = SDCard_Init(VERBOSE_OFF);
		DelayTask(MS2TICKS(1000));
	} while (status != SD_OK);
	#endif
	
	/* Read config.ini file and check configuration */
	config_check.byte = 0;
	ini_browse(callback_inifile, NULL, config_inifile);
	config_check_erro();

	DPRINTS_P(PSTR("Config OK\r\n"));

	terminal_acquire();
	PRINTS_P(PSTR("Config OK\r\n"));
	terminal_release();
	
	/* modem gprs driver */	
#if _WIN32
#define modem_driver	win_http
#elif MODEM_PRESENTE
#define modem_driver	gc864_modem_driver //m590_driver
#else
#define modem_driver	null_modem_driver
#endif	
	
	extern const modem_driver_t modem_driver;
	extern const modem_driver_t null_modem_driver;
		
	modem_driver_t *_modem = &modem_driver;
	while(simon_init(_modem) != MODEM_OK)
	{			
		PRINTS_ERRO_P(PSTR("\r\nSimon init error\r\n"));
		DelayTask(MS2TICKS(10000));
		if(monitor_modem_null == 1)
		{
			_modem = &null_modem_driver;			
		}
	}

	PRINTS_ERRO_P(PSTR("\r\nSimon init OK\r\n"));	
		
#if _WIN32	
	PT_INIT(&monitor_input_pt);
	PRINTF("help:\r\nq-quit\r\np-stop logger\r\nc-continue logger\r\ns-synch\r\nu-start upload\r\nv-stop upload\r\n");
	ftime(&start);

	struct tm t;
	simon_get_time(&t);
	printf ("Current local time and date: %s", asctime(&t));
	fflush(stdout);
#endif
		
#if COLDUINO || ARDUINO
	DelayTask(MS2TICKS(1000));	
#endif

	/* init monitors */
	monitores_em_uso = 0;
	for (monitor_num = 0; monitor_num < num_monitores; monitor_num++)
	{		
		if(monitor_state[monitor_num].state != IN_USE			
			|| monitor_init(monitor_num) != TRUE)
		{
			PRINT_ERRO_PP(monitor_error_msg[1], monitor_num);
			sleep_forever();
		}
		
		/* configura monitor MODBUS */	
		if(monitor_state[monitor_num].codigo < MODBUS_NUM_SLAVES)
		{
			if(modbus_slaves_all[monitor_state[monitor_num].codigo] == NULL) goto modbus_slave_erro;
			if(modbus_slaves_all[monitor_state[monitor_num].codigo]->slave_reader == NULL) goto modbus_slave_erro;			
			monitor_state[monitor_num].read_data = modbus_slaves_all[monitor_state[monitor_num].codigo]->slave_reader;	
					
		}else
		{
			modbus_slave_erro:			
			PRINT_ERRO_PP(monitor_error_msg[1], monitor_num);
			PRINTS_ERRO_P(PSTR("modbus slave nao suportado \r\n"));		
			sleep_forever();
		}		
		PRINT_ERRO_PP(monitor_error_msg[2], (uint8_t)(monitor_num & 0xFF)); PRINTS_ERRO_P(PSTR(" started\r\n"));
		monitores_em_uso++;
		
		/* Inicializa as threads deste monitor */
		PT_INIT(&monitor_state[monitor_num].read_pt);
		PT_INIT(&monitor_state[monitor_num].write_pt);
				
		monitor_state[monitor_num].time_to_send = 0;
		monitor_state[monitor_num].avg_time_to_send = 0;
		monitor_state[monitor_num].sinc = 0;
		monitor_state[monitor_num].written_entries = 0;
		monitor_state[monitor_num].total_written_entries = 0;		
		monitor_state[monitor_num].sent_entries = 0;
		monitor_state[monitor_num].read_entries = 0;
		monitor_state[monitor_num].sending = 0;
		monitor_state[monitor_num].uploading = 1; /* enable data uploading */
		
		/* hack to disable slave TS uploading */
		if(monitor_state[monitor_num].codigo == MODBUS_TS)
		{
			monitor_state[monitor_num].uploading = 0;
		}
	}
	
#ifdef _WIN32	
	fflush(stdout);
#else
	DelayTask(MS2TICKS(1000));
#endif	

	if(mon_verbosity > 3)  PRINTF_P(PSTR("\r\nMonitor threads running with %u monitors... \r\n"), monitores_em_uso);	
	
	monitors_state.time_started = (time_t)(clock_time()/1000);
	
	int8_t sending_mon = 0;
	
	/* run forever */
	while(1)
	{
				
		monitor_is_idle = 0;
		
		for (monitor_num = 0; monitor_num < monitores_em_uso; monitor_num++)
		{
			monitor_write_thread(&monitor_state[monitor_num].write_pt, monitor_num);
		}
		
		/* read next to send */		
		monitor_read_thread(&monitor_state[sending_mon].read_pt, sending_mon);
		
		if(monitor_state[sending_mon].sending == 0)
		{
			if(++sending_mon == monitores_em_uso)
			{
				sending_mon = 0;
			}
		}		
		monitor_is_idle = 1;
		
		
#ifdef _WIN32			
		monitor_set_input(&monitor_input_pt);
#endif

#ifdef _WIN32
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
			DelayTask(MS2TICKS(1000)); // executa a cada 1000ms			
		#endif

		
	}

#ifdef _WIN32
	ftime(&end);
	diff = (uint16_t) (1000.0 * (end.time - start.time)
		+ (end.millitm - start.millitm));

	printf("\nOperation took %u milliseconds\n", diff);
	getchar();
#else
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
