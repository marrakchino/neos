#include "screen.h"
#include "string.h"

void kernel_start(void){
    init(); 
    char* hello_world = "Hello, World!";
    console_putbytes(hello_world, strlen(hello_world));
    for (;;);
}
