[bits 16]

mov al, 'X'
mov ah, 0x0e
int 0x10

jmp $
