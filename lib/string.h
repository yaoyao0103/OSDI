#ifndef STRING_H
#define STRING_H

int strcmp(char* a, char* b);
int  strlen     ( char * s );
void itoa	( int x, char str[], int d);
void ftoa       ( float n, char* res, int afterpoint ); 
void reverse	( char *s );
#endif