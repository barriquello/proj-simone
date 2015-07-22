/*
 ============================================================================
 Name        : Test_logger.c
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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"
//#include <sys\timeb.h>

#include "minIni.h"
#include "logger.h"

static uint8_t num_monitores = 0;
static uint8_t logger = 0;
log_state_t logger_state[MAX_NUM_OF_LOGGERS];

/*---------------------------------------------------------------------------*/
/*
 * Finally, the implementation of the simple timer library follows.
 */

#ifdef _WIN32
#include <windows.h>
#include <time.h>
#else
#include "time_lib.h"
#endif

/*---------------------------------------------------------------------------*/
/*
 * The following definitions are just for the simple timer library
 * used in this example. The actual implementation of the functions
 * can be found at the end of this file.
 */
struct timer { int start, interval; };
static int  timer_expired(struct timer *t);
static void timer_set(struct timer *t, int usecs);
/*---------------------------------------------------------------------------*/

//log_header_t config_h; 		/* header for logger config */

#include <time.h>
#include <string.h>

uint8_t http_send_data(char *data, uint8_t len);
uint8_t http_get_time(struct tm *t);
//uint8_t dns_get_ipaddress(char* ip, char *hostname);
//uint8_t build_data_vector(char* ptr_data, uint8_t *data, uint8_t len);

void test_openlog(void)
{

   LOG_FILETYPE fp;
   char* filename = log_getfilename_to_write(logger);

   if(log_openread(filename,&fp))
   {
	   (void)log_close(&fp);
   }else
   {
	   if(log_openwrite(filename,&fp))
	   {
		   log_newheader(filename,0,
				   logger_state[logger].config_h.time_interv,
				   logger_state[logger].config_h.entry_size);

		   (void)log_close(&fp);
	   }
   }

}

void test_writelogts(void)
{

	LOG_FILETYPE fp;
	char timestamp[20];
	uint16_t ret;

#if _WIN32	
    struct tm ts = *localtime(&(time_t){time(NULL)});
    strftime(timestamp,80,"T%Y%m%d%H%M%SS\r\n",&ts);
#endif
    
    puts(timestamp);

   if(log_openread(log_getfilename_to_write(logger),&fp))
   {
	   ret = log_write(timestamp,&fp);
	   (void)log_close(&fp);
	   assert(ret == 1);
   }else
   {
	   assert(0);
   }
}


void test_createentry(void)
{

	uint16_t vetor_dados[3]={0x1111,0x2222,0x3333};
	char string[20];

	log_createentry(string,vetor_dados,3);

	assert((string[0] == '1') && (string[1]== '1') && (string[2] == '1') && (string[3]== '1') &&
			(string[0+4] == '2') && (string[1+4]== '2') && (string[2+4] == '2') && (string[3+4]== '2') &&
			(string[0+2*4] == '3') && (string[1+2*4]== '3') && (string[2+2*4] == '3') && (string[3+2*4]== '3'));

}

void test_setheader(void)
{
	log_header_t h = {{0,0,0,0},{0,0,0,0,0,0,0},0,0};
	h.h1.version = 0;
	h.h1.mon_id = 0;
	h.h1.time_interv = 30;
	h.h1.entry_size = 32;
	log_setheader(log_getfilename_to_write(logger), &h);
}

void test_getheader(void)
{
	log_header_t h = {{0,0,0,0},{0,0,0,0,0,0,0},0,0};
	log_getheader(log_getfilename_to_write(logger), &h);
}


#include "string.h"
void test_writeentry(void)
{

	uint16_t vetor_dados[3]={0x1111,0x2222,0x3333};
	char string[20];
	uint16_t cnt = 0;

	log_createentry(string,vetor_dados,3);

	assert((string[0] == '1') && (string[1]== '1') && (string[2] == '1') && (string[3]== '1') &&
			(string[0+4] == '2') && (string[1+4]== '2') && (string[2+4] == '2') && (string[3+4]== '2') &&
			(string[0+2*4] == '3') && (string[1+2*4]== '3') && (string[2+2*4] == '3') && (string[3+2*4]== '3'));

	/* change to log dir */
	log_chdir(logger_state[logger].log_dir_name);

	cnt = log_writeentry(log_getfilename_to_write(logger),string);

	/* change to parent dir */
	log_chdir("..");

	printf("Entry written %d\r\n", cnt);
}

void test_readentry(void)
{
	log_entry_t entry;
	uint8_t string[20];
	uint32_t nread;
	char buffer[sizeof(long)*8+1];

	char* fname = log_getfilename_to_read(logger);
	entry.values = string;

	/* change to log dir */
	log_chdir(logger_state[logger].log_dir_name);

	if((nread = log_readentry(logger, fname, &entry)) != 0)
	{
		if( nread < MAX_NUM_OF_ENTRIES)
		{
			puts((char*)entry.values);
			puts(ltoa((long)entry.ts,buffer,10));
		}
	}

	/* change to paretnt dir */
	log_chdir("..");

}

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
{;}
#endif

#if 0
void test_build_data_vector(void)
{
	char data_vector[1024];
	uint8_t vetor[]={1,2,3,11,12,23};
	build_data_vector(data_vector,vetor,6);
	puts(data_vector);
}
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
const char config_inifile[] = "config.ini";

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
	  test_writeentry();
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
	  test_readentry();
  }
  PT_END(pt);
}



#ifdef _WIN32

static int clock_time(void)
{ return (int)GetTickCount(); }

#else /* _WIN32 */

unsigned long static clock = 0;
static int clock_time(void)
{
  return clock;
}

void BRTOS_TimerHook(void)
{
	clock++;
}

#endif /* _WIN32 */

static int timer_expired(struct timer *t)
{ return (int)(clock_time() - t->start) >= (int)t->interval; }

static void timer_set(struct timer *t, int interval)
{ t->interval = interval; t->start = clock_time(); }
/*---------------------------------------------------------------------------*/

#include <string.h> /* memcpy, memset */
#include <stdio.h> /* snprintf */
#ifdef _WIN32
#include <winsock2.h>
//#include <ws2tcpip.h>
#endif

#define API_KEY  "90a004390f3530d0ba10199ac2b1ac3d"
#define SERVER_NAME "emon-gpsnetcms.rhcloud.com"

#if 0
#define END_STRING "HTTP/1.1\r\nHost: emon-gpsnetcms.rhcloud.com\r\n\r\n\r\n"
#define SEND_STRING "GET /input/post.json?json={p:3}&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1\r\nHost: emon-gpsnetcms.rhcloud.com\r\n\r\n\r\n"
#define SEND_STRING1 "GET /input/post.json?json={"
#define SEND_STRING2 ("}&apikey=" API_KEY " HTTP/1.1\r\nHost: " SERVER_NAME "\r\n\r\n\r\n")
#define SEND_STRING3 "}&apikey=90a004390f3530d0ba10199ac2b1ac3d HTTP/1.1\r\nHost: emon-gpsnetcms.rhcloud.com\r\n\r\n\r\n"
#endif

//#define DEBUG
#ifdef DEBUG
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
		offset = snprintf(ptr_data, max_len,"%d,", *data);
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

uint8_t http_send_data(char *data, uint8_t len)
{

	char message[1024], server_reply[1024];
	int recv_size;
	char ip[16];
	char* hostname = SERVER_NAME;
	//char* send_template = "GET /input/post.json?json={%s}&apikey=%s";
	char* send_monitor = "GET /monitor/set.json?monitorid=%d&data=%s&apikey=%s";
	char request[1024];
	uint8_t monitor_id = 10;

#if _WIN32
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	
    dprintf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		dprintf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}

	dprintf("Initialised.\n");

	if(dns_get_ipaddress(ip,hostname))
	{
		dprintf("Could not get ip from address : %s" , hostname);
	}
#endif
	
	//snprintf(request, 128, send_template, "p:3",API_KEY);

	snprintf(request, 1024, send_monitor, monitor_id, data, API_KEY);

	/// Form request
	snprintf(message, 1024,
	     "%s HTTP/1.1\r\n"
	     "Host: %s\r\n"
	     "\r\n\r\n", request, hostname);

#if _WIN32
	printf(message);

	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		dprintf("Could not create socket : %d" , WSAGetLastError());
	}

	dprintf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	//Connect to remote server
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		dprintf("connect error");
		return 1;
	}

	dprintf("Connected");

	//Send message
	if( send(s , message , strlen(message) , 0) < 0)
	{
		dprintf("Send failed");
		return 1;
	}
	dprintf("Data Send\n");

	//Receive a reply from the server
	if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
	{
		dprintf("recv failed");
	}

	dprintf("Reply received\n");
#endif
	
	//Add a NULL terminating character to make it a proper string before printing
	server_reply[recv_size] = '\0';
	printf(server_reply);

	return 0;
}

static const char *abmon[12] =
{
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

#include "time_lib.h"
void http_server_time(char* server_reply, struct tm *ts)
{
	
	char *ret;
	char *token;
	int k = 0;
	char mon[4];
	struct tm t;
	
	ret = strstr(server_reply, "Date:");	
	token = strtok(ret, " ");	

	for (k=0; k<6;k++)
	{
		switch(k)
		{
		case 0:
		case 1:
			break;
		case 2: if (1 != sscanf(token,"%d", &t.tm_mday)){;} // day
			break;
		case 3:
			if (1 != sscanf(token,"%s",(char*) mon)){;} // month
			t.tm_mon = 0;
			while (strcmp (abmon[t.tm_mon],mon) != 0)
			{
				++t.tm_mon;
			}
			//t.tm_mon--;
			break;
		case 4:
			if (1 != sscanf(token,"%d", &t.tm_year)){;}
			t.tm_year -= 1900;
			break;
		case 5:
			 if (3 != sscanf(token,"%d:%d:%d", &t.tm_hour, &t.tm_min, &t.tm_sec)){;}
			break;
		default:
			break;
		}
		printf( " %s\n", token );
		token = strtok(NULL, " ");
	}

	if (mktime(&t) < 0) {;}
	(*ts) = t;

	
}
uint8_t http_get_time(struct tm *ts)
{

	char message[1024], server_reply[1024];
	int recv_size;
    char ip[16];
    char* hostname = SERVER_NAME;
    //char* get_time_request = "GET /time/local&apikey=%s";
    char* get_time_request = "GET /";
    //char request[1024];

#if _WIN32
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	
    if(ts==NULL) return 1;

    dprintf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		dprintf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}

	dprintf("Initialised.\n");

	if(dns_get_ipaddress(ip,hostname))
	{
		dprintf("Could not get ip from address : %s" , hostname);
	}

	//snprintf(request, 1024, get_time_request, API_KEY);
	//snprintf(request, 1024, get_time_request);

	/// Form request
	snprintf(message, 1024,
	     "%s HTTP/1.1\r\n"
	     "Host: %s\r\n"
	     "\r\n\r\n", get_time_request, hostname);

	//printf(message);

	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		dprintf("Could not create socket : %d" , WSAGetLastError());
	}

	dprintf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	//Connect to remote server
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		dprintf("connect error");
		return 1;
	}

	dprintf("Connected");

	//Send message
	if( send(s , message , strlen(message) , 0) < 0)
	{
		dprintf("Send failed");
		return 1;
	}
	dprintf("Data Send\n");

	//Receive a reply from the server
	if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
	{
		dprintf("recv failed");
	}

	dprintf("Reply received\n");
#endif	

	//Add a NULL terminating character to make it a proper string before printing
	server_reply[recv_size] = '\0';
	//printf(server_reply);

	http_server_time(server_reply, ts);
	
	return 0;
}

#if 0
/*
	 Get IP address from domain name
*/
uint8_t dns_get_ipaddress(char* ip, char *hostname)
{

	    struct hostent *he;
	    struct in_addr **addr_list;
	    int i;

#if 0
	    WSADATA wsa;
	    printf("\nInitialising Winsock...");
	    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	    {
	        printf("Failed. Error Code : %d",WSAGetLastError());
	        return 1;
	    }
	    printf("Initialised.\n");
#endif

#if _WIN32
	    if ( (he = gethostbyname( hostname ) ) == NULL)
	    {
	        //gethostbyname failed
	    	dprintf("gethostbyname failed : %d" , WSAGetLastError());
	        return 1;
	    }

	    //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
	    addr_list = (struct in_addr **) he->h_addr_list;

	    for(i = 0; addr_list[i] != NULL; i++)
	    {
	        //Return the first one;
	        strcpy(ip , inet_ntoa(*addr_list[i]) );
	    }
#endif	    

	    printf("%s resolved to : %s\n" , hostname , ip);
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
				printf("Erro: num_monitores superior ao suportado\n\r.");
			}
		}else
		{
			printf("Erro: num_monitores não configurado\n\r.");
			return 0;
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

void main_monitor(void)
{

#ifdef _WIN32
	struct timeb start, end;
	uint16_t diff;
#endif	

	 /* Initialize the protothread state variables with PT_INIT(). */
	  PT_INIT(&log_read_pt);
	  PT_INIT(&log_write_pt);

	puts("help:\r\nq-quit\r\np-stop logger\r\nc-continue logger\r\ns-synch\r\nu-start upload\r\nv-stop upload\r\n");

#ifdef _WIN32
	ftime(&start);
#endif	

#if 0
	struct tm t;
	http_get_time(&t);
	printf ("Current local time and date: %s", asctime(&t));
	fflush(stdout);
#endif

	//test_logger(); // do tests
    // extern log_state_t logger_state[];
	ini_browse(Callback_inifile, NULL, config_inifile);
	log_init(0);
	
#ifdef _WIN32	
	fflush(stdout);
#endif	

#if 1
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
		
		DelayTask(1000); // executa a cada 1s
	}

	out:
#endif

#ifdef _WIN32
	ftime(&end);
	diff = (uint16_t) (1000.0 * (end.time - start.time)
		+ (end.millitm - start.millitm));

	printf("\nOperation took %u milliseconds\n", diff);	

	getchar();
#endif
	
	return;

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
	
}
#endif

