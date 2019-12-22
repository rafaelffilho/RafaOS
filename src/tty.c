#include <tty.h>
#include <types.h>

enum colors {
	black        = 0x0,
	blue         = 0x1,
	green        = 0x2,
	cyan         = 0x3,
	red          = 0x4,
	purple       = 0x5,
	brown        = 0x6,
	gray         = 0x7,
	dark_gray    = 0x8,
	light_blue   = 0x9,
	light_green  = 0xA,
	light_cyan   = 0xB,
	light_red    = 0xC,
	light_purple = 0xD,
	yellow       = 0xE,
	white        = 0xF
};

static uint16_t *const video_mem = (uint16_t *) 0xB8000;
static uint8_t         cursor_x  = 0;
static uint8_t         terminal_color;

uint8_t create_color(uint8_t bg, uint8_t fg) { return (bg << 4) | fg; }

void init_tty() {
	terminal_color = create_color(black, white);

	for (int i = 0; i < 25; ++i)
		for (int j = 0; j < 80; ++j) video_mem[80 * i + j] = 0x0020;
	// Print a blank char in every place, just a ' '
}

void new_line() {
	for (uint8_t i = 1; i < 25; ++i) {
		for (uint8_t j = 0; j < 80; ++j) {
			video_mem[80 * (i - 1) + j] = video_mem[80 * i + j];
		}
	}

	// Clean last line
	for (uint8_t j = 0; j < 80; ++j) video_mem[80 * 24 + j] = 0x0020;

	// Resets cursor to the beging of the line
	cursor_x = 0;
}

void put_char(char c) {
	if (c == '\n') {
		new_line();
		return;
	}

	// Every displayed character is 2 bytes, being 1 - Color & 2 - ASCII code
	video_mem[80 * 24 + cursor_x] = (terminal_color << 8) | c;
	++cursor_x;
}

void printf(char *str) {

	// Print every char until it find a null terminator
	// Yes, this is unsafe, blah blah blah

	while (*str != '\0') {
		put_char(*str);
		++str;
	}
}

void printc(char c) { put_char(c); }

void print_dec(uint32_t value) {
	uint32_t buff = value;
	while (buff != 0) {
		put_char((buff % 10) + 48);
		buff /= 10;
	}
}
