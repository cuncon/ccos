#include <cc/compiler-gcc.h>
#include <cc/string.h>
#include <video/vga.h>
#include <input/keyboard.h>

#include "isr.h"
#include "timer.h"
#include "descriptor_tables.h"

static void keyboard_handler(register_t reg __unused)
{
	char buf[10];

	kprint(itoa(buf, read_scan_code()));
}

static void timer_handler(register_t reg __unused)
{
	char buf[20];
	static uint32_t tick = 0;

	kprint("tick: ");
	kprint(itoa(buf, tick++));
	kprint("\n");
}

void kernel_main(void)
{
	clear_screen();

	asm volatile ("sti");

	init_descriptor_tables();
	register_int_handler(0x21, keyboard_handler);
	timer_init(50);
	register_int_handler(0x20, timer_handler);
}
