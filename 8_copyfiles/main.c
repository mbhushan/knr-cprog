#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

#define PERMS 0666

void error(char *, ...);

/* cp: copy f1 to f2 */
int main(int argc, char *argv[]) {
    int f1, f2, n;
    char buf[BUFSIZ];

    if (argc != 3) {
        error("Usage: cp from to");
    }
    if ((f1 = open(argv[1], O_RDONLY, 0)) == -1) {
        error("error: cant open file %s\n", argv[1]);
    }
    if ((f2 = creat(argv[2], PERMS)) == -1) {
        error("error: cant create file %s, mode %03o\n", argv[2], PERMS);
    }

    /* all set, do copy */
    while((n = read(f1, buf, BUFSIZ)) > 0) {
        if (write(f2, buf, n) != n) {
            error("error: write error on file: %s\n", argv[2]);
        }
    }
    return 0;
}

void error(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
