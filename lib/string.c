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

char *strcpy(char *dest, const char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';

	return dest;
}

char *itoa(char *buf, int c)
{
	char s[12];
	int i;

	buf[0] = (c >> 31) ? '-' : '+';

	unsigned int abs = (unsigned int)((c << 1) >> 1);
	for (i = 0; abs > 0; abs /= 10, i++)
		s[i] = (abs % 10) + '0';
	s[i] = '\0';

	if (buf[0] == '-')
		strcpy(buf + 1, s);
	else
		strcpy(buf, s);

	return buf;
}
