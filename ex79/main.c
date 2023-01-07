/*
 * Functions like isupper can be implemented to save space or to save time. Explore both possibilities.
 */
#include <stdio.h>
#include <string.h>

#define isuppersavetime(c) ((c) >= 'A' && (c) <= 'Z') ? 1 : 0

int isupper_savespace(char c);

int main() {
    char str[] = "C Programming Is Awesome!";
    int len = strlen(str);

    for (int i=0; i<len; i++) {
        if  (isupper_savespace(str[i])) {
            putchar(str[i]);
        }
    }
    printf("\n");
    for (int i=0; i<len; i++) {
        if (isuppersavetime(str[i])) {
            putchar(str[i]);
        }
    }
    return 0;
}

int isupper_savespace(char c) {
    if (c >= 'A' && c <= 'Z')
        return 1;
    else
        return 0;
}

