#include <stdio.h>
/******************************************************
"Write a program to remove all comments from a C program.
Don't forget to handle quoted strings and character
constants properly. C comments do not nest."
******************************************************/

#define MAXLINE 1000 /* max input line size */
char line[MAXLINE]; /* current input line */

int readline(void); /* read line from input */

int main() {
    int in_comment, len, in_quote, idx;

    in_comment = in_quote = idx = 0;

    while ((len = readline()) > 0) {
        printf("line size: %d\n", len);
        printf("RL: %s\n", line);
        idx = 0;
        while (idx < len) {
            if (line[idx] == '"') in_quote = 1;
            if (!in_quote) {
                if (line[idx] == '/' && line[idx+1] == '*') {
                    idx += 2;
                    in_comment = 1;
                }
                if (line[idx] == '*' && line[idx+1] == '/') {
                    idx += 2;
                    in_comment = 0;
                }
                if (in_comment == 1) {
                    idx++;
                } else {
                    putchar(line[idx++]);
                }
            } else {
                putchar(line[idx++]);
            }
        }

    }
    return 0;
}

int readline() {
    int ch, i;
    extern char line[];

    for (i=0; i<MAXLINE-1 && (ch = getchar()) != '$' && ch != '\n'; ++i) line[i] = ch;

    if (ch == '\n') {
        line[i] = ch;
        ++i;
    }
    line[i] = '\0';
//    printf("line size: %d\n", i);
//    printf("RL: %s\n", line);
    return i;
}