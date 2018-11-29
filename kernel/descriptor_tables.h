#ifndef _DESCRIPTOR_TABLES_H
#define _DESCRIPTOR_TABLES_H

#include <cc/types.h>
#include <cc/compiler-gcc.h>

#define MAX_IDT_ENTRY 256

/* Interrupt gate */
struct idt_entry {
	uint16_t base_lo;  /* The lower 16 bits of the handler address */
	uint16_t segment;  /* Kernel segment selector */
	uint8_t  zero;     /* Always zero */
	uint8_t flags;     /* More flags */
	uint16_t base_hi;  /* The upper 16 bits of the handler address */
} __packed;

typedef struct idt_entry idt_entry_t;

struct idt_pointer {
	uint16_t limit;
	uint32_t base;   /* The first interrupt descriptor in IDT */
} __packed;

typedef struct idt_pointer idt_pointer_t;

extern void init_descriptor_tables(void);

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

#endif
