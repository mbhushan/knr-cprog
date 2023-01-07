#include <stdio.h>

/**
 * Write a function reverse(s) that reverses the character string s.
 * Use it to write a program that reverses its input a line at a time.
 */

#define MAXLINE 80

void reverse(char str[]);
int read_line(char line[], int limit);

int main() {
    char str[] = "mani bhushan";
    printf("original: %s\n", str);
    reverse(str);
    printf("reversed: %s\n", str);

    int line_size = 0;
    char line[MAXLINE];

    while ((line_size  = read_line(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s\n", line);
    }

    return 0;
}

int read_line(char line[], int limit) {
    int ch, i;
    i = 0;
    while ((i<limit) && (ch=getchar()) != '\n') {
        line[i++] = ch;
    }

    if (i == limit) line[limit] = '\0';
    else line[i] = '\0';

    return i;
}

void reverse(char str[]) {

    printf("in rev fn: %s\n", str);
    int len, i, j;
    j = 0;

    while(str[j++] != '\0');

    j = j - 1; /* length of the string */
    i = 0;
    --j; /* last index of the string. */
    while (i<j) {
        char ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        ++i;
        --j;
    }
}
