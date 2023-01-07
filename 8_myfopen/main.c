
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>

#define PERMS 0666
#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* max files open at once */

typedef struct _iobuf{
    int cnt; /* characters left */
    char *ptr; /* next char position */
    char *base; /* location of buffer */
    int flag; /* mode of file access */
    int fd; /* file descriptor */
}FILE;

extern FILE _iob[OPEN_MAX];

FILE *myfopen(char *name, char *mode);

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags {
   _READ = 01, /* file open for reading */
   _WRITE = 02, /* file open for writing */
   _UNBUF = 04, /* file is unbuffered */
   _EOF = 010, /* EOF has occurred on this file */
   _ERR = 020 /* error occurred on this file */
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0) ? (unsigned char) *(p)->ptr++: _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x): _flashbuf((x), p))
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

FILE _iob[OPEN_MAX] = {
        {0, (char *)0, (char *)0, _READ, 0},
        {0, (char *)0, (char *)0, _WRITE, 1},
        {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}
};

int main() {
    FILE *ptr;
    char c;

    ptr = myfopen("build.ninja", "r");
    if (ptr == NULL)
        write(1, "error file!", 11);

    write(1, "success!", 8);
    return 0;
}
/*_fillbuf: allocate and fill input buffer*/
int _fillbuf(FILE *fp) {
    int bufsize;

    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1: BUFSIZ;

    if (fp->base == NULL) {
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return NULL;
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

FILE * myfopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob+OPEN_MAX; fp++) {
        if ((fp->flag & (_READ | _WRITE)) == 0)
            break;
    }
    if (fp >= _iob + OPEN_MAX)
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    }
    if (fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ: _WRITE;
    return fp;
}
