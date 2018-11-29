kernel = kernel.bin

CFLAGS := -Wall -std=gnu99 -I../include

all: $(kernel)

$(kernel): kernel.o kernel_entry.o drivers lib
	ld -melf_i386 -o $@ -Ttext 0x1000 *.o ../drivers/*.o ../lib/*.o --oformat binary

drivers:
	cd ../$@ && $(MAKE)

lib:
	cd ../$@ && $(MAKE)

kernel.o: kernel.c
	$(CC) $(CFLAGS) -m32 -ffreestanding -c $< -o $@

kernel_entry.o: kernel_entry.S
	nasm $< -f elf -o $@

clean:
	rm -rf $(kernel) *.o
