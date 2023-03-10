
/*
    Exercise 7-5. Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do the input and
    number conversion.
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXOP 100
#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f);
double pop(void);

int main() {
    char *c;
    char s[MAXOP], buf[MAXOP];
    double a=0.0, op2;
    char e = '\n';

    while (scanf("%s%c", s, &e) == 2) {
        if (sscanf(s, "%lf", &a) == 1)
            push(a);
        else if (sscanf(s, "%s", buf)) {
            for (c=buf; *c; c++) {
                switch (*c) {
                    case '+':
                        push(pop()+pop());
                        break;
                    case '-':
                        op2 = pop();
                        push(pop() - op2);
                        break;
                    case '*':
                        push(pop()*pop());
                        break;
                    case '/':
                        op2 = pop();
                        if (op2 != 0.0)
                            push(pop() / op2);
                        else
                            printf("error: divide by zero\n");
                    default:
                        printf("unknown command\n");
                        break;
                }
            }
            if (e == '\n')
                printf("\t%.8g\n", pop());
        }
    }
    return 0;
}

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("stack error: stack full, cant push %g\n", f);
}

double pop(void) {
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("stack error: stack empty, nothing to pop\n");
        return 0.0;
    }
}
