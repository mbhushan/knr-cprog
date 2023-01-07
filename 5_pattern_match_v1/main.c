#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int readline(char *line, int lim);

int main(int argc, char *argv[]) {
    char line[MAXLINE];
    int found = 0;

    if (argc != 2) {
        printf("usage: find pattern\n");
    } else {
        while (readline(line, MAXLINE) > 0) {
            if (strstr(line, argv[1]) != NULL) {
                printf("\n%s", line);
                found++;
            }
        }
    }
    printf("number of occurances: %d\n", found);
    return 0;
}

int readline(char *line, int lim) {
    char c;
    char *b = line;

    while (--lim > 0 && (c = getchar()) != '$' && c != '\n') *line++ = c;

    if (c == '\n') *line++ = '\n';

    *line = '\0';

    return line - b;

}
