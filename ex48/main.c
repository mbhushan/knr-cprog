/**
 * Exercise 4-8. Suppose that there will never be more than one character of pushback. Modify getch and
 * ungetch accordingly.
 */

#include <stdio.h>

char buf = 0;

int getch(void);
void ungetch(int c);

int main() {
    int c;

    c = getch();
    printf("getch call: %c\n", c);
    ungetch(c);
    printf("ungetch called successfully!\n");

    return 0;
}

/* getch: get a (possibly pushed back) character */
int getch(void) {
    int c;

    if (buf != 0) c = buf;
    else c = getchar();

    buf = 0;
    return c;
}

/* ungetch: push character back onto the input */
void ungetch(int c) {
    if (buf != 0) printf("error: too many characters\n");
    else buf = c;
}
