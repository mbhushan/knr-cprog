/**
 * Exercise 4-11. Modify getop so that it doesn’t need to use ungetch. Hint: use an internal static variable.
 */

/* reverse polish calculator */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100 /* max number of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define BUFSIZE 100
#define MAXVAL 100

char buf[BUFSIZE]; /* buffer for ungetch() */
double val[MAXVAL];
int bufp = 0; /* next free position in buf */
int sp = 0;
static int lastc = 0;

int getop (char s[]);
void push(double d);
double pop(void);
int getch(void);

int main() {
    int type;
    double op2;
    char s[MAXOP];
    int i;

    while ((type = getop(s)) != '$') {
//        printf("input: %s\n", s);
//        for (i=0;i < sp; i++) {
//            printf("%lf\n",val[i]);
//        }
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) push(pop() / op2);
                else printf("error: zero division!");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

void push(double f) {
    if (sp < MAXVAL) val[sp++] = f;
    else printf("error: full stack, cant push %g\n", f);
}

double pop() {
    if (sp > 0) return val[--sp];
    else printf("error: stack empty\n");

    return 0.0;
}
int getop(char s[]) {
    int i, c;

    if (lastc == 0) c = getch();
    else {
        c = lastc;
        lastc = 0;
    }

    while ((s[0] = c) == ' ' || c == '\t') c = getch();

    s[1] = '\0';

    if (!isdigit(c) && c != '.') return c; /* not a number */
    i=0;
    if (isdigit(c)) {
        while(isdigit(s[++i] = c = getch()));
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = getch()));
    }
    s[i] = '\0';
    if (c != '$') lastc = c;

    return NUMBER;
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}