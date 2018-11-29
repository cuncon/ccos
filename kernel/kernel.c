#include <cc/compiler-gcc.h>

#include "../drivers/screen.h"

static void __unused foo(void)
{
	print("foo\n");
}

void kernel_main(void)
{
	clear_screen();

	for (int i = 0; i < MAX_ROWS; i++)
		print("ccOS kernel\n");

	print("This text forces the kernel to scroll\n");
	print("And with this text, the kernel scrolls again\n");
}
