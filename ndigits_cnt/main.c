#include <stdio.h>

int main() {
    int ch, nwhite, nother;
    int ndigit[10];
    nwhite = nother = 0;

    for (int i=0; i<10; ++i) {
        ndigit[i] = 0;
    }

    while ((ch=getchar()) != '$') {
        if (ch == ' ' || ch == '\t' || ch == '\n') ++nwhite;
        if (ch >= '0' && ch <= '9') ++ndigit[ch - '0'];
        else ++nother;
    }

    printf("digits =");
    for (int i=0; i<10; i++) {
        printf(" %d", ndigit[i]);
    }
    printf(", white space: %d, other char: %d\n", nwhite, nother);
    return 0;
}
