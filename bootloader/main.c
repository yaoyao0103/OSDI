#include "uart.h"
#include "utils.h"

void loagimg(){
    uart_puts("Kernel size...\n");
    int kernel_size = 0;
    volatile char input;
    while(1){
        input = uart_getc();
        if(!input) break;
        kernel_size = kernel_size * 10 + (input - '0');
    }
    
    volatile unsigned char* kernel;
    kernel = (unsigned char *) 0x80000;
    for(int i = 0; i < kernel_size; i++){
        input = uart_getc();
        kernel[i] = input;
    }
    for(int i = 0; i < 10000; i++){
        asm volatile("nop");
    }
    void (*jump)(void) = kernel;
    uart_puts("Jump to kernel...\n");
    jump();
}

void main(){
    uart_init();
    char *helloworld = "\n\
 _                     _ _               ________  ________ \n\
| |                   | (_)             |_   _|  \\/  |  __ \\\n\
| |     ___   __ _  __| |_ _ __   __ _    | | | .  . | |  \\/\n\
| |    / _ \\ / _` |/ _` | | '_ \\ / _` |   | | | |\\/| | | __ \n\
| |___| (_) | (_| | (_| | | | | | (_| |  _| |_| |  | | |_\\ \\\n\
\\_____/\\___/ \\__,_|\\__,_|_|_| |_|\\__, |  \\___/\\_|  |_/\\____/\n\
                                  __/ |                     \n\
                                 |___/                      \n\
    \n";
    uart_puts(helloworld);
    char input[20];
    while(1) {
        uart_puts("# ");
        char input[20];
        shell(input);


        if(!strcmp(input, "help")) {
            uart_puts("help: print all available commands\n");
            uart_puts("reboot: reboot system\n");
        }
        else if(!strcmp(input, "reboot")) {
            reset(100000);
            uart_puts("input c to cancel reset\n");
            shell(input);
            if(!strcmp(input, "c")) {
                cancel_reset();
            }
        }
        else if(!strcmp(input, "loadimg")){
            loagimg();
        }
        else {
	   	 uart_puts("Error: ");
           	 uart_puts(input);
            	uart_puts(" command not found! Try <help> to check all available commands\n");
        }
    }
}