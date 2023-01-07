/**
 In Chapter 1 we wrote a program to count the occurrences of each digit, white space, and all other characters,
 using a sequence of if ... else if ... else. Here is the same program with a switch:
 */

#include <stdio.h>

/** count digits, whitespace and others */

int main() {
    int ch, i, nwhite, nother, ndigit[10];

    nwhite = nother = 0;
    for(i=0; i<10; i++) ndigit[i] = 0;

    while((ch = getchar()) != '$') {
        switch (ch) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            ndigit[ch - '0']++;
            break;
            case ' ': case '\t': case '\n':
                nwhite++;
                break;
            default:
                nother++;
                break;
        }
    }
    printf("digits = ");
    for (i=0; i<10; i++) printf(" %d", ndigit[i]);
    printf(" white space: %d, other chars: %d\n", nwhite, nother);

    return 0;
}
