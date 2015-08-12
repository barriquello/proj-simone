#ifndef RANDOM_LIB_H_
#define RANDOM_LIB_H_

/*
 * Initialize the pseudo-random generator.
 *
 */
void random_init(unsigned short seed);

/*
 * Calculate a pseudo random number between 0 and 65535.
 *
 * \return A pseudo-random number between 0 and 65535.
 */
unsigned short random_get(void);

#define RANDOM_RAND_MAX 65535U

#endif /* RANDOM_LIB_H_*/
