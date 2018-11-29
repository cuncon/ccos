kernel = kernel.bin

C_SOURCES = $(wildcard *.c)
S_SOURCES = $(wildcard *.S)

CFLAGS := -Wall -std=gnu99 -I../include

c_objs = ${C_SOURCES:.c=.o}
s_objs = ${S_SOURCES:.S=.s.o}

all: $(kernel)

$(kernel): $(c_objs) $(s_objs) drivers lib
	ld -melf_i386 -o $@ -T kernel.lds *.o ../drivers/*.o ../lib/*.o --oformat binary

drivers:
	cd ../$@ && $(MAKE)

lib:
	cd ../$@ && $(MAKE)

%.o: %.c
	$(CC) $(CFLAGS) -m32 -ffreestanding -c $< -o $@

%.s.o: %.S
	nasm $< -f elf -o $@

clean:
	rm -rf $(kernel) *.o
