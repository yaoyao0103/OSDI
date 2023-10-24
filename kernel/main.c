#include "uart.h"
#include "reboot.h"
#include "utils.h"
#include "mbox.h"

void main() {
    uart_init();    
    print_welcome();
    while(1) {
        uart_puts("# ");
        char input[20];
        shell(input);

        if(!strcmp(input, "hello")) {
            uart_puts("Hello World!\n");
        }
        else if(!strcmp(input, "help")) {
            uart_puts("hello: print Hello World!\n");
            uart_puts("help: print all available commands\n");
            uart_puts("timestamp: print the time stamp.\n");
            uart_puts("info: get the hardware's information\n");
            uart_puts("reboot: reboot system\n");
        }
	else if(!strcmp(input, "timestamp")){
	    unsigned long int cnt_freq, cnt_tpct;
	    char str[20];
	    
	    asm volatile(
		"mrs %0, cntfrq_el0 \n\t"
		"mrs %1, cntpct_el0 \n\t"
		: "=r" (cnt_freq), "=r" (cnt_tpct)
		:		
	    );
	    ftoa((float)cnt_tpct / cnt_freq, str, 6);
	    uart_puts("[");
	    uart_puts(str);
	    uart_puts("]\n");
	}
	else if(!strcmp(input, "info")){
	    get_board_revision();
            uart_puts("My board revision is: ");
            uart_hex(mailbox[5]);
            uart_puts("\n");
            get_arm_mem();
            uart_puts("My ARM memory base address is: ");
            uart_hex(mailbox[5]);
            uart_puts("\n");
            uart_puts("My ARM memory size is: ");
            uart_hex(mailbox[6]);
            uart_puts("\n");  
	}
        else if(!strcmp(input, "reboot")) {
            reset(100000);
            uart_puts("input c to cancel reset\n");
            shell(input);
            if(!strcmp(input, "c")) {
                cancel_reset();
            }
        }
	else if(!strcmp(input, "ls")){
		ls(input, 0);
	}
	else if(checkcat(input)){
		cat(input);
	}
        else {
	   	 uart_puts("Error: ");
           	 uart_puts(input);
            	uart_puts(" command not found! Try <help> to check all available commands\n");
        }
    }
}
