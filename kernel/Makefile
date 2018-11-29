kernel = kernel.bin

all: $(kernel)

$(kernel): kernel.o
	ld -melf_i386 -o $@ -Ttext 0x1000 kernel.o --oformat binary

kernel.o: kernel.S
	nasm $< -f elf -o $@

clean:
	rm -rf $(kernel) *.o
