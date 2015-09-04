#include <stdio.h>

void _xassert(const char *file, int lineno);

#define UNUSED(a)	(void)(a)
void _xassert(const char *file, int lineno)
{
	UNUSED(file);UNUSED(lineno);
	//printf("Assertion failed: file %s, line %d.\n", file, lineno);
  /*
   * loop for a while;
   * call _reset_vector__();
   */
}
