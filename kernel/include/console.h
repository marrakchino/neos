#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "console_colors.h"

typedef struct {
    uint8_t x;
    uint8_t y;
} cursor_position_t;

typedef struct {
    cursor_position_t cursor;
    colorscheme_t colorscheme;
} console_state_t;

void init_console(void);

void set_colorscheme(colorscheme_t colorscheme);
colorscheme_t get_colorscheme(void);

void scroll(uint8_t lines);

void set_cursor_position(cursor_position_t position);
cursor_position_t get_cursor_position(void);


#endif
