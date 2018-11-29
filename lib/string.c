#include <cc/string.h>

void *memcpy(void *to, const void *from, size_t n)
{
	char *temp = to;

	while (n-- && (*temp++ = *(const char *)from++));

	return to;
}

void *memset(void *src, int c, size_t n)
{
	while (n-- > 0)
		*((char *)src + n) = c;

	return src;
}
