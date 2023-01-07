/**
 * Exercise 5-3. Write a pointer version of the function strcat that we showed in Chapter 2: strcat(s,t) copies the
 * string t to the end of s.
 */

#include <stdio.h>

/* strcat: copies string t to the end of s */
void strcat(char *s, char *t);

int main() {
    char s[] = "programming ";
    char t[] = "in C is fun!";
    strcat(s, t);
    printf("output: %s\n", s);
    return 0;
}

void strcat(char *s, char *t) {
    while (*s) s++;
    while (*s = *t) {
        s++;
        t++;
    }
}