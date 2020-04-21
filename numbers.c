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
void print_next (Num , FILE *); /*get the current number and print it to the output location*/


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
   
    printf ("Read Number : ");
    fgets(inp_row, MAX_STRING, inp); /*use the custom inp as input location*/
    printf ("The string is: %s", inp_row); /*print current string to screen*/
    while (1) {
        p = read_next(&next_num, p); /*call function to read next line and return the next number pointer*/
        print_next (next_num, out); /*call function to print current number as words*/
        if (!p) break;
    }
    
}

/* The function get Num struct pointer and char pointer, 
read the next number and store the results on the struct,
send back pointer to the next digit on the string and NULL if EOF*/

char * read_next (Num *next, char *p){
    char temp_str[MAX_STRING]; /*temp string to store current number*/
    int temp_num; /*temp int to store current number as int*/
    int i=0;
    int c;
    if (!p) return p; 
        while ((c = *p++ == ' ' || c=='\t') ) /*keep skipping next whitespaces*/
            ;
        --p;
        if (c==EOF || c=='\n') { /*exit if EOF/EOL reched*/
            return NULL;
        }
        while (isdigit(temp_str[i] = c = *p)) { /*keep reading numbers and store at temp_str*/
            i++;
            p++;
        }
        temp_num = atoi (temp_str); /*convert the temp_str to int*/
        next->ones = (int) temp_num%10; /*calculate and store the ones digit*/
        next->tens = (int) ((temp_num-next->ones)%100)/10; /*calculate and store the tens digit*/

        if (c==EOF || c=='\n') { /*exit if EOF/EOL */
            return NULL;
        }
        else if (c==' ') return p;  /*return pointer for next number*/
        else { /*send error if input is invalid*/
            fprintf (stderr,"\nInvalid input\n");
            exit (0);
        }



}

/*The function recieve Num struct with current number data and output file pointer
the fuction print the number as words to the output file location*/

void print_next (Num next, FILE *out){
    int t = next.tens; /*t store the tens digit*/
    int o = next.ones; /*o store the ones digit*/
    const char ones[10][10] = {"zero","one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    const char tens[8][10] = {"twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    const char teens[10][10] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

    switch (t){
        case 0: /*if number is 0-9, use ones array for output*/
            fprintf (out,"\n%s",ones[o]);
            break;
        case 1: /*if number if 10-19 use teens array for output*/
            fprintf (out,"\n%s",teens[o]);
            break;
        default: /*on all other cases use tens and ones for output*/
            fprintf (out,"\n%s",tens[t-2]); 
            if (o!=0) fprintf (out," %s",ones[o]); 
    }
}
