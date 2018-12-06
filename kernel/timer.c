#include <asm-generic/io.h>

#include "timer.h"

void timer_init(uint32_t freq)
{
	uint32_t divisor = 1193180 / freq;

	outb(PIT_COMMAND_IO, 0x36);

	uint8_t l = (uint8_t)(divisor & 0xFF);
	uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);

	outb(PIT_CHANNEL_0_IO, l);
	outb(PIT_CHANNEL_0_IO, h);
}
