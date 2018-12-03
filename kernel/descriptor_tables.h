#ifndef _DESCRIPTOR_TABLES_H
#define _DESCRIPTOR_TABLES_H

#include <cc/types.h>
#include <cc/compiler-gcc.h>

#define IDT_ENTRY_MAX 256

/* Interrupt descriptor entry */
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

/* PICs */
#define MASTER_PIC_IO 0x20 /* IO base address for master PIC */
#define MASTER_PIC_COMMAND MASTER_PIC_IO
#define MASTER_PIC_DATA    (MASTER_PIC_IO + 1)
#define SLAVE_PIC_IO 0xA0 /* IO base address for slave PIC */
#define SLAVE_PIC_COMMAND SLAVE_PIC_IO
#define SLAVE_PIC_DATA    (SLAVE_PIC_IO + 1)

extern void init_descriptor_tables(void);

#endif /* _DESCRIPTOR_TABLES_H */
