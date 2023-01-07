#include <stdio.h>

#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

/* count char, words and lines in input */

int main() {
    int ch, nc, nw, nl, state;
    nc = nw = nl = 0;
    state = OUT;

    while ((ch = getchar()) != '9') {
        ++nc;
        if (ch == '\n') {
            ++nl;
        }
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            state = OUT;
        } else if (state == OUT){
            ++nw;
            state = IN;
        }
    }
    printf("line, word, char counts: %d %d %d\n", nl, nw, nc);
    return 0;
}
