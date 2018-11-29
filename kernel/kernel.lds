/* OUTPUT_FORMAT(elf32-i386); */
/* OUTPUT_ARCH(i386); */

ENTRY(_start);

SECTIONS
{
  .text 0x1000 :
  {
    kernel_entry.s.o (.text)
    kernel.o (.text)
    interrupt.s.o (.text)
    gdt.s.o (.text)
    isr.o (.text)
    descriptor_tables.o (.text)
  }
  .data :
  {
    *(.data)
  }
  .bss :
  {
    *(.bss)
  }
}
