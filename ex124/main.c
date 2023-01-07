#include <stdio.h>

/*
 Write a program to check a C program for rudimentary syntax errors like unbalanced parentheses, brackets and braces.
 Don't forget about quotes, both single and double, escape sequences, and comments.
 (This program is hard if you do it in full generality.)
 */

#define MAXLINE 10000
char line[MAXLINE];

int readline(void);

int main() {

    int len = 0;
    int idx = 0;
    int brace = 0, bracket = 0, parenthesis = 0;
    int s_quote = 1, d_quote = 1;

    while ((len = readline()) > 0) {
        idx = 0;
        while (idx < len) {
            if (line[idx] == '{') brace++;
            if (line[idx] == '}') brace--;
            if (line[idx] == '[') bracket++;
            if (line[idx] == ']') bracket--;
            if (line[idx] == '(') parenthesis++;
            if (line[idx] == ')') parenthesis--;
            if (line[idx] == '\'') s_quote *= -1;
            if (line[idx] == '"') d_quote *= -1;
            idx++;
        }
        if (d_quote != 1) printf("Mismatch! double quote\n");
        if (s_quote != 1) printf("Mismatch! single quote\n");
        if (parenthesis != 0) printf("Mismatch! parenthesis\n");
        if (bracket != 0) printf("Mismatch! brackets\n");
        if (brace != 0) {
            printf("Mismatch! braces: %d\n", brace);
        }
        if (d_quote == 1 && s_quote == 1 && parenthesis == 0 && bracket == 0 && brace == 0)
            printf("Syntax appears to be valid!\n");
    }
    return 0;
}

int readline(void) {
    int ch, i;
    extern char line[];

    for (i=0; i<MAXLINE-1 && (ch = getchar()) != '$'; ++i) line[i] = ch;

    line[i] = '\0';

    return i;
}
