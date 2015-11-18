#include <stdarg.h>
#include <stdio.h>
#define error_file		"erro.txt"

#include "monitor.h"
#include "terminal.h"
#include "printf_lib.h"

/**------------------------------------------------------**/
void print_R(char* out, const char *format, ...)
{
	
	LOG_FILETYPE stderr_f;
	char buffer[32];
	
	va_list argptr;
	va_start(argptr, format);
	VSNPRINTF(buffer, format, argptr);
	va_end(argptr);

	if(out == NULL)
	{
		printf_terminal(buffer);
	}else
	{
		if(!monitor_openappend(out,&stderr_f))
		{
			if(!monitor_openwrite(out,&stderr_f))
			{
				return;
			}
		}
		/* print to file */
		(void)monitor_seek_end(&stderr_f);
		(void)monitor_write(buffer,&stderr_f);
		(void)monitor_close(&stderr_f);
	}
	
}

void print_P(char* out, const char *format, ...)
{
	
	LOG_FILETYPE stderr_f;
	char buffer[32];
	
	va_list argptr;
	va_start(argptr, format);
	VSNPRINTF_P(buffer, format, argptr);
	va_end(argptr);

	if(out == NULL)
	{
		printf_terminal(buffer);
	}else
	{
		if(!monitor_openappend(out,&stderr_f))
		{
			if(!monitor_openwrite(out,&stderr_f))
			{
				return;
			}
		}
		/* print to file */
		(void)monitor_seek_end(&stderr_f);
		(void)monitor_write(buffer,&stderr_f);
		(void)monitor_close(&stderr_f);
	}
}

/**------------------------------------------------------**/
void prints_R(char* out, const char *string)
{	
	LOG_FILETYPE stderr_f;
	
	if(out == NULL)
	{
		printf_terminal(string);
	}else
	{
		if(!monitor_openappend(out,&stderr_f))
		{
			if(!monitor_openwrite(out,&stderr_f))
			{
				return;
			}
		}
		/* print to file */
		(void)monitor_seek_end(&stderr_f);
		(void)monitor_write(string,&stderr_f);
		(void)monitor_close(&stderr_f);
	}
	
}

void prints_P(char* out, const char *string)
{
	char buffer[32];
	LOG_FILETYPE stderr_f;

	if(out == NULL)
	{
		printf_terminal_P(string);
	}else
	{
		STRCPY_P(buffer,string);
		if(!monitor_openappend(out,&stderr_f))
		{
			if(!monitor_openwrite(out,&stderr_f))
			{
				return;
			}
		}
		/* print to file */
		(void)monitor_seek_end(&stderr_f);
		(void)monitor_write(buffer,&stderr_f);
		(void)monitor_close(&stderr_f);
	}
}
