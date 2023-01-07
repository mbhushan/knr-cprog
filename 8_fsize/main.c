#include <stdio.h>
#include <string.h>
#include "syscall.h"
#include <fcntl.h> // flags for read and write
#include <sys/types.h> // typedef
#include <sys/stat.h> // structure returned by stat
#include "dirent.h"

#define MAX_PATH 1024
#define NAME_MAX 14 // longest filename, system dependent

typedef struct {
    long ino;
    char name[NAME_MAX+1];
}Dirent;

typedef struct {
    int fd;
    Dirent d;
}DIRx;

void fsizex(char *);
int statx(char *, struct stat *);
void dirwalkx(char *, void(*fn)(char *));

/* print file sizes */
int main(int argc, char **argv) {
    if (argc == 1)
        fsizex(".");
    else {
        while (--argc > 0)
            fsizex(*++argv);
    }
    return 0;
}

/* fsizex: print the size of the file "name" */
void fsizex(char *name) {
    struct stat stbuf;
    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsizex: cant access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalkx(name, fsizex);
    printf("%81d %s\n", stbuf.st_size, name);
}

/* dirwalk: apply fcn to all files in dir */
void dirwalkx(char *dir, void(*fn)(char *)) {
    char name[MAX_PATH];
    Dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalkx: cant open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, "..") == 0)
            continue;
        if (strlen(dir) + strlen(dp->name)+2 > sizeof(name)) {
            fprintf(stderr, "dirwalkx: name %/%s too long\n", dir, dp->name);
        } else {
            sprintf(name, "%s/%s\n", dir, dp->name);
            (*fn)(name);
        }
    }
    closedir(dfd);
}