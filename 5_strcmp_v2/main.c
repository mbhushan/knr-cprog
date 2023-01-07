/**
 * strcmp program with ptrs
 */

#include <stdio.h>

/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp(char *, char *);

int main() {
    char *s[] = {"a", "ab", "abc", "zbc"};
    char *t[] = {"abc", "abc", "abc", "abc"};
    int n = 4;

    while(n--) {
        printf("%s, %s: %d\n", s[n], t[n], strcmp(s[n], t[n]));
    }
    return 0;
}

int strcmp(char *s, char *t) {
    for (; *s == *t; s++, t++) {
        if (*s == '\0') return 0;
    }

    return *s - *t;
}