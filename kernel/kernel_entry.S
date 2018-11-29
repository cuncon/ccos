[bits 16]
; switch to 32-bit Protected Mode
cli ; we must switch of interrupts intil we have set-up
    ; the protected mode interrupt vector otherwise
    ; interrupt will run riot
lgdt [gdt_descriptor] ; Load our GDT

mov eax, cr0
or eax, 0x1
mov cr0, eax

jmp CODE_SEG:init_pm  ; Make a far jump (i.e. to a new segment)
                      ; to our 32-bit code. This also forces the
                      ; CPU to flush its cache of pre-fetched
                      ; and real-mode decoded instructions,
                      ; which can cause problems

[bits 32]
; Initialise registers and the stack once in PM
init_pm:
	mov ax, DATA_SEG    ; Now in PM, our old segments are meaningless,
	mov ds, ax          ; so we point our segment registers to the
	mov ss, ax          ; data selector we defined in our GDT
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000    ; update our stack position so it is right
	mov esp, ebp        ; at the top of the free space

	call BEGIN_PM       ; Finally, call some well-known label

BEGIN_PM:
[extern kernel_main]
call kernel_main

jmp $

%include "gdt.S"

[GLOBAL load_idt]
load_idt:
	mov eax, [esp + 4]
	lidt [eax]
	ret
