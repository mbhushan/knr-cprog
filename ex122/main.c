#include <stdio.h>
/******************************************************
   KnR 1-22
   --------
   Write a program that wraps very long lines of input
   into two or more shorter lines.
 */

#define FOLDLEN 40 /* max length of the line */
#define MAXBUFFER 100

int read_line(char line[], int limit);
int main() {

    int curr_len = 0;
    char line[MAXBUFFER];
    while ((curr_len = read_line(line, MAXBUFFER)) > 0) {
        if (curr_len >= FOLDLEN) {
            int last_space_pos = -1;
            int curr_line_size = 0;
            int idx = 0;
            while (idx < curr_len) {
                if (line[idx] == ' ') last_space_pos = idx;
                if (curr_line_size == FOLDLEN) {
                    line[last_space_pos] = '\n';
                    curr_line_size = 0;
                }
                ++idx;
                ++curr_line_size;
            }
        }
        printf("%s\n", line);
    }
    return 0;
}

int read_line(char line[], int limit) {
    int ch, i;
    i = 0;
    while((i < limit) && (ch = getchar()) != '\n') line[i++] = ch;

    if (i == limit) line[limit-1] = '\0';
    if (ch == '\n') line[i] = '\0';

    return i;
}
