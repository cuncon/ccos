#include <cc/string.h>

void *memcpy(void *to, const void *from, size_t n)
{
	char *tmp = to;

	while (n-- && (*tmp++ = *(const char *)from++));

	return to;
}

void *memset(void *src, int c, size_t n)
{
	while (n-- > 0)
		*((char *)src + n) = c;

	return src;
}

size_t strlen(const char *s)
{
	const char *sc;

	for (sc = s; *sc != '\0'; ++sc)
		/* do nothing */;

	return sc - s;
}

char *strcpy(char *dest, const char *src)
{
	char *tmp = dest;

	while ((*dest++ = *src++) != '\0');

	return tmp;
}

char *itoa(char *ascii, int c)
{
	int i = 0;
	int sign = c < 0 ? -c : c;

	do {
		ascii[i++] = (c % 10) + '0';
	} while ((c /= 10) > 0);

	if (sign < 0)
		ascii[i++] = '-';
	ascii[i] = '\0';

	return reverse(ascii);
}

char *reverse(char *s)
{
	char *tmp = s;
	char *tail = s + strlen(s) - 1;

	while ((*s++ = *tail--) && (tail >= tmp));
	*s = '\0';

	return tmp;
}
