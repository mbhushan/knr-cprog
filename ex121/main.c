#include <stdio.h>

/**
 * Exercise 1.21 - Write a Program entab that replaces strings of blanks by
 * the minimum number of tabs and blanks to achieve the same spacing.
 * Use the same tab stops as for detab.
 **/

#define TABSTOP 4
#define IN 1
#define OUT 0

int main() {
    int sp, nsp, i, ch;
    int state, ntab;

    state = OUT;
    nsp = ntab = sp = 0;

    while ((ch = getchar()) != EOF) {
        if (ch == ' ') {
            state = IN;
            nsp++;
        } else {
            if (state == IN) {
                if (nsp >= TABSTOP) {
                    ntab = nsp / TABSTOP;
                    sp = nsp % TABSTOP;

                    for (i=0; i<ntab; i++) putchar('\t');
                    for (i=0; i<nsp; i++) putchar('#');
                } else {
                    for (i=0; i<nsp; i++) putchar('#');
                }
                nsp = 0;
                putchar(ch);
                state = OUT;
            } else putchar(ch);

        }
    }

    return 0;
}
