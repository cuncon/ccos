#ifndef _CC_STRING_H
#define _CC_STRING_H

#define __need_size_t
#include <stddef.h>
#include <cc/types.h>

extern void *memcpy(void *, const void *, size_t n);
extern void *memset(void *, int, size_t n);
extern char *strcpy(char *, const char *);
extern char *itoa(char *, int);

#endif
