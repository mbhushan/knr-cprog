/**
 * getint: get next integer from input into *pn
 */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);
int getint(int *);

int main() {
    int p;
    int c;
    while ((c = getint(&p)) != '$') {
        printf("getint: %d\n", p);
    }
    return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn) {
    int c, sign;

    printf("pn: %x, *pn: %d\n", pn, *pn);
    while(isspace(c = getch()));

    if(!isdigit(c) && c != '$' && c!= '+' && c != '-') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-')? -1: 1;
    if (c == '-' || c == '+') c = getch();

    for(*pn=0; isdigit(c); c = getch()) {
        *pn = 10 * (*pn) + (c - '0');
    }
    *pn = *pn * sign;
    if (c != '$') ungetch(c);

    printf("pn value: %d\n", *pn);
    return c;
}

/* getch: get a (possibly pushed back) character */
int getch(void) {
    return (bufp > 0) ? buf[--bufp]: getchar();
}

/* ungetch: push characters back into the input */
void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("error ungetch: too many characters!\n");
    } else {
        buf[bufp++] = c;
    }
}
