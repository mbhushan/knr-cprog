#include <stdio.h>

#define MAXLINE 20 /* max input line size */

int readline(char line[], int line_limit);
void copy(char dst[], char src[]);

int main() {

    int curr_len, max_len;
    char line[MAXLINE];
    char longest_line[MAXLINE];

    max_len = 0;

    while ((curr_len = readline(line, MAXLINE)) > 0) {
        if (curr_len > max_len) {
            max_len = curr_len;
            copy(longest_line, line);
        }
    }
    if (max_len > 0) {
        if (max_len > MAXLINE) {
            printf("\n\nStorage limit exceeded by: %d", max_len - MAXLINE);
            printf("\nline length: %d", max_len);
            printf("longest line: %s", longest_line);
        } else {
            printf("longest line: %s", longest_line);
        }
    }


    return 0;
}

/** read line into line and return its len */
int readline(char line[], int line_limit) {
    int ch, i;
   // printf("line limit: %d\n", line_limit);
    for (i=0; i<line_limit && (ch=getchar())!='\t' && ch!='\n'; ++i) line[i] = ch;

    if (i == line_limit) {
        while ((ch = getchar()) != '\n') ++i;
    }

    if (ch == '\n') {
        line[ch] = '\n';
        ++i;
    }
    line[i] = '\0';
   // printf("line [%d]: %s", i, line);

    return i;
}

/** copy line src to dst */
void copy(char dst[], char src[]) {
    int i = 0;

    while((dst[i] = src[i]) != '\0') ++i;
}
