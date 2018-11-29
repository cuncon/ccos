# ccOS
A toy operating system

# Table of Contents
* [OS development](#OS-development)
    * [Booting process](#Booting-process)
    * [BIOS](#BIOS)
    * [Bootloader](#Bootloader)

# OS development
## Booting process
```
                   ------      ------------      --------      ----
                  | BIOS | -> | Bootloader | -> | Kernel | -> | OS |
                   ------      ------------      --------      ----
```

## BIOS
```
When a PC is turned on, the computer will start a small program that adheres to Basic Input Output
System standard. This program is usually stored on a read only memory chip on the motherboard of
the PC. Modern operating systems do not use the BIOS functions, they use drivers that interact
directly with the hardware, bypassing the BIOS. Today, BIOS mainly runs some early diagnostics
(power-on-self-test) and then transfers control to the bootloader.
```

## Bootloader
### A machine code boot sector
```
e9 fd ff 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
*
00 00 00 00 00 00 00 00 00 00 00 00 00 00 55 aa

```
* The first three bytes, in hdexadecimal as 0xe9, 0xfd and 0xff, are actually machine code
instruction, as defined by the CPU manufacturer, to perform an endless jump.
* The last two bytes, 0x55 and 0xaa, make up the magic number, which tells BIOS that this is
indeed a boot block and not just data that happens to be on a drive's boot sector.

### A simple boot sector written in assembly language
```
jmp $                   ; jump to address of current instruction

times 510-($-$$) db 0   ; Tell our assembly compiler to pad out our program with enough zero
                        ; bytes to bring us to the 510th byte

dw 0xaa55               ; Last two bytes form the magic number
```

