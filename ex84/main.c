/**
 * The standard library function
 int fseek(FILE *fp, long offset, int origin)
 is identical to lseek except that fp is a file pointer instead of a file descriptor and the return value is an
 int status, not a position. Write fseek . Make sure that your fseek coordinates properly with the buffering done
 for the other functions of the library.
 https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_8:Exercise_4
 */
#include <stdio.h>
#include <unistd.h>

int fseekx(FILE *f, long offset, int whence) {
    if ((f->_flags & _UNBUF) == 0 && base != NULL) {
        if (f->flag & _WRITE)
            fflush(f);
        else if (f->flag & _READ) {
            f->cnt = 0;
            f->ptr = f->base;
        }

    }
    return (lseek(f->fd, offset, whence) < 0);
}