#ifndef _IRS_H
#define _IRS_H

#include <cc/types.h>

typedef struct {
	uint32_t ds; /* Data segment selector */
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* push by pusha */
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss; /* push by the processor automatically */
} register_t;

#endif
