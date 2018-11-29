all: ccos-image

ccos-image: bootloader.bin kernel.bin
	cat bootloader/bootloader.bin kernel/kernel.bin > $@

bootloader.bin:
	cd bootloader && $(MAKE)

kernel.bin:
	cd kernel && $(MAKE)

clean:
	$(RM) -rf ccos-image
	cd kernel && $(MAKE) $@
	cd bootloader && $(MAKE) $@

run: ccos-image
	qemu-system-i386 -fda $<

.PHONY: all clean run
