#ifndef __INPUT_KEYBOARD_H
#define __INPUT_KEYBOARD_H

#include <cc/types.h>

#define KEYBOARD_DATA_PORT 0x60

extern uint8_t read_scan_code(void);

#endif /* __INPUT_KEYBOARD_H */
