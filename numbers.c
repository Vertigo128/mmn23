#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING 100

typedef struct { /*store the next number*/
    int tens;
    int ones;
    int exit;
}Num;

char * read_next (Num *, char *); /*helper function to read the initial command*/
void print_next (Num *);
int main () {
    Num next_num;
    char inp_row[MAX_STRING];
    char *p;
    p = inp_row;

    next_num.exit = -1;
    next_num.ones = -1;
    next_num.tens = -1;
    next_num.tens = -1;
    printf ("Read Number : ");
    fgets(inp_row, MAX_STRING, stdin);
    while (1) {
        p = read_next(&next_num, p);
        print_next (&next_num);
        if (next_num.exit == 1) break;
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
            next->exit =1; 
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
            next->exit =1; 
            return NULL;
        }
        if (c==' ') return p;
        while ((c = *p++ == ' ' || c=='\t') )
            ;
        return p--;



}

void print_next (Num *next){
    int t = next->tens;
    int o = next->ones;
    const char ones[10][10] = {"zero","one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    const char tens[8][10] = {"twenty", "thirty", "fourty", "fivty", "sixty", "seventy", "eighty", "ninety"};
    const char teens[10][10] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    switch (t){
        case 0:
            printf ("\n%s",ones[o]);
            break;
        case 1:
            printf ("\n%s",teens[o]);
            break;
        default:
            printf ("\n%s",tens[t-2]); 
            if (o!=0) printf (" %s",ones[o]); 
    }




}
