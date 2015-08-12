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

