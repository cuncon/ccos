#include <cc/compiler-gcc.h>
#include <cc/string.h>
#include <video/vga.h>
#include <input/keyboard.h>

#include "isr.h"
#include "descriptor_tables.h"

static void keyboard_handler(register_t reg __unused)
{
	char buf[10];

	kprint(itoa(buf, read_scan_code()));
}

void kernel_main(void)
{
	clear_screen();

	asm volatile ("sti");

	init_descriptor_tables();
	register_int_handler(0x21, keyboard_handler);
}
