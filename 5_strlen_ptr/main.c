/**
 * strlen using ptrs
 */

#include <stdio.h>

/* strlen: return length of the string */
int strlen(char *s);

int main() {
    char s[] = "programming in C!";

    printf("len(\"%s\"): %d\n", s, strlen(s));
    return 0;
}

int strlen(char *s) {
    char *p = s;

    while(*p) p++;

    return p-s;
}