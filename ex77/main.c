/*
 * Modify the pattern finding program of Chapter 5 to take its input from a set of named files or, if no files are
 * named as arguments, from the standard input. Should the file name be printed when a matching line is found?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100

void fpat(FILE *fp, char *fname, char *pattern, int except, int num);

int main(int argc, char *argv[]) {
    char pattern[MAXLINE];
    int c, except=0, num=0;
    FILE *fp;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch (c) {
                case 'x':
                    except=1;
                    break;
                case 'n':
                    num=1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc=0;
                    break;
            }
        }
    }
    if (argc >= 1)
        strcpy(pattern, *argv);
    else {
        printf("error, usage: find [-x] [-n] pattern [file ...]\n");
        exit(1);
    }

    if (argc == 1)
        fpat(stdin, "", pattern, except, num);
    else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "find cant open file %s\n", *argv);
                exit(1);
            } else {
                fpat(fp, *argv, pattern, except, num);
                fclose(fp);
            }
        }
    }
    return 0;
}

void fpat(FILE *fp, char *fname, char *pattern, int except, int num) {
    char line[MAXLINE];
    int linenum = 0;

    while (fgets(line, MAXLINE, fp) != NULL) {
        ++linenum;
        if ((strstr(line, pattern) != NULL) != except) {
            if (*fname)
                printf("%s - ", fname);
            if (num)
                printf("%d: ", linenum);
            printf("%s", line);
        }
    }
}