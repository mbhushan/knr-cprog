/**
 * Exercise 5-5. Write versions of the library functions strncpy, strncat, and strncmp, which operate on at most the
 * first n characters of their argument strings. For example, strncpy(s,t,n) copies at most n characters of t to s.
 * Full descriptions are in Appendix B.
 */

#include <stdio.h>

/* strncpy: copy n characters from t to s */
void strncpy(char *s, char *t, int n);
/* strncat: concatanate n characters of t to the end of s */
void strncat(char *s, char *t, int n);
/* strncmp: compare at most n characters of t with s */
int strncmp(char *s, char *t, int n);

int main() {
    char s[] = "Billion Dollars is Cool";
    char t[] = "Lets experience it";
    printf("S: %s\n", s);
    printf("T: %s\n", t);
    strncpy(s, t, 18);
    printf("S after strncpy: %s\n", s);

    char s1[] = "Billion Dollars";
    char t1[] = " is Awesome!";
    printf("S1: %s\n", s1);
    printf("T1: %s\n", t1);
    strncat(s1, t1, 11);
    printf("S1 after strncat: %s\n", s1);

    printf("%d\n", strncmp("abc", "abc", 3));
    printf("%d\n", strncmp("bbc", "abc", 3));
    printf("%d\n", strncmp("abc", "bbc", 3));
    return 0;
}

int strncmp(char *s, char *t, int n) {
    while ((*s == *t) && n-- > 0) {
        s++;
        t++;
    }
    if (*s == '\0' || n == 0) return 0;
    return *s - *t;


}

void strncat(char *s, char *t, int n) {
    while (*s) s++;

    while ((*s++ = *t++) && n-- > 0)
        ;
    *s = '\0';
}
void strncpy(char *s, char *t, int n) {
    while (*t && n-- > 0) {
        *s++ = *t++;
    }
    if (n > 0) *s = '\0';
}