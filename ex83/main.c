/* Design and write _flushbuf , fflush , and fclose . */

#include <stdio.h>
#include <malloc.h>
#include "syscall.h"

/* fflush */
int fflush(FILE *f)
{
    int retval;
    int i;

    retval = 0;
    if (f == NULL) {
        /* flush all output streams */
        for (i = 0; i < OPEN_MAX; i++) {
            if ((_iob[i]->flag & _WRITE) && (fflush(_iob[i]) == -1))
                retval = -1;
        }
    } else {
        if ((f->flag & _WRITE) == 0)
            return -1;
        _flushbuf(EOF, f);
        if (f->flag & _ERR)
            retval = -1;
    }
    return retval;
}

/* fclose */
int fclose(FILE *f)
{
    int fd;

    if (f == NULL)
        return -1;
    fd = f->fd;
    fflush(f);
    f->cnt = 0;
    f->ptr = NULL;
    if (f->base != NULL)
        free(f->base);
    f->base = NULL;
    f->flag = 0;
    f->fd = -1;
    return close(fd);
}

int _flushbuf(int c, FILE *f)
{
    int num_written, bufsize;
    unsigned char uc = c;

    if ((f->flag & (_WRITE|_EOF|_ERR)) != _WRITE)
        return EOF;
    if (f->base == NULL && ((f->flag & _UNBUF) == 0)) {
        /* no buffer yet */
        if ((f->base = malloc(BUFSIZ)) == NULL)
            /* couldn't allocate a buffer, so try unbuffered */
            f->flag |= _UNBUF;
        else {
            f->ptr = f->base;
            f->cnt = BUFSIZ - 1;
        }
    }
    if (f->flag & _UNBUF) {
        /* unbuffered write */
        f->ptr = f->base = NULL;
        f->cnt = 0;
        if (c == EOF)
            return EOF;
        num_written = write(f->fd, &uc, 1);
        bufsize = 1;
    } else {
        /* buffered write */
        if (c != EOF)
            f->ptr++ = uc;
        bufsize = (int)(f->ptr - f->base);
        num_written = write(f->fd, fp->base, bufsize);
        f->ptr = f->base;
        f->cnt = BUFSIZ - 1;
    }
    if (num_written == bufsize)
        return c;
    else {
        f->flag |= _ERR;
        return EOF;
    }
}