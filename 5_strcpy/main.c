/**
 * write a program to copy string from src to dst.
 */

#include <stdio.h>

void strcpy(char *src, char *dst);

int main() {
    char s[] = "C programming!";
    char d[20];

    strcpy(d, s);
    printf("dst: %s\n", d);
    return 0;
}

void strcpy(char *dst, char *src) {
    while(*dst++ = *src++)
        ;
}