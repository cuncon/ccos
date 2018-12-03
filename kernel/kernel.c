#include <cc/compiler-gcc.h>
#include <video/vga.h>

#include "isr.h"
#include "descriptor_tables.h"

void kernel_main(void)
{
	clear_screen();

	asm volatile ("sti");

	init_descriptor_tables();
}
