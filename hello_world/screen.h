#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <inttypes.h>

uint32_t cursor[2];

uint16_t *ptr_mem(uint32_t line, uint32_t column);

void print_char(uint32_t lig, uint32_t col, char c, uint8_t bg, uint8_t fg, uint8_t cli);

void clear_screen(void);

void place_cursor(uint32_t lig, uint32_t col);

void prepare_cursor(char c);

void console_putbytes(char* chaine, int32_t taille);

void init(void);

#endif
