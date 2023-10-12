#include "uart.h"
#include "shell.h"

void main(){
	// set ip serial console
	uart_init();

	// say hello
	uart_puts("Hello World!\n");

	ShellStart();
}
