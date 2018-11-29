#include <cc/compiler-gcc.h>
#include <cc/string.h>

#include "isr.h"
#include "../drivers/screen.h"

void isr_handler(register_t reg)
{
	char buf[10];

	print("recieved interrupt:");
	print(itoa(buf, reg.int_no));
	print("\n");
}
