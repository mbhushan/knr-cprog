#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int readline(char *s, int limit);

int main(int argc, char *argv[]) {
    char line[MAXLINE];
    int lineno = 0;
    int c, except = 0, num=0, found=0;

    while (--argc > 0 && *(++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    num = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
        }
    }
    if (argc != 1) printf("usage: find -x -n pattern\n");
    else {
        while (readline(line, MAXLINE) > 0) {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except) {
                if (num) printf("%ld:", lineno);
                printf("%s", line);
                found++;
            }
        }
    }
    printf("total occurance: %d\n", found);
    return 0;
}

int readline(char *line, int limit) {
    char *begin = line;
    char c;
    while(--limit > 0 && (c = getchar()) != '$' && c != '\n') *line++ = c;
    if (c == '\n') *line++ = c;
    *line = '\0';
    return line - begin;
}