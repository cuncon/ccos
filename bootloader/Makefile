all: bootloader.bin

bootloader.bin: bootloader.S
	nasm -f bin $^ -o $@

clean:
	rm -rf *.bin
