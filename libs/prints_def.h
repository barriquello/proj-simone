#include "AppConfig.h"
#include "terminal.h"

void print_R(char* out, const char *format, ...);
void print_P(char* out, const char *format, ...);
void prints_R(char* out, const char *string);
void prints_P(char* out, const char *string);

#if	PRINTS_ENABLED
#if ARDUINO
#define PRINTF(...)			printf_lib(__VA_ARGS__);
#define PRINTF_P(...)		print_P(NULL, __VA_ARGS__);
#define PRINTF_PP(s,...)	print_P(NULL,(PGM_P)pgm_read_word(&(s)), __VA_ARGS__);
#define PRINTS_P(s)			do{printf_terminal_P(s); }while(0);
#define PRINTC(c)			do{putchar_terminal(c);}while(0);
#define DPRINTS_P(s)		prints_P("debug.txt", s);
#define PRINT_ERRO(...)		print_R("erro.txt",__VA_ARGS__);
#define PRINT_ERRO_P(...)	 PRINTF_P(__VA_ARGS__); print_P("erro.txt", __VA_ARGS__);
#define PRINT_ERRO_PP(s,...) PRINTF_PP((s),__VA_ARGS__); print_P("erro.txt",(PGM_P)pgm_read_word(&(s)), __VA_ARGS__);
#define PRINTS_ERRO(s)		PRINTS_P(s); prints_R("erro.txt",s);
#define PRINTS_ERRO_P(s)	PRINTS_P(s); prints_P("erro.txt",s); 
#define PRINTS_ERRO_PP(s)	PRINTS_P(s); prints_P("erro.txt",(PGM_P)pgm_read_word(&(s))); 
#elif COLDUINO
#include "printf_lib.h"
#define PRINTF(...)			printf_lib(__VA_ARGS__);
#define PRINTF_P(...)		printf_lib(__VA_ARGS__);
#define PRINTF_PP(...)		printf_lib(__VA_ARGS__);
#define PRINTS_P(s)			printf_lib(s);
#define PRINTC(c)			do{putchar_terminal(c);}while(0);
#define DPRINTS_P(s)		prints_P("debug.txt", s);
#define PRINT_ERRO(...)		print_R("erro.txt",__VA_ARGS__);
#define PRINT_ERRO_P(...)	print_P("erro.txt", __VA_ARGS__);
#define PRINT_ERRO_PP(s,...)  print_P("erro.txt", (s), __VA_ARGS__);
#define PRINTS_ERRO(s)		prints_R("erro.txt",s);
#define PRINTS_ERRO_P(s)	prints_P("erro.txt",s); PRINTS_P(s);
#define PRINTS_ERRO_PP(s)	prints_P("erro.txt",s); PRINTS_P(s);
#else /* WIN32*/
#define PRINTF(...)			printf(__VA_ARGS__);
#define PRINTS_P(s)			printf(s);
#define PRINTC(c)			putchar(c);
#define DPRINTS_P(s)		prints_P("debug.txt", s);
#define PRINT_ERRO(...)		print_R("erro.txt",__VA_ARGS__);
#define PRINT_ERRO_P(...)	print_P("erro.txt", __VA_ARGS__);
#define PRINT_ERRO_PP(s,...)  print_P("erro.txt", (s)__VA_ARGS__);
#define PRINTS_ERRO(s)		prints_R("erro.txt",s);
#define PRINTS_ERRO_P(s)	prints_P("erro.txt",s); PRINTS_P(s);
#define PRINTS_ERRO_PP(s)	prints_P("erro.txt",s); PRINTS_P(s);
#endif
#else
#define PRINTF(...)			
#define PRINTS_P(s)			
#define PRINTC(c)			
#define DPRINTS_P(s)		
#define PRINT_ERRO(...)		
#define PRINT_ERRO_P(...)	
#define PRINT_ERRO_PP(s,...)  
#define PRINTS_ERRO(s)		
#define PRINTS_ERRO_P(s)	
#define PRINTS_ERRO_PP(s)	
#define PSTR(s)			(s)
#endif

