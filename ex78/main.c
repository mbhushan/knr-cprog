/*
 * Write a program to print a set of files, starting each new one on a new page, with a title and a
 * running page count for each file.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXBOT 2
#define MAXHDR 2
#define MAXLINE 100
#define MAXPAGELINE 7

void fileprint(FILE *fp, char *fname);
int heading(char *fname, int pageno);

/* print files - each one on a new page */
int main(int argc, char *argv[]) {
    FILE *fp;
    if (argc == 1) {
        fileprint(stdin, " ");
    } else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "print: cant open %s\n", *argv);
                exit(1);
            } else {
                fileprint(fp, *argv);
                fclose(fp);
            }
        }
    }
    printf("\n");
    return 0;
}

void fileprint(FILE *fp, char *fname) {
    int lineno, pageno = 0;
    char line[MAXLINE];

    lineno = heading(fname, pageno++);
    while (fgets(line, MAXLINE, fp) != NULL) {
        if (lineno == 0) {
            fprintf(stdout, "\f");
            lineno = heading(fname, pageno++);
        }
        fputs(line, stdout);
        if (++lineno > (MAXPAGELINE - MAXBOT))
            lineno = 0;
    }
    fprintf(stdout, "\f");
}

int heading(char *fname, int pageno) {
    int ln = 1;
    fprintf(stdout, "\n");
    fprintf(stdout, "%s\tpage %d\n", fname, pageno);
    while (ln++ < MAXHDR)
        fprintf(stdout, "\n");
    return ln;
}