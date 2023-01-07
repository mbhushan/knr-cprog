/**
 * Exercise 5-4. Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s,
 * and zero otherwise.
 */

#include <stdio.h>

/* strend: 1 if t occurs at the end of s, 0 otherwise. */
int strend(char *s, char *t);

int main() {
    char s[] = "C programming is lot of fun!";
    char t[] = "lot of fun!";
    printf("strend: %d\n", strend(s, t));
    return 0;
}

int strend(char *s, char *t) {
    char *bs = s;
    char *bt = t;
    while (*s) s++;
    while (*t) t++;

    while (*s == *t) {
        if (s == bs || t == bt) break;
        s--;
        t--;
    }
    if ((*s == *t) && (t == bt) && (*s != '\0')) {
        return 1;
    }
    return 0;
}