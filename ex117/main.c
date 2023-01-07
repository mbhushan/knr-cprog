#include <stdio.h>

/** Write a program to print all input lines that are longer than 80 characters. */

#define LINE_MAX_LIMIT 250
#define THRESHOLD 80

int read_line(char line[], int limit);
void copy_line(char dst[], char src[]);

int main() {
    int max_line, curr_line;
    char line[LINE_MAX_LIMIT], longest_line[LINE_MAX_LIMIT];
    curr_line = max_line = 0;

    while ((curr_line = read_line(line, LINE_MAX_LIMIT)) > 0) {
        if (curr_line > THRESHOLD) {
            printf("Threshold (%d) exceeded!\n", THRESHOLD);
            printf("%s\n", line);
        }
    }
    return 0;
}

int read_line(char line[], int limit) {
    int i, ch;

    for (i=0; i<limit && ((ch = getchar()) != '\n'); i++) line[i] = ch;

    if (i == limit) {
        while ((ch = getchar()) != '\n') line[i++] = ch;
    }
    line[i] = '\0';
    return i;
}

void copy(char dst[], char src[]) {
    int i = 0;
    while((dst[i++] = src[i++]) != '\0');
}
