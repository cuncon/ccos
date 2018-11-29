#include <cc/compiler-gcc.h>

#include "descriptor_tables.h"

#include "../drivers/screen.h"

void kernel_main(void)
{
	clear_screen();

	for (int i = 0; i < MAX_ROWS; i++)
		print("ccOS kernel\n");

	print("This text forces the kernel to scroll\n");
	print("And with this text\n");

	init_descriptor_tables();

	asm volatile ("int $0x03");
	asm volatile ("int $0x04");

	print("kernel\n");
}
