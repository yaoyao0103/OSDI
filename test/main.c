#include "uart.h"
#include "shell.h"

void main(){
	// set up serial console
	uart_init();

	// say hello
	print_welcome();

	//ShellStart();
}

void print_welcome(){
    char* helloworld;
    helloworld = "\n _   _      _ _         __        __         _     _ \n\
| | | | ___| | | ___    \\ \\      / /__  _ __| | __| |\n\
| |_| |/ _ \\ | |/ _ \\    \\ \\ /\\ / / _ \\| '__| |/ _` |\n\
|  _  |  __/ | | (_) |    \\ V  V / (_) | |  | | (_| |\n\
|_| |_|\\___|_|_|\\___( )    \\_/\\_/ \\___/|_|  |_|\\__,_|\n\
                    |/                               \n";
    uart_puts(helloworld);
}
