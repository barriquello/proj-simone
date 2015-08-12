#ifndef ASSERT_H_
#define ASSERT_H_

#undef assert
#ifdef NDEBUG
#define assert(e) ((void)0)
#else
#define assert(e) ((e) ? (void)0 : _xassert(__FILE__, __LINE__))
void _xassert(const char *, int);
#endif

#ifndef CTASSERT                /* Allow lint to override */
#define CTASSERT(x)             _CTASSERT(x, __LINE__)
#define _CTASSERT(x, y)         __CTASSERT(x, y)
#define __CTASSERT(x, y)        typedef char __assert ## y[(x) ? 1 : -1]
#endif

#endif /* ASSERT_H_ */
