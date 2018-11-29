C_SOURCES = $(wildcard *.c)

CFLAGS := -Wall -std=gnu99 -I../include/

obj = ${C_SOURCES:.c=.o}

all: $(obj)

%.o: %.c
	$(CC) $(CFLAGS) -m32 -ffreestanding -c $< -o $@

clean:
	rm -rf *.o
