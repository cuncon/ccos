#include <cc/string.h>
#include <cc/stddef.h>
#include <cc/types.h>
#include <cc/compiler-gcc.h>

#include "io.h"
#include "screen.h"

static char * const frame_buffer = (char * const)FRAME_BUFFER_ADDRESS;

static uint16_t get_cursor(void)
{
	uint16_t offset;

	outb(CRTC_INDEX_REG, 0xE);
	offset = inb(CRTC_DATA_REG) << 8;
	outb(CRTC_INDEX_REG, 0xF);
	offset |= inb(CRTC_DATA_REG);

	return (offset << 1);
}

static uint16_t get_offset(uint16_t col, uint16_t row)
{
	if (col >= MAX_COLS || row >= MAX_ROWS)
		return get_cursor();

	return ((row * MAX_COLS + col) << 1);
}

static void set_cursor(uint16_t offset)
{
	offset >>= 1;

	outb(CRTC_INDEX_REG, 0xE);
	outb(CRTC_DATA_REG, (uint8_t)(offset >> 8));
	outb(CRTC_INDEX_REG, 0xF);
	outb(CRTC_DATA_REG, (uint8_t)(offset & 0xff));
}

static uint16_t handle_scrolling(uint16_t cursor)
{
	if (cursor < MAX_ROWS * MAX_COLS * 2)
		return cursor;

	for (int i = 1; i < MAX_ROWS; i++)
		memcpy(frame_buffer + get_offset(0, i - 1),
		       frame_buffer + get_offset(0, i),
		       (size_t)(MAX_COLS << 1));

	memset(frame_buffer + get_offset(0, MAX_ROWS - 1), 0, MAX_COLS << 1);

	return (cursor - (MAX_COLS << 1));
}

void print_char(char c, int col, int row, char attr)
{
	int offset;

	if (unlikely(!attr))
		attr = WHITE_ON_BLACK;

	if (col >= 0 && row >= 0)
		offset = get_offset(col, row);
	else
		offset = get_cursor();

	if (c == '\n') {
		int r = offset / (2 * MAX_COLS);
		offset =  get_offset(MAX_COLS - 1, r);
	} else {
		frame_buffer[offset] = c;
		frame_buffer[offset + 1] = attr;
	}

	set_cursor(handle_scrolling(offset + 2));
}

void print_at(const char *msg, int col, int row)
{
	if (col >= 0 && row >=0)
		set_cursor(get_offset(col, row));

	for (int i = 0; msg[i] != '\0'; i++)
		print_char(msg[i], col, row, WHITE_ON_BLACK);
}

void print(const char *msg)
{
	print_at(msg, -1, -1);
}

void clear_screen(void)
{
	uint16_t *memory = (uint16_t *)frame_buffer;

	for (int i = 0; i < MAX_ROWS * MAX_COLS; i++)
		*(memory + i) = BLANK_CHAR;

	set_cursor(0);
}
