#include "screen.h"

#include <inttypes.h>
#include <cpu.h>

#define BLACK		0x0
#define WHITE 		0xF 

#define MAX_LINES	25
#define MAX_COLUMNS	80
#define MEM_VIDEO_ADDR	0xB8000

/* computes and returns a pointer corresponding to the memory address
 * specified by line and column */
uint16_t *ptr_mem(uint32_t line, uint32_t column)
{
	return (uint16_t *) (MEM_VIDEO_ADDR + 2*(line*80 + column));
}

void print_char(uint32_t lig, uint32_t col, char c, uint8_t bg, uint8_t fg, uint8_t cli)
{
	uint16_t* ptr = ptr_mem(lig, col);
	*ptr = ((cli << 8|bg << 4|fg) << 8)|c; 
}

void clear_screen(void)
{
	for (uint32_t i_l = 0; i_l < MAX_LINES; i_l++)
	{
		for (uint32_t i_c = 0; i_c < MAX_COLUMNS; i_c++)
			print_char(i_l, i_c, 0, BLACK, WHITE, 0);
	}
}

void place_cursor(uint32_t lig, uint32_t col)
{
	if ((lig < MAX_LINES)&&(lig >= 0)
	&&(col < MAX_COLUMNS)&&(col >= 0))
	{
		outb(0xF, 0x3D4);
		outb(col, 0x3D5);
		outb(0xE, 0x3D4);
		outb(lig, 0x3D5);

		cursor[0] = lig;
		cursor[1] = col;
	}
}

/* prepare the cursor to deal with character c (tab, newline, etc) */
void prepare_cursor(char c)
{
	if (c == (char) 8)
	// backspace \b
		if (cursor[1] == 0) 
			place_cursor(cursor[0] - 1, MAX_COLUMNS - 1);
		else
			place_cursor(cursor[0], cursor[1] - 1);

	else if (c == (char) 9)
	// horizanatal tab \t
		if (cursor[1] + 10 < MAX_COLUMNS)
			place_cursor(cursor[0], cursor[1] + 10);
		else
			place_cursor(cursor[0] + 1, MAX_COLUMNS - cursor[1] + 10);
	
	else if (c == (char) 10)
	// new line \n
	{
		if (cursor[0] == MAX_LINES - 1)
		{
			// screen_stream(); /* not needed */
			place_cursor(cursor[0], 0);
		}
		place_cursor(cursor[0] + 1, 0);
	}
	
	else if (c == (char) 12)
	// line feed \f
	{
		if (cursor[0] == MAX_LINES - 1)
			// screen_stream(); /* not needed */
		place_cursor(cursor[0] + 1, cursor[1] + 1);
	}
	
	else if (c == (char) 13)
	// carriage return \r
		place_cursor(cursor[0], 0);
	
	else if ((c > 31) && (c < 127))
	{
		if (cursor[1] == MAX_COLUMNS - 1)
		{
			if (cursor[0] != MAX_LINES - 1)
			{
				print_char(cursor[0], cursor[1], c, BLACK, WHITE, 0);
				place_cursor(cursor[0] +1, 0);
			}
			else 
			{
				clear_screen();
				print_char(0, 0, c, BLACK, WHITE, 0);
				place_cursor(0, 1);
			}
		}
		else 
		{
			print_char(cursor[0], cursor[1], c, BLACK, WHITE, 0);
			place_cursor(cursor[0], cursor[1] + 1);
		}	
	}
}

void console_putbytes(char* chaine, int32_t taille)
{
	for (uint32_t i = 0; i < taille; i++)
		prepare_cursor(chaine[i]);
}

// clear the screen and place the cursor at (0, 0)
void init(void)
{
	clear_screen();
	place_cursor(0, 0);
}
