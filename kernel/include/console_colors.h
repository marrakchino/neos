#ifndef __CONSOLE_COLORS_H__
#define __CONSOLE_COLORS_H__

#define BLACK               0 
#define BLUE                1 
#define GREEN               2 
#define CYAN                3 
#define RED                 4 
#define MAGENTA             5 
#define BROWN               6 
#define LIGHT_GRAY          7 
#define DARK_GRAY           8 
#define LIGHT_BLUE          9 
#define LIGHT_GREEN         10
#define LIGHT_CYAN          11
#define LIGHT_RED           12
#define LIGHT_MAGENTA       13
#define LIGHT_BROWN         14
#define WHITE               15

typedef uint8_t colorsheme_t;

#define COLOR_SCHEME(FG, BG) FG << 4 | BG

#endif
