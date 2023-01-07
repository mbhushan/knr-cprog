#include <stdio.h>
#include <ctype.h>

#define NUMBER '0' /* signal that a number was found */
#define BUFSIZE 100

int getch(void);
void ungetch(int);
int getop(char *s);

char buf[BUFSIZE];
int bufp = 0;

int main() {
    char s[] = "   2+3-5$";
    int c = getop(s);
    printf("%c\n", c);
    printf("getop: %s\n", s);
    return 0;
}

/* getop: get next operator or numeric operand: pointer version */
int getop(char *s) {
    int c;
    while((*s = c = getch()) == ' ' || c == '\t')
        ;
    *(++s) = '\0';
    if (!isdigit(c) && c != '.') return c;
    if (isdigit(c)) {
        while(isdigit(*++s = c = getch()))
            ;
    }
    if (c == '.') {
        while(isdigit(*++s = c = getch()))
            ;
    }
    *s = '\0';
    if (c != '$') ungetch(c);
    return NUMBER;
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) printf("ungetch: too many characters!");
    else buf[bufp++] = c;
}