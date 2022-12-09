/*
 *  init.c: Entry point and basic initialization of the kernel.
 *  Copyright (C) 2022 Aggelos Tselios.
 *
 *  AngelOS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  AngelOS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with AngelOS.  If not, see <https://www.gnu.org/licenses/>.
 */

#if defined(__linux__) && !defined(__ANGOS__EXPLICIT)
#error "You seem to be targeting another operating system. Define __ANGOS__EXPLICIT to disable this check."
#endif

#include <Bool.h>
#include <Types.h>
#include <String.h>

/* Width and height of the VGA output. */
#define VGA_DISPLAY_WIDTH  (80)
#define VGA_DISPLAY_HEIGHT (25)

/* Which row are we currently at. */
static size_t     terminal_row;
/* And which column. */
static size_t     terminal_column;

/* The terminal color. Completely useless as of now since we don't use colors. */
static u8_t   	  terminal_color;
static u16_t* 	  terminal_buffer;

/* The colors we can use at the VGA display. */
typedef enum {
        VGA_COLOR_BLACK         = 0x0000,
	VGA_COLOR_BLUE          = 0x1,
	VGA_COLOR_GREEN         = 0x2,
	VGA_COLOR_CYAN          = 0x3,
	VGA_COLOR_RED           = 0x4,
	VGA_COLOR_MAGENTA       = 0x5,
	VGA_COLOR_BROWN         = 0x6,
	VGA_COLOR_LIGHT_GREY    = 0x7,
	VGA_COLOR_DARK_GREY     = 0x8,
	VGA_COLOR_LIGHT_BLUE    = 0x9,
	VGA_COLOR_LIGHT_GREEN   = 0xA,
	VGA_COLOR_LIGHT_CYAN    = 0xB,
	VGA_COLOR_LIGHT_RED     = 0xC,
	VGA_COLOR_LIGHT_MAGENTA = 0xD,
	VGA_COLOR_LIGHT_BROWN   = 0xE,
	VGA_COLOR_WHITE         = 0xF,
} VGAColor;

/* Sets the entry color of the display. */
static inline u8_t aglSetVGAEntryColor(u32_t fg, u32_t bg) {
	return fg | bg << 4;
}

static inline u16_t aglVGAEntry(unsigned char uc,
			        const u8_t color) {
	return (u16_t) uc | (u16_t) color << 8;
}

/* 
 * Initializes the VGA Display. First function called when entering the kernel, takes
 * care of a variety of subroutines to allow us to display text.
 */
void aglInitializeConsole(void) {
	terminal_row    = 0;
	terminal_column = 0;
	terminal_color  = aglSetVGAEntryColor(VGA_COLOR_RED, VGA_COLOR_BLACK);
	terminal_buffer = (u16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_DISPLAY_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_DISPLAY_WIDTH; x++) {
			const size_t index = y * VGA_DISPLAY_WIDTH + x;
			terminal_buffer[index] = aglVGAEntry(' ', terminal_color);
		}
	}
}

inline void aglSetConsoleColor(u8_t color) {
	terminal_color = color;
}

void aglEntryAt(char c, u8_t color, size_t x, size_t y)
{
	const size_t index     = y * VGA_DISPLAY_WIDTH + x;
	terminal_buffer[index] = aglVGAEntry(c, color);
}

static inline void aglPutChar(char c) {
	aglEntryAt(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_DISPLAY_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_DISPLAY_HEIGHT)
			terminal_row = 0;
	}
}

static inline void aglWriteTerminal(const char *data, size_t size) {
	for (size_t i = 0; i < size; i++)
		aglPutChar(data[i]);
}

static inline void aglConsoleNewline() {
	if (terminal_row >= VGA_DISPLAY_HEIGHT) terminal_row = 0;
	else terminal_row++;
}

static inline void aglWriteString(const char *string) {
	aglWriteTerminal(string, strlen(string));
	aglConsoleNewline();
}

void _aglKernel(void) {
	aglInitializeConsole();
	aglWriteString("Welcome to AngelOS !");

	aglSetConsoleColor(VGA_COLOR_WHITE);
	aglWriteString("Kernel loaded. Preparing to enter host environment...");
}