/*
 ============================================================================
 Name        : monitor_main.c
 Author      : Carlos H. Barriquello
 Version     :
 Description : Data logger
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

#include "printf_lib.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
#include <stdio.h>
#endif

#include "assert.h"
#include "minIni.h"
#include "monitor.h"
#include "simon-api.h"

#include "SD_API.h"
#include "AppConfig.h"

static uint8_t 	num_monitores = MAX_NUM_OF_LOGGERS;
static uint8_t 	logger = 0;
log_state_t 	logger_state[MAX_NUM_OF_LOGGERS];
log_config_ok_t config_check;


#ifdef _WIN32
#define DEBUG_MONITOR 1
#endif

#if DEBUG_MONITOR
#define PRINTF(...) printf(__VA_ARGS__);
#else
#define PRINTF(...)
#endif

#if PLATAFORMA == COLDUINO
#define CONST
#else
#define CONST const
#endif

/*---------------------------------------------------------------------------*/
/*
 * Finally, the implementation of the simple timer library follows.
 */

#ifdef _WIN32
#include <windows.h>
#include <time.h>
#include <sys\timeb.h>
#else
#include "time_lib.h"
#include "utils.h"
#endif

/*---------------------------------------------------------------------------*/
/*
 * The following definitions are just for the simple timer library
 * used in this example. The actual implementation of the functions
 * can be found at the end of this file.
 */
typedef unsigned long long clock_t;
struct timer { clock_t start, interval; };
static clock_t  timer_expired(struct timer *t);
static void timer_set(struct timer *t, int usecs);
/*---------------------------------------------------------------------------*/
void sleep_forever(void);


#if _WIN32
void wait (unsigned int secs) {
	unsigned int retTime = time(0) + secs;     // Get finishing time.
    while (time(0) < retTime);    // Loop until it arrives.
}


#include "conio.h"
char getchar_timeout(int timeout)
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
char getchar_timeout(int timeout)
{(void)timeout;}
#endif

/* We must always include pt.h in our protothreads code. */
#include "pt.h"

static struct pt log_read_pt, log_write_pt,log_input_pt;
/*
 * We use two timers: one for the log write protothread and
 * one for the log read protothread.
 */
static struct timer logread_timer, logwrite_timer, log_input_timer;
volatile uint8_t log_running = 1;
volatile uint8_t log_uploading = 1;
volatile uint8_t log_is_connected = 0;

static char set_input = 0;

#define sizearray(a)  (sizeof(a) / sizeof((a)[0]))
CONST char config_inifile[] = "config.ini";

/*---------------------------------------------------------------------------*/

static
PT_THREAD(log_set_input(struct pt *pt))
{

  PT_BEGIN(pt);
  while(1)
  {
	  timer_set(&log_input_timer, 30*1000); // 30s
	  PT_WAIT_UNTIL(pt, timer_expired(&log_input_timer));
	  set_input = 's';
  }
  PT_END(pt);
}

static
PT_THREAD(log_write_thread(struct pt *pt))
{

  PT_BEGIN(pt);
  while(1)
  {
		timer_set(&logwrite_timer, logger_state[logger].config_h.time_interv*1000);
		PT_WAIT_UNTIL(pt, log_running && timer_expired(&logwrite_timer));
		monitor_writeentry(logger);
  }
  PT_END(pt);
}

static
PT_THREAD(log_read_thread(struct pt *pt))
{

  PT_BEGIN(pt);
  while(1)
  {
		timer_set(&logread_timer, 1000);
		PT_WAIT_UNTIL(pt, log_uploading && timer_expired(&logread_timer));
		monitor_readentry(logger);

  }
  PT_END(pt);
}

#ifdef _WIN32

static clock_t clock_time(void)
{ return (clock_t)GetTickCount(); }

#else /* _WIN32 */

	
static clock_t clock = 0;
static clock_t clock_time(void)
{
  return clock;
}

void BRTOS_TimerHook(void)
{
	clock++;
}

#endif /* _WIN32 */

static clock_t timer_expired(struct timer *t)
{ return (clock_t)(clock_time() - t->start) >= (clock_t)t->interval; }

static void timer_set(struct timer *t, int interval)
{ t->interval = interval; t->start = clock_time(); }
/*---------------------------------------------------------------------------*/

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


int Callback_inifile(const char *section, const char *key, const char *value, const void *userdata)
{
  
    static int mon_cnt = 0;
    static int field_cnt = 0;
    
    (void)userdata;

    /* configura monitores */
    if(strcmp(section,"Config") == 0)
    {

		if(strcmp(key,"num_monitores") == 0)
		{
			num_monitores = strtoul(value,NULL,0);
			if(num_monitores > MAX_NUM_OF_LOGGERS)
			{
				PRINTF("Erro: num_monitores superior ao suportado\n\r.");
			}else
			{
				config_check.bit.num_mon_ok=1;
			}
		}

		if(strcmp(key,"simon_server") == 0)
		{
			//strncpy(simon_hostname, value, sizearray(simon_hostname));
			simon_set_hostname(value);
			config_check.bit.server_ok = 1;
		}
		if(strcmp(key,"api_key") == 0)
		{
			//strncpy(apikey, value, sizearray(apikey));			
			simon_set_apikey(value);
			config_check.bit.key_ok = 1;
		}
    }

  	if(strcmp(section,"Monitor") == 0)
	{
  	    if(mon_cnt >= num_monitores)
  	    {
  	    	return 0;
  	    }

  		if(field_cnt == 0)
  		{
  			logger_state[mon_cnt].sync_state = NOT_SYNC;
  		}

		/* configura monitores */
		if(strcmp(key,"id") == 0)
		{
			logger_state[mon_cnt].config_h.mon_id = strtoul(value,NULL,0);
			++field_cnt;
		}

		if(strcmp(key,"nome") == 0)
		{
			strncpy(logger_state[mon_cnt].log_dir_name, value, sizearray(logger_state[mon_cnt].log_dir_name));
			++field_cnt;
		}
		if(strcmp(key,"intervalo") == 0)
		{
			logger_state[mon_cnt].config_h.time_interv = strtoul(value,NULL,0);
			++field_cnt;
		}

		if(strcmp(key,"tamanho") == 0)
		{
			logger_state[mon_cnt].config_h.entry_size = strtoul(value,NULL,0);
			++field_cnt;
		}
		if(field_cnt == NUM_OF_FIELDS)
		{
			field_cnt = 0;
			++mon_cnt;
		}
		return 1;

	}
  	return 1;
}

void config_check_erro(void)
{
	int erro = 0;
	if(config_check.bit.num_mon_ok == 0)
	{
		print_erro("Config Erro: faltando num_monitores ou maior que %d \n\r.", MAX_NUM_OF_LOGGERS);
		erro++;
	}
	if(config_check.bit.server_ok == 0)
	{
		print_erro("Config Erro: faltando simon server \n\r.");
		erro++;
	}
	if(config_check.bit.key_ok == 0)
	{
		print_erro("Config Erro: faltando apikey \n\r.");
		erro++;
	}
	if(config_check.bit.gprs_server_ok == 0)
	{
		print_erro("Config Erro: faltando gprs server \n\r.");
	}
	if (erro)
	{
		sleep_forever();
	}
}

void main_monitor(void)
{

#ifdef _WIN32
	struct timeb start, end;
	uint16_t diff;
#else
	INT8U status = 0;
#endif	

	
	uint8_t log_num = 0;

	 /* Initialize the protothread state variables with PT_INIT(). */
	  PT_INIT(&log_read_pt);
	  PT_INIT(&log_write_pt);

	PRINTF("help:\r\nq-quit\r\np-stop logger\r\nc-continue logger\r\ns-synch\r\nu-start upload\r\nv-stop upload\r\n");

#ifdef _WIN32
	ftime(&start);
#endif	

#if _WIN32
	struct tm t;
	http_get_time(&t);
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
		
	
	config_check.byte = 0;
	ini_browse(Callback_inifile, NULL, config_inifile);
	config_check_erro(); /* check configuration */

	for (log_num = 0; log_num < num_monitores; log_num++)
	{
		if(log_init(log_num))
		{
			PRINTF("Log init erro: %d", log_num);
			sleep_forever();
		}
	}
	
#ifdef _WIN32	
	fflush(stdout);
#endif	

	while(1)
	{
		char c;

		log_write_thread(&log_write_pt);
		log_read_thread(&log_read_pt);

		log_set_input(&log_input_pt);

		c=getchar_timeout(1);
		if(c == 0 && set_input != 0)
		{
			c=set_input;
		}

		switch(c)
		{
			case 'q': 				// parar
				goto out;
			case 's': log_is_connected = 1;
					break;
			case 'c': log_running = 1; // iniciar ou continuar
				break;
			case 'p': log_running = 0; // parar
				break;
			case 'u': log_uploading = 1; // iniciar ou continuar upload
				break;
			case 'v': log_uploading = 0; // parar upload
				break;
		}
		#ifndef _WIN32
			DelayTask(1000); // executa a cada 1s
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
	while(1)
	{
		/* sleep forever */
		__RESET_WATCHDOG();
	}
#endif

	return;

}

void sleep_forever(void)
{

	while(1)
	{
		#ifndef _WIN32
			/* sleep forever */
			DelayTask(1000);
		#endif
	}
}


#if 1

void InitializeUART(void);
void WriteUARTN(char c);
char ReadUARTN(void);

void InitializeUART(void)
{
		
}


void WriteUARTN(char c)
{
	(void)c;
	
}


char ReadUARTN(void)
{
	return 0;
}
#endif


