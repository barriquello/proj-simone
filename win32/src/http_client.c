/*
 * http_client.c
 *
 *  Created on: Aug 12, 2015
 *      Author: Universidade Federal
 */


#include "http_client.h"
#include "printf_lib.h"
#include <string.h>
#include "simon-api.h"
#include "utils.h"

#define STDIO
#ifdef STDIO
#include <stdio.h>
#endif

#ifdef _WIN32
#include <winsock2.h>
//#include <ws2tcpip.h>
#endif

#ifdef _WIN32
#define DEBUG_PRINTF 1
#endif

#if DEBUG_PRINTF
#define PRINTF(...) printf(__VA_ARGS__);
#define dprintf(...) printf(__VA_ARGS__);
#else
#define PRINTF(...)
#endif

#if _WIN32
char server_reply[10*1024];
#else
char server_reply[512];
#endif
char ip[16];
char* hostname = NULL;
int recv_size = 0;

uint8_t http_send(uint8_t *data, uint16_t len)
{
#if _WIN32

	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;

	*(data+len) = '\0';

	if(hostname == NULL)
	{
		hostname = simon_get_hostname();
	}

    dprintf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		dprintf("Failed. Error Code : %d",WSAGetLastError());
		return MODEM_ERR;
	}

	dprintf("Initialised.\n");

	if(dns_get_ipaddress(ip,hostname))
	{
		dprintf("Could not get ip from address : %s" , hostname);
		return MODEM_ERR;
	}

	printf((char*)data);

	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		dprintf("Could not create socket : %d" , WSAGetLastError());
		return MODEM_ERR;
	}

	dprintf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	//Connect to remote server
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		dprintf("connect error");
		return MODEM_ERR;
	}

	dprintf("Connected");

	//Send message
	if( send(s , (char*)data , len, 0) < 0)
	{
		dprintf("Send failed");
		return MODEM_ERR;
	}
	dprintf("Data Send\n");

	//Receive a reply from the server
	if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
	{
		recv_size = 0;
		dprintf("recv failed");
		return MODEM_ERR;
	}

	dprintf("Reply received\n");

	//Add a NULL terminating character to make it a proper string before printing
	server_reply[recv_size] = '\0';
	PRINTF(server_reply);

#endif

	return MODEM_OK;
}

uint8_t http_send_data(char *data, uint8_t len)
{
	
#if _WIN32
	char message[1024];

	//char* send_template = "GET /input/post.json?json={%s}&apikey=%s";
	char* send_monitor = "GET /monitor/set.json?monitorid=%d&data=%s&apikey=%s";
	char request[1024];
	uint8_t monitor_id = 10;

	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;

	if(hostname == NULL)
	{
		hostname = simon_get_hostname();
	}
	
    dprintf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		dprintf("Failed. Error Code : %d",WSAGetLastError());
		return MODEM_ERR;
	}

	dprintf("Initialised.\n");

	if(dns_get_ipaddress(ip,hostname))
	{
		dprintf("Could not get ip from address : %s" , hostname);
		return MODEM_ERR;
	}
	
	SNPRINTF(request, 1024, send_monitor, monitor_id, data, simon_get_apikey());

	/// Form request
	SNPRINTF(message, 1024,
	     "%s HTTP/1.1\r\n"
	     "Host: %s\r\n"
	     "\r\n\r\n", request, hostname);

	printf(message);

	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		dprintf("Could not create socket : %d" , WSAGetLastError());
		return MODEM_ERR;
	}

	dprintf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	//Connect to remote server
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		dprintf("connect error");
		return MODEM_ERR;
	}

	dprintf("Connected");

	//Send message
	if( send(s , message , strlen(message) , 0) < 0)
	{
		dprintf("Send failed");
		return MODEM_ERR;
	}
	dprintf("Data Send\n");

	//Receive a reply from the server
	if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
	{
		recv_size = 0;
		dprintf("recv failed");
		return MODEM_ERR;
	}

	dprintf("Reply received\n");
	
	//Add a NULL terminating character to make it a proper string before printing
	server_reply[recv_size] = '\0';
	PRINTF(server_reply);

#endif

	return MODEM_OK;
}

static CONST char *abmon[12] =
{
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

#ifndef _WIN32
#include "time_lib.h"
#endif

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
		PRINTF( " %s\n", token );
		token = strtok(NULL, " ");
	}

	if (mktime(&t) < 0) {;}
	(*ts) = t;	
}

uint8_t http_get_time(struct tm *ts)
{

#if _WIN32
	char message[1024];
	int recv_size;
    //char* get_time_request = "GET /time/local&apikey=%s";
    char* get_time_request = "GET /";
    //char request[1024];

	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	
	if(hostname == NULL)
	{
		hostname = simon_get_hostname();
	}

    if(ts==NULL) return MODEM_ERR;

    dprintf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		dprintf("Failed. Error Code : %d",WSAGetLastError());
		return FALSE;
	}

	dprintf("Initialised.\n");

	if(dns_get_ipaddress(ip,hostname))
	{
		dprintf("Could not get ip from address : %s" , hostname);
	}

	//SNPRINTF(request, 1024, get_time_request, API_KEY);
	//SNPRINTF(request, 1024, get_time_request);

	/// Form request
	SNPRINTF(message, 1024,
	     "%s HTTP/1.1\r\n"
	     "Host: %s\r\n"
	     "\r\n\r\n", get_time_request, hostname);

	//printf(message);

	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		dprintf("Could not create socket : %d" , WSAGetLastError());
		return MODEM_ERR;
	}

	dprintf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	//Connect to remote server
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		dprintf("connect error");
		return MODEM_ERR;
	}

	dprintf("Connected");

	//Send message
	if( send(s , message , strlen(message) , 0) < 0)
	{
		dprintf("Send failed");
		return MODEM_ERR;
	}
	dprintf("Data Send\n");

	//Receive a reply from the server
	if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
	{
		recv_size = 0;
		dprintf("recv failed");
		return MODEM_ERR;
	}

	dprintf("Reply received\n");

	//Add a NULL terminating character to make it a proper string before printing
	server_reply[recv_size] = '\0';
	//printf(server_reply);

	http_server_time(server_reply, ts);
#endif		
	
	return MODEM_OK;
}

#if _WIN32
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
	        return MODEM_ERR;
	    }
	    printf("Initialised.\n");
#endif

#if _WIN32
	    if ( (he = gethostbyname( hostname ) ) == NULL)
	    {
	        //gethostbyname failed
	    	dprintf("gethostbyname failed : %d" , WSAGetLastError());
	        return MODEM_ERR;
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
	    return MODEM_OK;
}
#endif

uint8_t http_receive (uint8_t *dados, uint16_t *tam)
{
	uint16_t size =(uint16_t) MIN(*tam,SIZEARRAY(server_reply));

	if(size)
	{
		memcpy(dados,server_reply,size);
		if(size < SIZEARRAY(server_reply))
		{
			memcpy(server_reply,&server_reply[size],SIZEARRAY(server_reply)-size);
		}
	}

	*tam = size;
	return MODEM_OK;
}

uint8_t http_set_hostname (char * host)
{
	hostname = host;
	return MODEM_OK;
}

uint8_t http_set_ip(char * _ip)
{
	if(hostname == NULL || _ip == NULL)
	{
		return MODEM_ERR;
	}
	strcpy(ip,_ip);
	return MODEM_OK;
}


const modem_driver_t win_http =
{
		http_receive,
		http_send,
		http_set_hostname,
		http_set_ip
};
