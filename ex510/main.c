/**
Write the program expr , which evaluates a reverse Polish expression from the command line, where each operator or
operand is a separate argument. For example,
expr 2 3 4 + *
evaluates 2 X (3 + 4).
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define STACKSIZE 100
double stack[STACKSIZE];
int sp = 0;

void panic(const char *msg);
void push(double value);
double pop(void);
int isnumber(char *s);
int isoperand(char *s);

int main(int argc, char *argv[]) {
    int i;
    double val = 0.0;

    for (i=1; i<argc; i++) {
       if (isnumber(argv[i])) push(atof(argv[i]));
       else if (isoperand(argv[i])) {
           switch (argv[i][0]) {
               case '+':
                   push(pop() + pop());
                   break;
               case '*':
                   push(pop() * pop());
                   break;
               case '-':
                   val = pop();
                   push(pop() - val);
                   break;
               case '/':
                   val = pop();
                   if (val != 0) push(pop() / val);
                   else printf("error: div by zero!\n");
                   break;
               default:
                   printf("unknown error: %s\n", argv[i]);
                   break;
           }
       } else {
           printf("error: unknown operand %s\n", argv[i]);
       }
    }
    printf("result: %.2f\n", pop());
    return 0;
}

int isnumber(char *s) {
    char *p = s;

    if (*p == '-' || *p == '+') {
        *p++;
        if (strlen(s) == 1) return 0;
    }
    while (*p) {
        if (!isdigit(*p)) return 0;
        *p++;
    }
    return 1;
}

int isoperand(char *s) {
    char op[] = "+-*/";
    int c = s[0];
    char *p = op;
    while (*p) {
        if (c == *p) return 1;
        *p++;
    }
    return 0;
}

void push(double val) {
    if (sp == STACKSIZE) panic("stack err: stack full!\n");
    else {
        stack[sp++] = val;
    }
}

double pop(void) {
    if (sp == 0) panic("stack err: stack empty!\n");
    else {
        return stack[--sp];
    }
}

void panic(const char *msg) {
    printf("error: %s\n", msg);
}
