#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING 100 /*maximum allowed string length*/

typedef struct { /*store the next number digits*/
    int tens;
    int ones;
}Num;

char * read_next (Num *, char *); /*read next number, store results on struct and return string pointer */
void print_next (Num , FILE *); /*get the current number and print it to the output location*/
