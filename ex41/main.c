/*
 Exercise 4-1. Write the function strrindex(s,t), which returns the position of the rightmost occurrence of t
 in s, or −1 if there is none.
 */

#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int readline(char line[], int limit);
int strrindex_ex(char s[], char t[]);
int strrindex_alt(char s[], char t[]);


int main() {
    char line[MAXLINE];
    int maxinput = 5;
    char pattern[] = "prog";

    while ((maxinput-- > 0) && readline(line, MAXLINE) > 0) {
        printf("%s", line);
        if (strrindex_alt(line, pattern) >= 0) {
            printf("pattern %s found!\n", pattern);
        } else {
            printf("pattern %s not found!\n", pattern);
        }
    }
    return 0;
}

int strrindex_alt(char s[], char t[]) {
    int i, j, k;

    for (i=(strlen(s)- strlen(t)); i>=0; i--) {
        for (j=i, k=0; t[k] != '\0' && s[j] == t[k]; j++, k++);

        if (k>0 && t[k] == '\0') return i;
    };
    return -1;
}
int strrindex_ex(char s[], char t[]) {
    int tlen = strlen(t);
    int slen = strlen(s);

    int i = 0;
    int j = 0, k = 0;
    if (tlen == 0 || tlen > slen) {
        return -1;
    }
    for (i=(slen-tlen); i>=0; i--) {
        j = i;
        while ((k < tlen && j < slen) && (t[k++] == s[j++]));

        if (k == tlen) return i;

        k = 0;
    }
    return -1;
}

int readline(char line[], int limit) {
    int i, ch;
    i = 0;

    while (--limit > 0 && ((ch = getchar())!='\n')) line[i++] = ch;

    if (ch == '\n') line[i++] = '\n';

    line[i] = '\0';

    return i;
}
