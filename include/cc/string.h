#ifndef _CC_STRING_H
#define _CC_STRING_H

#define __need_size_t
#include <stddef.h>

extern void *memcpy(void *, const void *, size_t);
extern void *memset(void *, int, size_t n);
extern size_t strlen(const char *);
extern char *strcpy(char *, const char *);
extern char *itoa(char *, int);
extern char *reverse(char *);

#endif /* _CC_STRING_H */
