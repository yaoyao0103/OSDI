#include "utils.h"

int pow(int base, int exponent)
{
    int result = 1;
    for ( ; exponent > 0; exponent--)
    {
        result = result * base;
    }
    return result;
}

int strcmp(char* a,char* b){
        while(*a){
                if(*a!=*b)return 1;
                a++;
                b++;
        }
        if(*a!=*b)return 1;
        return 0;
}

int strlen ( char * s )
{
    int i = 0;
    while ( 1 )
    {
        if ( *(s+i) == '\0' )
            break;
        i++;
    }

    return i;
}

void substr(char s[20], char target[20], int start, int len){
	if(start > len) return 0;
	int i = 0;
	for(i = start; i < start+len; i++){
		target[i-start] = s[i];
	}
	target[i] = '\0';
}

// https://www.geeksforgeeks.org/convert-floating-point-number-string/
void itoa (int x, char str[], int d) 
{ 
    int i = 0; 
    while (x) { 
        str[i++] = (x % 10) + '0'; 
        x = x / 10; 
    } 
  
    // If number of digits required is more, then 
    // add 0s at the beginning 
    while (i < d) 
        str[i++] = '0'; 
    
    str[i] = '\0'; 
    reverse(str); 
} 

// https://www.geeksforgeeks.org/convert-floating-point-number-string/
void ftoa(float n, char* res, int afterpoint) 
{ 
    // Extract integer part 
    int ipart = (int)n; 
  
    // Extract floating part 
    float fpart = n - (float)ipart; 
  
    // convert integer part to string 
    itoa(ipart, res, 0); 
    int i = strlen(res);
  
    // check for display option after point 
    if (afterpoint != 0) { 
        res[i] = '.'; // add dot 
  
        // Get the value of fraction part upto given no. 
        // of points after dot. The third parameter  
        // is needed to handle cases like 233.007 
        fpart = fpart * pow(10, afterpoint); 
  
        itoa((int)fpart, res + i + 1, afterpoint); 
    } 
}

void reverse ( char * s )
{
    int i;
    char temp;

    for ( i = 0; i < strlen(s) / 2; i++ )
    {
        temp = s[strlen(s) - i - 1];
        s[strlen(s) - i - 1] = s[0];
        s[0] = temp;
    }
}

int ls(char input[20], int readcontent)
{
    volatile unsigned char *kernel = (unsigned char *) 0x8000000;
    //volatile unsigned char *kernel = (unsigned char *) 0x20000000;
    volatile unsigned char *filename;
    int file_size;
    int name_size;
    int file_size_offset    = 6+8+8+8+8+8+8;
    int name_size_offset    = 6+8+8+8+8+8+8+8+8+8+8+8;

    while(1){ 
        file_size = 0;
        name_size = 0;
        
        for(int i=0;i<8;i++){
            if(kernel[file_size_offset + i] >= 'A' && kernel[file_size_offset + i] <= 'F')
                file_size = file_size * 0x10 + ((int)kernel[file_size_offset + i]) - 'A' + 0xA;            
            else
                file_size = file_size * 0x10 + ((int)kernel[file_size_offset + i]) - '0' ;

            if(kernel[name_size_offset + i] >= 'A' && kernel[name_size_offset + i] <= 'F')
                name_size = name_size * 0x10 + ((int)kernel[name_size_offset + i]) - 'A' + 0xA;
            else
                name_size = name_size * 0x10 + ((int)kernel[name_size_offset + i]) - '0' ;         
        }

        name_size += 0x6E;

        if((file_size % 4) != 0)
            file_size += (4 - (file_size % 4));

        if((name_size % 4) != 0)
            name_size += (4 - (name_size % 4));

        filename = (unsigned char *) kernel + 0x6E;

        if(!strcmp(kernel + 0x6E, "TRAILER!!!"))
            return 0;

        if(strcmp(kernel + 0x6E, ".") && !readcontent){
            uart_puts(filename);
            uart_puts("\n");
        }
        if(!strcmp(kernel + 0x6E, input) && readcontent){
            for(int i=0; i<file_size; i++){
                uart_send(*(kernel + name_size + i));
                if(!strcmp(*(kernel + name_size + i),'\n')) uart_send('\r');
            }                
            return 1;
        }

        kernel += file_size + name_size ;
    }

}

int checkcat(char *input){
	char str[4] = "cat";
	for(int i = 0; i < 3; i++){
		if(input[i] != str[i]) return 0;
	}
	return 1;
}

void cat(char input[20]){
    int len = strlen(input);
    volatile unsigned char *kernel = (unsigned char *) 0x8000000;
    //volatile unsigned char *kernel = (unsigned char *) 0x20000000;
    volatile unsigned char *filename;
    int file_size;
    int name_size;
    int file_size_offset    = 6+8+8+8+8+8+8;
    int name_size_offset    = 6+8+8+8+8+8+8+8+8+8+8+8;
    char target[20] = {0};
    substr(input, target, 4, len-4);



    while(1){ 
        file_size = 0;
        name_size = 0;
        
        for(int i=0;i<8;i++){
            if(kernel[file_size_offset + i] >= 'A' && kernel[file_size_offset + i] <= 'F')
                file_size = file_size * 0x10 + ((int)kernel[file_size_offset + i]) - 'A' + 0xA;            
            else
                file_size = file_size * 0x10 + ((int)kernel[file_size_offset + i]) - '0' ;

            if(kernel[name_size_offset + i] >= 'A' && kernel[name_size_offset + i] <= 'F')
                name_size = name_size * 0x10 + ((int)kernel[name_size_offset + i]) - 'A' + 0xA;
            else
                name_size = name_size * 0x10 + ((int)kernel[name_size_offset + i]) - '0' ;         
        }

	
	name_size += 0x6E;

        if((file_size % 4) != 0)
            file_size += (4 - (file_size % 4));

        if((name_size % 4) != 0)
            name_size += (4 - (name_size % 4));

        filename = (unsigned char *) kernel + 0x6E;
	
	if(!strcmp(kernel + 0x6E, "TRAILER!!!")){
	    uart_puts("Error: ");
 	    uart_puts(target);
    	    uart_puts(" file not found!\n");		
	    return;
	}

	if(!strcmp(kernel + 0x6E, target)){
            for(int i=0; i<file_size; i++){
                uart_send(*(kernel + name_size + i));
                if(!strcmp(*(kernel + name_size + i),'\n')) uart_send('\r');
            }                
            return 1;
        }

        kernel += file_size + name_size ;
    }
}

void shell(char *input) {
    int index = 0;
    char c;
    do {
        c = uart_getc();
        input[index++] = (c != '\n')? c : '\0';
        uart_send(c);
    }while(c != '\n');
    uart_puts("\r");
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

    // uart_puts ("                                                                                      \n");
    // uart_puts ("                                                                                      \n");
    // uart_puts ("                                                    _    _,__    _                    \n");
    // uart_puts ("                                              _pgN0MM00M0MMMMM0M000MNNpgpppq_         \n");
    // uart_puts ("                                              0M^'                     `^~7M0&        \n");
    // uart_puts ("                                              &                              0        \n");
    // uart_puts ("                                             ]#                              0        \n");
    // uart_puts ("                                             ]f                              0        \n");
    // uart_puts ("                                             4f                              0        \n");
    // uart_puts ("                                             0                              ]0        \n");
    // uart_puts ("                                             #                              ]0        \n");
    // uart_puts ("                                             #                              ]0        \n");
    // uart_puts ("                                            ]&                              4#        \n");
    // uart_puts ("                                            ]#                              ##        \n");
    // uart_puts ("                                            jA                              MA        \n");
    // uart_puts ("                                            05                              0f        \n");
    // uart_puts ("                                            M                               0         \n");
    // uart_puts ("                                            0                              ]0         \n");
    // uart_puts ("                                           ]0                              4#         \n");
    // uart_puts ("                                           j0                              Bf         \n");
    // uart_puts ("                                           #0                              B!         \n");
    // uart_puts ("                                           B&        _______,pqggpgpqpM0M0N0          \n");
    // uart_puts ("                                           000NMMM0MM000MMMM~~~~~~~'^`^```B0          \n");
    // uart_puts ("                                          ]0P~                            ]#          \n");
    // uart_puts ("                                          ]#                              MP          \n");
    // uart_puts ("                                          Q&                              0f          \n");
    // uart_puts ("                                          #&                             ]06  _       \n");
    // uart_puts ("                                          0f                         _,,p0000M00      \n");
    // uart_puts ("                                          0'            __,,gggp0MM00000000~~``       \n");
    // uart_puts ("                                      _ _j0q,gggpgp0MMM000MM00000000000000&           \n");
    // uart_puts ("                              00M00M000M000MM@M~~~^    ]0     ^~MM00000000f           \n");
    // uart_puts ("    __,      ,ggg_             ~~~0F~`]0~              ]0           '70000f           \n");
    // uart_puts ("   gMM0g   qMF~^'Mp               Q   Q0               ]#              ~#0            \n");
    // uart_puts ("  #'   M0p05     '0               #   #&               4#               ]0            \n");
    // uart_puts (" gf     MM'       0               #   Q#               0M               j&            \n");
    // uart_puts (" 0      ^^       _0               #   `0_             0@             _yQMc            \n");
    // uart_puts ("M&               #H               H    '0g          p#M           _y*^ J0             \n");
    // uart_puts ("4&              j#               ]&     '0MNgggpgg00@'         _p&~]  j0`             \n");
    // uart_puts (" 0             jM'               i6      0f~~~~'~~        _,g+~ E  ] p0f              \n");
    // uart_puts (" M&           p0'                0#      #6          __yaMP`    #  jM0'               \n");
    // uart_puts ("  Bp        _g0                 N00&     '0p___,ma#V'^    6     &g00~                 \n");
    // uart_puts ("   M&     _pMP                 00000&      M0#_   f       !  __p0M~                   \n");
    // uart_puts ("    '0gpgg0~                 _0000000&       ~M0Np&______gQp0MM^                      \n");
    // uart_puts ("      ~M7^                  _000000000A          `~~MMMMF~~                           \n");
    // uart_puts ("                            '~~'~~` `                                                 \n");
    // uart_puts ("                                                                                      \n");
    // uart_puts ("                                                                                      \n");
}
