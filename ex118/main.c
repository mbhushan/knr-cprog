#include <stdio.h>

/**
 * Write a program to remove all trailing blanks and tabs from each line of input, and to delete entirely blank lines.
 */

#define MAXLINE 250

char line[MAXLINE+1];

int read_line(void);

int main() {
    int curr_line, tail, idx;
    //curr_line = idx = tail = 0;
    while ((curr_line = read_line()) > 0) {
        for (tail=curr_line-1; line[tail] == ' ' || line[tail] == '\t' || line[tail] == '\n'; --tail);
        if (tail >=0) {
            for (idx=0; idx<=tail; idx++) putchar(line[idx]);
            putchar('\0');
        }
    }
    return 0;
}

int read_line(void) {
    extern char line[];
    int ch, i;
    for (i=0; i<MAXLINE && (ch=getchar())!='\n'; i++) line[i] = ch;

    if (ch == '\n') line[i++] = ch;

    line[i] = '\0';

    return i;
}