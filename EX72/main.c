/*
    Exercise 7-2. Write a program that will print arbitrary input in a sensible way. As a minimum, it should print
    non-graphic characters in octal or hexadecimal according to local custom, and break long text lines.
*/
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 10
#define OCTLEN 6
#define EOF '$'
#define LINELEN 100
#define FORMAT "%X"

int incr(int pos, int n);
void solutionv2(void);

/* print arbitrary input in sensible way */
int main() {

    solutionv2();

//    int c, pos;
//    pos = 0;
//
//    while ((c = getchar()) != EOF) {
//        if (iscntrl(c) || isspace(c)) {
//            pos = incr(pos, OCTLEN);
//            printf(" %X ", c);
//            if (c == '\n') {
//                pos = 0;
//                putchar(c);
//            }
//        } else {
//            pos = incr(pos, 1);
//            putchar(c);
//        }
//    }
    return 0;
}

void solutionv2(void) {
    int c, i = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n') // reset line length counter
            i = 0;
        else if (++i == LINELEN) // check if equal to line length. If so, print new line and reset counter
        {
            i = 0;
            putchar('\n');
        }
        if (isgraph(c) || isspace(c)) // graphic characters and spaces
            putchar(c);
        else
            printf(FORMAT, c); // non-graphic characters
    }
}

int incr(int pos, int n) {
    if (pos+n < MAXLINE)
        return pos+n;
    else {
        putchar("\n");
        return n;
    }
}
