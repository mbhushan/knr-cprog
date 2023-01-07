/**
 Exercise 2-10. Rewrite the function lower, which converts upper case letters to lower case,
 with a conditional expression instead of if-else.
 */

#include <stdio.h>

int lower(int ch) {
    return (ch >= 'A' && ch <= 'Z') ? ch + ('a' - 'A') : ch;
}

int main() {
    char st[] = "MANI BHUSHAN SINHA";
    int i=0;

    printf("original: %s\n", st);
    while(st[i] != '\0') {
        st[i] = lower(st[i]);
        ++i;
    }
    printf("lower case: %s\n", st);
    return 0;
}
