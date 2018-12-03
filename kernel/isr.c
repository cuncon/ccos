#include <cc/compiler-gcc.h>
#include <cc/string.h>
#define __need_NULL
#include <cc/stddef.h>
#include <video/vga.h>
#include <asm-generic/io.h>

#include "isr.h"
#include "descriptor_tables.h"

static isr_t int_handlers[INT_HANDLER_MAX];

static const char * const cpu_isr_msg[] = {
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

void isr_handler(register_t reg)
{
	char buf[10];

	kprint("int #");
	kprint(itoa(buf, reg.int_no));
	kprint(": ");
	kprint(cpu_isr_msg[reg.int_no]);
	kprint("\n");
}

void irq_handler(register_t reg)
{
	char buf[10];

	/* Acknowledge the interrupt */
	if (reg.int_no > 40) /* slave */
		outb(SLAVE_PIC_COMMAND, 0x20);
	outb(MASTER_PIC_COMMAND, 0x20);

	kprint("irq #");
	kprint(itoa(buf, reg.int_no));
	kprint("\n");

	if (int_handlers[reg.int_no] != NULL)
		int_handlers[reg.int_no](reg);
}

void register_int_handler(uint8_t n, isr_t handler)
{
	int_handlers[n] = handler;
}
