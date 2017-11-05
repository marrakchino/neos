#include "screen.h"

void kernel_start(void){
	init(); 
	console_putbytes("Hi, there!", 10);
	for (;;);
}
