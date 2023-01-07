#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mygetline(char *line, int max);
char *myfgets(char *s, int n, FILE *iop);
int myfputs(char *s, FILE *iop);

int main() {
    char line[100];
    int max = 100;
    while (mygetline(line, max) > 0) {
        printf("%s\n", line);
    }
    return 0;
}

/* mygetline: read a line, return length */
int mygetline(char *line, int max) {
    if (fgets(line, max, stdin) == NULL)
        return 0;
    else
        return strlen(line);
}

/* myfputs: put string s on file iop */
int myfputs(char *s, FILE *iop) {
    int c;
    while (c == *s++) {
        putc(c, iop);
    }
    return ferror(iop) ? EOF: 0;
}


/* get atmost n chars from iop */
char *myfgets(char *s, int n, FILE *iop) {
    register int c;
    register char *cs;

    cs = s;
    while ((--n > 0) && (c = getc(iop)) != EOF) {
        if ((*cs++ = c) == '\n')
            break;
    }
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL: s;
}
