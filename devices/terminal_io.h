/*
 * terminal_io.h
 *
 *  Created on: Jul 22, 2015
 *      Author: Universidade Federal
 */

#ifndef TERMINAL_IO_H_
#define TERMINAL_IO_H_

#include "BRTOS.h"

typedef INT8U (*term_input)(CHAR8 *);
typedef INT8U (*term_output)(CHAR8);	

void terminal_set_input (term_input _input);
void terminal_set_output (term_output _output);

void terminal_input (CHAR8 *c);
void terminal_output (CHAR8 c);

#endif /* TERMINAL_IO_H_ */
