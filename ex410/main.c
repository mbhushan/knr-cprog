#include <stdio.h>

/* reverse polish calculator */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100 /* max number of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100
#define MAXLINE 100

char line[MAXLINE];
double val[MAXVAL];
int sp = 0;
int idx = 0;


int getop (char s[]);
void push(double d);
double pop(void);
int readline(char line[], int limit);

int main() {
    int type;
    double op2;
    char s[MAXOP];
    int i;

    while (readline(line, MAXLINE) > 0) {
        idx = 0;
        while ((type = getop(s)) != '\0') {

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
    }
    return 0;
}

/* readline: read line into s, return length */
int readline(char line[], int lim) {
    int c, i;
    i=0;
    while (--lim > 0 && (c = getchar()) != '$' && c != '\n') line[i++] = c;

    if (c == '\n') line[i++] = '\n';

    line[i] = '\0';
    return i;
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

    while ((s[0] = c = line[idx++]) == ' ' || c == '\t') ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.') return c; /* not a number */
    i=0;
    if (isdigit(c)) {
        while(isdigit(s[++i] = c = line[idx++]));
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = line[idx++]));
    }
    s[i] = '\0';
    idx--;

    return NUMBER;
}