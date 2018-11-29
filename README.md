# ccOS
A toy operating system

# Table of Contents
* [OS development](#OS-development)
    * [Booting process](#Booting-process)
    * [BIOS](#BIOS)
    * [Bootloader](#Bootloader)
    * [Kernel](#Kernel)
         * [Interact with the Hardware](#Interact_with_the_Hardware)
         * [Framebuffer](#Framebuffer)
         * [Segmentation](#Segmentation)
* [References](#References)

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

## Kernel
### Interact with the Hardware
#### Memory-mapped I/O
```
You write to a specific memory address and the hardware will be updated with the new data.
```
#### I/O ports
```
Assembly code instructions out and in must be used to communicate with the hardware.
The instruction out takes two parameter: the address of the I/O port and the data to send.
The instruction in takes a single parameter, the address of the I/O port, and returns data
from the hardware.
```

```
; Switch on the motor of the first drive
mov dx, 0x3f2      ; must use dx to store port address
in al, dx          ; Read contents of port to al
or al, 00001000b   ; Switch on the motor bit
out dx, al         ; Update dor of the device

```

For more in/out: [Inline Assembly](https://wiki.osdev.org/Inline_Assembly/Examples)

### Framebuffer
#### Text mode
#### Graphic mode

### Segmentation
```
Segmentation in x86 means accessing the memory through segments. Segments are portions of the
address space, possibly overlapping, specified by a base address and a limit.
To enable segmentation you need to set up a table that describles each segment - a segment
descriptor table. In x86, there are two types of descriptor tables: the Global Descriptor Table
(GDT) and Local Descriptor Tables (LDT). An LDT is set up and managed by user-space processes,
and all processes have their own LDT. The GDT is shared by everyone - it's global.
```
#### Real mode
```
In Real Mode you use a logical address in the form A:B to address memory. This is translated into
a physical address using the equation:
       Physical address = (A * 0x10) + B
The registers in pure real-mode are limited to 16 bits for addressing. 16 bits can represent any
integer between 0 and 64k. This means that if we set A to be a fixed value and allow B to change
we can address a 64k area of memory. This 64k area is called a segment.
       A = a 64k segment B = offset within the segment
```

| -     | -                         |
|:-----:|---------------------------|
| CS    | Code segment              |
| DS    | Data segment              |
| SS    | Stack segment             |
| ES    | Extra segment             |
| FS    | General purpose segment   |
| GS    | General purpose segment   |


```
# Operation that affect segment registers
Beside CS, segment registers may be loaded with a general register (mov ds, ax) or with
the top-of-stack (pop ds).
CS is the only segment register that cannot be directly altered. The only time CS is altered is when
the code switches execution into another segment. The only commands that can do this are:
## Far jump
Here the new value for CS is encoded in the jump instruction. Eg: jmp 0x10:0x100 says to load CS with
segment 0x10 and IP with 0x100. CS:IP is the logical address of the instruction to be executed.
## Far call
This is exactly the same as a far jump, but the current values of CS/IP are pushed onto the stack before
executing at the new position.
## INT
The processor reads the new value of CS/IP from the Interrupt Vector Table and then executes what is
effectively a far call after pushing EFLAGS onto the stack.
## Far return
Here the processor pops the return segment/offset from the stack into CS/IP and switches execution
to that address.
## IRET
This is exactly the same as a far return apart from the processor popping EFLAGS off the stack in
addition to CS/IP. Apart from these cases no instruction alters the value of CS.
```

#### Protected mode
```
In Protected mode you use a logical address in the form A:B to address memory. As in Real mode, A
is the segment part and B is the offset within that segment. Our segments now have a maximum size
of 4 GiB since this registers in protected mode are limited to 32 bits.

  31                           0             31                           0
   ----------------------------               ----------------------------
  |      segment selector      |             | offset (effective address) |
   ----------------------------               ----------------------------
          |                                                |
          |              GDT                               |
          |      -------------------                       |
          |     |                   |                      |
          |     |                   |                     \_/
          |     |-------------------|
           ---> | Segment desciptor | -----------------> [ + ]
                |-------------------|
                |                   |                      |
                |                   |                      |
                 -------------------                      \_/
                                             31                            0
                                              -----------------------------
                                             |       Linear address        |
                                              -----------------------------

A GDT/LDT is an array of 8-byte segment descriptors. The first descriptor in the GDT is always
a null descriptor and can never be used to access memory. At least two segmnet descriptors are
(plus the null descriptor) needed for the GDT.

     31               24  23  22  21   20 19    16  15 14 13   12  11   8 7                0
      -------------------------------------------------------------------------------------
     |                 |   |   |   |  A  |  Seg.  |   |  D  |     |      |                 |
     |   Base 31:24    | G |D/B| L |  V  |  Limit | P |  P  |  S  | Type | Base 23:16      |  4
     |                 |   |   |   |  L  |  19:16 |   |  L  |     |      |                 |
      -------------------------------------------------------------------------------------

     31                                         16 15                                      0
      -------------------------------------------------------------------------------------
     |                                            |                                        |
     |        Base Address 15:00                  |         Segment Limit 15:00            |  0
     |                                            |                                        |
      -------------------------------------------------------------------------------------

                                      8-byte segment descriptor
```

#### [Notes regarding C](https://wiki.osdev.org/Segmentation#Notes_Regarding_C)
