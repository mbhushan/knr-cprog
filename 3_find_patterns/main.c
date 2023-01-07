/* find all lines matching pattern */

#include <stdio.h>

#define MAXLINE 1000

int readline(char line [], int max);
int strindex(char src[], char pattern[]);

char pattern[] = "prog";

int main() {
    char line[MAXLINE];
    int found = 0;

    while (readline(line, MAXLINE) > 0) {
        if (strindex(line, pattern) >= 0) {
            printf("%s\n", line);
            ++found;
        }
    }
    printf("pattern found %d times!", found);

    return 0;
}

/* strindex: return index of pattern in src, -1 if none */
int strindex(char src[], char pattern[]) {
    int i, j, k;

    for (i=0; src[i] != '\0'; i++) {
        for (j=i, k=0; pattern[k] != '\0' && src[j] == pattern[k]; ++j, ++k);

        if (k > 0 && pattern[k] == '\0') return i;
    }

    return -1;
}

/* readline: get line into line, return length */
int readline(char line[], int lim) {
    int ch, i;
    i=0;

    while(--lim > 0 && ((ch = getchar()) != '$') && ch != '\n') line[i++] = ch;

    if (ch == '\n') line[i++] = ch;

    line[i] = '\0';

    return i;
}