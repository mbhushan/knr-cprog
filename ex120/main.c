#include <stdio.h>

/**
 * Exercise 1.20 -
 *
 * Write a Program detab, which replaces tabs in the input with a proper
 * number of blanks to spaces
 *
 **/

#include <stdio.h>

#define TABINC 4
#define WHITESPACE '#'

int main(void) {

    int nb, pos, ch;
    nb = 0;
    pos = 1;

    while ((ch = getchar()) != EOF) {
        if (ch == '\t') {
            nb = TABINC - ((pos-1)%TABINC);
            while (nb > 0) {
                putchar(WHITESPACE);
                ++pos;
                --nb;
            }
        } else if (ch == '\n') {
            putchar(ch);
            pos = 1;
        } else {
            putchar(ch);
            ++pos;
        }
    }
    return 0;
}
