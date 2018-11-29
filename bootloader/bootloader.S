; A bootloader that boots a kernel in 32-bit protected mode.

[org 0x7c00]

mov bx, WELCOME
call print_string
call print_nl

mov bp, 0x9000 ; Set-up the stack
mov sp, bp

jmp $

%include "print16.S"

; data
BOOT_DRIVE db 0
WELCOME    db "WELCOME ccOS", 0

; padding and magic number
times (510 - ($ - $$)) db 0
dw 0xaa55
