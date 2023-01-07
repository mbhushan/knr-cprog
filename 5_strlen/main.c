/**
 * write a program to return the length of the string.
 */

#include <stdio.h>

int strlen(char *s);

int main() {
    char s[] = "programming in c";
    printf("string s len: %d\n", strlen(s));
    return 0;
}

int strlen(char *s) {
    int slen = 0;
    while(*s++) slen++;
    return slen;
}