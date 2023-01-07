/**
 * write a version of strcmp
 */

#include <stdio.h>

/* strcmp: return <0 if s < t, 0 if s == t and >0 if s>t */
int strcmp(char *, char *);

int main() {
    char s[] = "a";
    char t[] = "ab";
    printf("%d\n", strcmp(s, t));
    return 0;
}

int strcmp(char *s, char *t) {
    int i;
    for(i=0; s[i]==t[i]; i++) {
        if (s[i] == '\0') {
            return 0;
        }
    }
    return s[i] - t[i];
}


