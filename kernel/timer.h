#ifndef __TIMER_H
#define __TIMER_H

#include <cc/types.h>

#define OSCILLATOR_FREQ 1193180

#define PIT_CHANNEL_0_IO 0x40
#define PIT_CHANNEL_1_IO 0x41
#define PIT_CHANNEL_2_IO 0x42
#define PIT_COMMAND_IO   0x43

extern void timer_init(uint32_t);

#endif /* __TIMER_H */
