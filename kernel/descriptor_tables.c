#include <cc/string.h>
#include <asm-generic/io.h>

#include "isr.h"
#include "descriptor_tables.h"

extern void load_idt(uint32_t);

#define ICW1_ICW4       0x01 /* ICW4 (not) needed */
#define ICW1_SINGLE     0x02 /* Single (cascade) mode */
#define ICW1_INTERVAL4  0x04 /* Call address interval 4 (8) */
#define ICW1_LEVEL      0x08 /* Level triggered (edge) mode */
#define ICW1_INIT       0x10 /* Initialization - required! */

#define ICW4_8086       0x01 /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO       0x02 /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE  0x08 /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C /* Buffered mode/master */
#define ICW4_SFNM       0x10 /* Special fully nested (not) */

static idt_entry_t idt[IDT_ENTRY_MAX];
static idt_pointer_t idt_p;

static void set_idt_gate(uint8_t num, uint32_t base, uint16_t seg, uint8_t flag)
{
	idt[num].base_hi = (uint16_t)((base >> 16) & 0xFFFF);
	idt[num].base_lo = (uint16_t)(base & 0xFFFF);
	idt[num].segment = seg;
	idt[num].zero = 0;
	idt[num].flags = flag /* | 0x60 */; /* uncomment it when get to using user-mode */
}

/*
 * offset1 - vector offset for master PIC
 * vectors on the master become offset1..offset1 + 7
 * offset2 - same for slave PIC: offset2..offset2 + 7
 */
static void remap_pics(int offset1, int offset2)
{
	unsigned char a1, a2;

	a1 = inb(MASTER_PIC_DATA); /* save masks */
	a2 = inb(SLAVE_PIC_DATA);

	outb(MASTER_PIC_COMMAND, ICW1_INIT | ICW1_ICW4); /* starts the initialization sequence (in cascade mode) */
	io_wait();
	outb(SLAVE_PIC_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(MASTER_PIC_DATA, offset1); /* ICW2: Master PIC vector offset */
	io_wait();
	outb(SLAVE_PIC_DATA, offset2);  /* ICW2: Slave PIC vector offset */
	io_wait();
	outb(MASTER_PIC_DATA, 4);  /* ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100) */
	io_wait();
	outb(SLAVE_PIC_DATA, 2);   /* ICW3: tell Slave PIC its cascade identity (0000 0010) */
	io_wait();
	outb(MASTER_PIC_DATA, ICW4_8086);
	io_wait();
	outb(SLAVE_PIC_DATA, ICW4_8086);
	io_wait();

	outb(MASTER_PIC_DATA, a1);   // restore saved masks.
	outb(SLAVE_PIC_DATA, a2);
}

static void init_idt(void)
{
	idt_p.limit = sizeof(idt_entry_t) * IDT_ENTRY_MAX - 1;
	idt_p.base = (uint32_t)&idt;

	memset(idt, 0, sizeof(idt_entry_t) * IDT_ENTRY_MAX);

	/* CPU exceptions and faults */
	set_idt_gate( 0, (uint32_t)isr0,  0x08, 0x8E);
	set_idt_gate( 1, (uint32_t)isr1,  0x08, 0x8E);
	set_idt_gate( 2, (uint32_t)isr2,  0x08, 0x8E);
	set_idt_gate( 3, (uint32_t)isr3,  0x08, 0x8E);
	set_idt_gate( 4, (uint32_t)isr4,  0x08, 0x8E);
	set_idt_gate( 5, (uint32_t)isr5,  0x08, 0x8E);
	set_idt_gate( 6, (uint32_t)isr6,  0x08, 0x8E);
	set_idt_gate( 7, (uint32_t)isr7,  0x08, 0x8E);
	set_idt_gate( 8, (uint32_t)isr8,  0x08, 0x8E);
	set_idt_gate( 9, (uint32_t)isr9,  0x08, 0x8E);
	set_idt_gate(10, (uint32_t)isr10, 0x08, 0x8E);
	set_idt_gate(11, (uint32_t)isr11, 0x08, 0x8E);
	set_idt_gate(12, (uint32_t)isr12, 0x08, 0x8E);
	set_idt_gate(13, (uint32_t)isr13, 0x08, 0x8E);
	set_idt_gate(14, (uint32_t)isr14, 0x08, 0x8E);
	set_idt_gate(15, (uint32_t)isr15, 0x08, 0x8E);
	set_idt_gate(16, (uint32_t)isr16, 0x08, 0x8E);
	set_idt_gate(17, (uint32_t)isr17, 0x08, 0x8E);
	set_idt_gate(18, (uint32_t)isr18, 0x08, 0x8E);
	set_idt_gate(19, (uint32_t)isr19, 0x08, 0x8E);
	set_idt_gate(20, (uint32_t)isr20, 0x08, 0x8E);
	set_idt_gate(21, (uint32_t)isr21, 0x08, 0x8E);
	set_idt_gate(22, (uint32_t)isr22, 0x08, 0x8E);
	set_idt_gate(23, (uint32_t)isr23, 0x08, 0x8E);
	set_idt_gate(24, (uint32_t)isr24, 0x08, 0x8E);
	set_idt_gate(25, (uint32_t)isr25, 0x08, 0x8E);
	set_idt_gate(26, (uint32_t)isr26, 0x08, 0x8E);
	set_idt_gate(27, (uint32_t)isr27, 0x08, 0x8E);
	set_idt_gate(28, (uint32_t)isr28, 0x08, 0x8E);
	set_idt_gate(29, (uint32_t)isr29, 0x08, 0x8E);
	set_idt_gate(30, (uint32_t)isr30, 0x08, 0x8E);
	set_idt_gate(31, (uint32_t)isr31, 0x08, 0x8E);

	remap_pics(0x20, 0x28);

	/* Install the IRQ, 0x08, 0x8Es */
	set_idt_gate(32, (uint32_t)irq0,  0x08, 0x8E);
	set_idt_gate(33, (uint32_t)irq1,  0x08, 0x8E);
	set_idt_gate(34, (uint32_t)irq2,  0x08, 0x8E);
	set_idt_gate(35, (uint32_t)irq3,  0x08, 0x8E);
	set_idt_gate(36, (uint32_t)irq4,  0x08, 0x8E);
	set_idt_gate(37, (uint32_t)irq5,  0x08, 0x8E);
	set_idt_gate(38, (uint32_t)irq6,  0x08, 0x8E);
	set_idt_gate(39, (uint32_t)irq7,  0x08, 0x8E);
	set_idt_gate(40, (uint32_t)irq8,  0x08, 0x8E);
	set_idt_gate(41, (uint32_t)irq9,  0x08, 0x8E);
	set_idt_gate(42, (uint32_t)irq10, 0x08, 0x8E);
	set_idt_gate(43, (uint32_t)irq11, 0x08, 0x8E);
	set_idt_gate(44, (uint32_t)irq12, 0x08, 0x8E);
	set_idt_gate(45, (uint32_t)irq13, 0x08, 0x8E);
	set_idt_gate(46, (uint32_t)irq14, 0x08, 0x8E);
	set_idt_gate(47, (uint32_t)irq15, 0x08, 0x8E);
}

void init_descriptor_tables(void)
{
	init_idt();
	load_idt((uint32_t)&idt_p);
}
