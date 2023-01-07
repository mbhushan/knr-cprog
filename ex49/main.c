/**
 * Exercise 4-9. Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what their properties ought
 * to be if an EOF is pushed back, then implement your design.
 */

#include <stdio.h>

#define BUFSIZE 100

int buf[BUFSIZE];
int bufp;

int getch(void);
void ungetch(int c);

int main() {
    int c;

    c = getch();
    printf("getch character: %c\n", c);
    ungetch(c);

    return 0;
}

/* getch: get a (possibly pushed back) character */
int getch(void) {
    int c;

    if (bufp > 0) c = buf[--bufp];
    else c = getchar();

    return c;
}

/* ungetch: push character back onto the input */
void ungetch(int c) {
    if (bufp >= BUFSIZE) printf("error ungetch: too many characters!");
    else buf[bufp++] = c;
}