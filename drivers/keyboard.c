#include <asm-generic/io.h>

#include "input/keyboard.h"

uint8_t read_scan_code(void)
{
	return inb(KEYBOARD_DATA_PORT);
}
