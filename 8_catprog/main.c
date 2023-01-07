/*
 * Rewrite the program cat from Chapter 7 using read , write , open and close
 * instead of their standard library equivalents. Perform experiments to determine the relative
 * speeds of the two versions.
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


void filecopy(int ifd, int ofd);

/* cat: concatanate files - read, write, open, close */
int main(int argc, char *argv[]) {
    int fd;

    if (argc == 1) {
        filecopy(0, 1);
    } else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY)) == -1) {
                printf("file open error: cant open %s file\n", *argv);
            } else {
                filecopy(fd, 1);
                close(fd);
            }
        }
    }
    return 0;
}

void filecopy(int ifd, int ofd) {
    int n;
    char buf[BUFSIZ];

    while((n = read(ifd, buf, BUFSIZ)) > 0) {
        if (write(ofd, buf, n) != n) {
            printf("cat error: write error!\n");
        }
    }
}
