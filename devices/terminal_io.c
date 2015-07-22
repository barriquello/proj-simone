/*
 * terminal_io.c
 *
 *  Created on: Jul 22, 2015
 *      Author: Universidade Federal
 */

#include "terminal_io.h"

static term_input input = NULL;
static term_output output = NULL;

void terminal_set_input (term_input _input)
{
	input = _input;
}
void terminal_set_output (term_output _output)
{
	output = _output;
}

void terminal_input (CHAR8 *c)
{
	if(input == NULL)
	{
		*c = 0;
	}else
	{
		input(c);
	}
}
void terminal_output (CHAR8 c)
{
	if(output == NULL)
	{
		(void)c;
	}else
	{
		output(c);
	}
}
