#include <stdio.h>
#include <unistd.h>

int getchar_unbuf(void);
int getchar_buf(void);

int main() {
    printf("unbuffered getchar: %c\n", getchar_unbuf());

    int c;
    printf("buffered getchar demo: \n");
    while ((c = getchar_buf()) != EOF) {
        putchar(c);
    }
    return 0;
}

int getchar_buf(void) {
    static char buf[BUFSIZ];
    static char *bufp = buf;
    static int n = 0;

    if (n == 0) {
        n = read(0, buf, sizeof(buf));
        bufp = buf;
    }
    return (--n > 0) ? (unsigned char) *bufp++: EOF;
}

int getchar_unbuf(void) {
    char c;
    return (read(0, &c, 1) == 1) ? (unsigned char)c: EOF;
}