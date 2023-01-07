#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int myget(int fd, long pos, char *buf, int n);

int main(int argc, char *argv[]) {
    int fd;
    char buf[BUFSIZ];

    if (argc == 1)
        printf("no file argument specified!\n");
    else {
        if ((fd = open(*++argv, O_RDONLY)) == -1) {
            printf("error opening file: %s\n", *argv);
        } else {
            int n = myget(fd, 10, buf, 100);
            printf("read bytes: %d\n", n);
            printf("%s\n", buf);
        }
    }



    return 0;
}

int myget(int fd, long pos, char *buf, int n) {
    if (lseek(fd, pos, 0) >= 0) {
        return read(fd, buf, n);
    } else {
        return -1;
    }
}
