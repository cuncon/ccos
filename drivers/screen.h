#ifndef _SCREEN_H
#define _SCREEN_H

#define WHITE_ON_BLACK 0x0f
#define BLANK_CHAR (0x20 | WHITE_ON_BLACK << 8)

#define MAX_ROWS 25
#define MAX_COLS 80
#define FRAME_BUFFER_SIZE (MAX_ROWS * MAX_COLS)

#define FRAME_BUFFER_ADDRESS 0xb8000

/* VGA Registers */
#define CRTC_INDEX_REG 0x3D4
#define CRTC_DATA_REG  0x3D5

extern void print_char(char, int, int, char);
extern void print_at(const char *, int, int);
extern void print(const char *);
extern void clear_screen(void);

#endif
