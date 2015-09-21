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
#include "random_lib.h"
#include <stdlib.h>

#define STDLIB_RAND 	0

#if !STDLIB_RAND
static unsigned long next = 1;	
#endif

/*---------------------------------------------------------------------------*/
void random_init(unsigned short seed)
{
#if STDLIB_RAND
	srand(seed);
#else
	next=seed;
#endif
}
/*---------------------------------------------------------------------------*/
unsigned short random_get(void)
{

#if STDLIB_RAND
  return (unsigned short)rand();
#else
  next = next * 1103515245 + 12345;
  return (unsigned short)((next>>16) & RANDOM_RAND_MAX);
#endif
  
}
/*---------------------------------------------------------------------------*/

