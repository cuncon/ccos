#ifndef _ASM_GENERIC_IO_H
#define _ASM_GENERIC_IO_H

#include <cc/types.h>
#include <cc/compiler-gcc.h>

static inline uint8_t inb(uint16_t port)
{
	uint8_t result;

	asm volatile ("inb %1, %0" : "=a" (result) : "Nd" (port));

	return result;
}

static inline void outb(uint16_t port, uint8_t data)
{
	asm volatile ("outb %0, %1" : : "a" (data), "Nd" (port));
}

static inline uint16_t inw(uint16_t port)
{
	uint16_t result;

	asm volatile ("inw %1, %0" : "=a" (result) : "Nd" (port));

	return result;
}

static inline void outw(uint16_t port, uint16_t data)
{
	asm volatile ("outw %0, %1" : :"a" (data), "Nd" (port));
}

static inline void io_wait(void)
{
	asm volatile ("outb %%al, $0x80" : : "a"(0));
}

#endif /* _ASM_GENERIC_IO_H */
