/**
 * Exercise 4-7. Write a routine ungets(s) that will push back an entire string onto the input. Should ungets know
 * about buf and bufp, or should it just use ungetch?
 */

/* reverse polish calculator */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>


#define MAXOP 100 /* max number of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define NAME 'n' /* signal that a name was found */

#define BUFSIZE 100
#define MAXVAL 100

char buf[BUFSIZE]; /* buffer for ungetch() */
double val[MAXVAL];
int bufp = 0; /* next free position in buf */
int sp = 0;

int getop (char s[]);
void push(double d);
double pop(void);
int getch(void);
void ungetch(int);
void clear(void);
void mathfunc(char s[]);
void ungets(char s[]);

int main() {
    int type, i, var=0;
    double op1, op2, v, variable[26];
    char s[MAXOP];

    for (i=0; i<26; i++) {
        variable[i] = 0.0;
    }

    while ((type = getop(s)) != '$') {
//        printf("input: %s\n", s);
//        for (i=0;i < sp; i++) {
//            printf("%lf\n",val[i]);
//        }
        switch (type) {
            case NAME:
                mathfunc(s);
                break;
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
            case '%':
                op2 = pop();
                if (op2 != 0.0) push(fmod(pop(),op2));
                else printf("error: zero divisor!");
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) push(pop() / op2);
                else printf("error: zero division!");
                break;
            case '?': /* print top element of the stack */
                op2 = pop();
                printf("\tstack top: %.8g\n", op2);
                push(op2);
                break;
            case 'c': /* clear the stack */
                clear();
                break;
            case 'd': /* duplicate the top lement of the stack */
                op2 = pop();
                push(op2);
                push(op2);
                break;
            case 's': /* swap the top two element */
                op1 = pop();
                op2 = pop();
                push(op1);
                push(op2);
                break;
            case '=':
                pop();
                if (var >= 'A' && var <= 'Z') variable[var - 'A'] = pop();
                else printf("error: no variable name\n");
                push(variable[var - 'A']);
                break;
            case '\n':
                v = pop();
                printf("\t%.8g\n", v);
                push(v);
                break;
            default:
                if (type >= 'A' && type <= 'Z') push(variable[type - 'A']);
                else if (type == 'v') push(v);
                //else printf("error: unknown command %s\n", s);
                break;
        }
        var = type;
    }
    return 0;
}

/* matchfunc: check string s for supported math functions */
void mathfunc(char s[]){
    double op2;
    if (strcmp(s, "sin") == 0) push(sin(pop()));
    else if (strcmp(s, "cos") == 0) push(cos(pop()));
    else if (strcmp(s, "exp") == 0) push(exp(pop()));
    else if (strcmp(s, "pow") == 0) {
        op2 = pop();
        push(pow(pop(), op2));
    } else {
        printf("error: %s is not supported\n", s);
    }
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

void clear(void) {
    sp = 0;
}

int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t') ;
    s[1] = '\0';

    i = 0;

    if (islower(c)) {
        while (islower(s[++i] = c = getch())) ;
        s[i] = '\0';
        if (c != '$') ungetch(c);
        if (strlen(s) > 1) return NAME;
        else {
            return c; /* it may be command */
        }
    }

    if (!isdigit(c) && c != '.' && c != '-') return c; /* not a number */

    if (c == '-') {
        if (isdigit(c = getch()) || c == '.') {
            s[++i] = c;
        } else {
            if (c != '$') ungetch(c);
            return '-';
        }
    }
    if (isdigit(c)) {
        while(isdigit(s[++i] = c = getch()));
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = getch()));
    }
    s[i] = '\0';
    if (c != '$') ungetch(c);

    return NUMBER;
}

/* ungets: push string back onto input */
void ungets(char s[]) {
    int len = strlen(s);
    while (len > 0) ungetch(s[--len]);
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int ch) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters!\n");
    } else {
        buf[bufp++] = ch;
    }
}


