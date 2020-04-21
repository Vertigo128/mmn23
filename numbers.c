#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING 100

typedef struct { /*store the next number digits*/
    int tens;
    int ones;
}Num;

char * read_next (Num *, char *); /*read next number, store results on struct and return string pointer */
void print_next (Num *, FILE *); /*get the current number and print it to the output location*/


int main (int argc, char *argv[]) {
    
    FILE *inp; /*input file pointer*/
    FILE *out; /*output file pointer*/

    
    Num next_num; /*Next number struct*/
    char inp_row[MAX_STRING]; /*array to store the input line*/
    char *p; /*pointer to the input string array*/
    p = inp_row;

        switch (argc){ /*set the input/output based on command line arguments*/
        case 1: /*if no arguments passed, use the defult stdin/stdout */
            inp = stdin;
            out = stdout;
            break;
        case 2: /*if one argument passed, use the argument as input and defualt output*/
            if (!(inp = fopen (argv[1],"r"))) {
                fprintf (stderr,"\nerror reading file %s\n", argv[1]);
                exit (0);
                }
            out = stdout;
            break;
        case 3: /*if two arguments passed, use them as input and output*/
            if (!(inp = fopen (argv[1],"r"))) {
                fprintf (stderr,"\nerror reading file %s\n", argv[1]);
                exit (0);
                }
            if (!(out = fopen (argv[2],"w"))) {
                fprintf (stderr,"\nerror opening file %s for writing\n", argv[2]);
                exit (0);
                }
                break;
        default: /*if more than 2 arguments passed, send error to stderr*/
            fprintf (stderr,"\nInvalid number of parameters\n");
            exit (0);
        }
    
    // next_num.ones = -1;
    // next_num.tens = -1;

    printf ("Read Number : ");
    fgets(inp_row, MAX_STRING, inp);
    printf ("The string is: %s", inp_row);
    while (1) {
        p = read_next(&next_num, p);
        print_next (&next_num, out);
        if (!p) break;
    }
    
}

char * read_next (Num *next, char *p){
    char temp_str[MAX_STRING];
    int temp_num;
    int i=0;
    char c;
    if (!p) return p;
        while ((c = *p++ == ' ' || c=='\t') )
            ;
        --p;
        if (c==EOF || c=='\n') {
            // next->exit =1; 
            return NULL;
        }
        while (isdigit(temp_str[i] = c = *p)) { /*keep reading numbers*/
            i++;
            p++;
        }
        temp_num = atoi (temp_str);
        next->ones = (int) temp_num%10;
        next->tens = (int) ((temp_num-next->ones)%100)/10;

        if (c==EOF || c=='\n') {
            // next->exit =1; 
            return NULL;
        }
        if (c==' ') return p;
        while ((c = *p++ == ' ' || c=='\t') )
            ;
        return p--;



}

void print_next (Num *next, FILE *out){
    int t = next->tens;
    int o = next->ones;
    const char ones[10][10] = {"zero","one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    const char tens[8][10] = {"twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    const char teens[10][10] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    switch (t){
        case 0:
            fprintf (out,"\n%s",ones[o]);
            break;
        case 1:
            fprintf (out,"\n%s",teens[o]);
            break;
        default:
            fprintf (out,"\n%s",tens[t-2]); 
            if (o!=0) fprintf (out," %s",ones[o]); 
    }
}
