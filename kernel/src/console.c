#include "console.h"
#include "console_colors.h"
#include "types.h"
#include "asm_wrapper.h"
#include "string.h"

#define CURSOR_LSB_MASK             0x00FF
#define CURSOR_MSB_MASK             0xFF00
#define CURSOR_INDEX_LOW            0x0F
#define CURSOR_INDEX_HIGH           0x0E
#define CRT_INDEX_REGISTER_PORT     0x3D4
#define CRT_DATA_REGISTER_PORT	    0x3D5
#define COLS                        80
#define LINES                       25
#define VIDEO_MEMORY_ADDRESS        0xB8000

#define VALID_LINE_NUMBER(l)        (l >= 0 && l < LINES)
#define VALID_COLUMN_NUMBER(c)      (c >= 0 && c < COLS)
#define VALID_CURSOR(cursor)        VALID_LINE_NUMBER(cursor.x) &&\
                                    VALID_COLUMN_NUMBER(cursor.y)

static console_state_t console_state;

static uint16_t* get_pointer_to_address(uint8_t line, uint8_t column){
    if (!VALID_LINE_NUMBER(line) || !VALID_COLUMN_NUMBER(column))
        return NULL;
    return (uint16_t* ) (VIDEO_MEMORY_ADDRESS + 2 * (column + line * COLS));
}

static inline void print_char(const uint8_t line, const uint8_t column, const char c){
    volatile uint16_t* mem = get_pointer_to_address(line, column);
    *mem = (uint16_t) (get_colorscheme() << 8 | c); 
}

static void clear_console(void){
    for (uint8_t i = 0; i < LINES; ++i)
        for (uint8_t j = 0; j < COLS; ++j)
            print_char(i, j, ' ');
}

void init_console(void){
    set_cursor_position((cursor_position_t) {0, 0});
    set_colorscheme((colorscheme_t) COLOR_SCHEME(WHITE, BLACK));
    clear_console();
}

void set_colorscheme(colorscheme_t color){
    console_state.colorscheme = color;
}

colorscheme_t get_colorscheme(void){
    return console_state.colorscheme;
}

void scroll(uint8_t lines){
    if (lines >= LINES)
        return;
    
    // TODO

}

void set_cursor_position(cursor_position_t position){
    if (!VALID_CURSOR(position))
        return;
    else {
        /* Update the cursor's position in the console display */
        int16_t new_position = position.x + position.y * COLS;
        /* First send LSB */
        outb(CRT_INDEX_REGISTER_PORT, CURSOR_INDEX_LOW);
        outb(CRT_DATA_REGISTER_PORT, new_position & CURSOR_LSB_MASK);
        /* Then MSB */
        outb(CRT_INDEX_REGISTER_PORT, CURSOR_INDEX_HIGH);
        outb(CRT_DATA_REGISTER_PORT, (new_position & CURSOR_MSB_MASK) >> 8);

        /* Update internal state */
        console_state.cursor.x = position.x;
        console_state.cursor.y = position.y;
    }
}

cursor_position_t get_cursor_position(void){
    return console_state.cursor;
}
