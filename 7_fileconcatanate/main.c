#include <stdio.h>

// #define EOF '$'

void filecopy(FILE *ifp, FILE *ofp);

int main(int argc, char *argv[]) {
    FILE *fp;

    if (argc == 1)
        filecopy(stdin, stdout);
    else {
        while (--argc > 0) {
            char *fname = *(++argv);
            printf("%s %s\n", argv[0], fname);
            if ((fp = fopen(fname, "r")) == NULL) {
                printf("error cat: cant open file %s\n", *argv);
                return 1;
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
        }
    }
    return 0;
}

void filecopy(FILE *ifp, FILE *ofp) {
    int c;
    while((c = getc(ifp)) != EOF)
        putc(c, ofp);
}
