numbers:    numbers.o
	gcc -g -ansi -Wall -pedantic numbers.o -o numbers
numbers.o:    numbers.c numbers.h
	gcc -c -ansi -Wall -pedantic numbers.c -o numbers.o