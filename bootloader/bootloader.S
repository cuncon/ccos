; A bootloader that boots a kernel in 32-bit protected mode.

[org 0x7c00]

KERNEL_OFFSET equ 0x1000 ; This is the memory offset to which we will load our kernel

mov bx, WELCOME
call print_string
call print_nl

mov [BOOT_DRIVE], dl

mov bp, 0x9000 ; Set-up the stack
mov sp, bp

call load_kernel

call KERNEL_OFFSET ; Jump to the address of our loaded kernel code

jmp $

%include "print16.S"
%include "disk.S"

[bits 16]
load_kernel:
	mov bx, KERNEL_OFFSET ; Read from disk and store in KERNEL_OFFSET
	mov dh, 15 ; Read the first 15 sectors
	mov dl, [BOOT_DRIVE]
	call disk_load

	ret

; data
BOOT_DRIVE db 0
WELCOME    db "WELCOME ccOS", 0

; padding and magic number
times (510 - ($ - $$)) db 0
dw 0xaa55
