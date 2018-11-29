; load dh sectors to es:bx from drive dl
disk_load:
	pusha

	push dx			; store dx on stack so later we can recall
					; how many sectors were request to be read,
					; even if it is altered in the meantime

	mov ah, 0x02	; BOIS read sector function
	mov al, dh		; read dh sectors
	mov ch, 0x00	; select cylinder 0
	mov dh, 0x00	; select head 0
	mov cl, 0x02	; start reading from second sector
					; (i.e. after the boot sector)
	int 0x13		; BIOS interrupt

	jc disk_error	; jump if carry flag set

	pop dx
	cmp al, dh
	jne sectors_error

	popa
	ret

disk_error:
	mov bx, DISK_ERROR
	call print_string
	mov dh, ah
	call print_hex
	call print_nl
	jmp disk_loop

sectors_error:
	mov bx, SECTORS_ERROR
	call print_string

disk_loop:
	jmp $

DISK_ERROR:
	db "Disk read error: ", 0
SECTORS_ERROR:
	db "Incorrect number of sectors read", 0

;
; print: prints string in bx to screen
;
print_string:
	pusha

start:
	mov al, [bx] ; bx is the base address for the string
	cmp al, 0
	je print_string_done ; exit if get terminate character

	mov ah, 0x0e ; tty mode
	int 0x10

	add bx, 1
	jmp start

print_string_done:
	popa
	ret

;
; print_hex: prints hex in dx to screen
;
print_hex:
	pusha

	mov cx, 0 ; index

print_hex_loop:
	cmp cx, 4
	je end

	; 1. convert last char of dx to ascii
	mov ax, dx
	and ax, 0x000f
	add al, 0x30 ; add 0x30 to N to convert it to ASCII "N"
	cmp al, 0x39 ; if N > 9, add extra 8 to represent 'A' to 'F'
	jle step2
	add al, 7 ; 'A' is ASCII 65 instead of 58

step2:
	; 2. get the correct position of the string to place our ASCII char
	; bx <- base address + string length - index of char
	mov bx, HEX_OUT + 5
	sub bx, cx
	mov [bx], al
	ror dx, 4

	add cx, 1
	jmp print_hex_loop

end:
	; print receivers parameters in bx
	mov bx, HEX_OUT
	call print_string

	popa
	ret

;
; print_nl: prints a new line
;
print_nl:
	pusha

	mov ah, 0x0e
	mov al, 0x0a ; newline char
	int 0x10
	mov al, 0x0d ; carriage return
	int 0x10

	popa
	ret

HEX_OUT:
	db '0x0000', 0 ; reserve memory for our new string
