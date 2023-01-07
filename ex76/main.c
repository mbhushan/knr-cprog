/* Write a program to compare two files, printing the first line where they differ. */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
int mygetline(char *line, int max, FILE *fp);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "comp: need two files to compare!\n");
        exit(1);
    }

    FILE *fp1 = fopen(argv[1],"r");
    FILE *fp2 = fopen(argv[2], "r");
    char line1[MAXLINE];
    char line2[MAXLINE];
    int linenum = 0;

    int len1 = mygetline(line1, MAXLINE, fp1);
    int len2 = mygetline(line2, MAXLINE, fp2);
    while(len1 && len2) {
        ++linenum;
        if (strcmp(line1, line2) != 0) {
            printf("files differ on line: %d\n", linenum);
            printf("line1: %s", line1);
            printf("line2: %s", line2);
            break;
        }
        len1 = mygetline(line1, MAXLINE, fp1);
        len2 = mygetline(line2, MAXLINE, fp2);
    }
    if (len1 == len2)
        printf("files are same!");
    fclose(fp1);
    fclose(fp2);

    exit(0);
}

int mygetline(char *line, int max, FILE *fp) {
    if (fgets(line, max, fp) == NULL)
        return 0;
    else
        return strlen(line);
}
