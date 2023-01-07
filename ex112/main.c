#include <stdio.h>

/**
 * Write a program that prints its input one word per line.
 */

#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

int main() {
    char ch;
    short state;
    state = OUT;

    while ((ch = getchar()) != '9') {
        if (ch != ' ' && ch != '\t' && ch != '\n') {
            if (state == OUT) state = IN;
            putchar(ch);
        } else if (state == IN) {
            state = OUT;
            putchar('\n');
        }
    }
    return 0;
}
