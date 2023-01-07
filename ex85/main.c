/**
 * Modify the fsize program to print the other information contained in the inode entry.
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "sys/types.h"
#include "sys/stat.h"
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>

#define MAX_PATH 1024

#ifndef DIRSIZ
#define DIRSIZ 14
#endif

void dirwalk(char *dir, void (*fcn)(char *));
void fsize(char *name);

int main(int argc, char *argv[]) {
    if (argc == 1) fsize(".");
    else {
        while (--argc > 0) fsize(*++argv);
    }
    return 0;
}
void dirwalk(char *dir, void (*fcn)(char *)) {
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        puts("Error: cant open directory!\n");
        return;
    }
    puts(dir);
    // get each dir entry
    while((dp = readdir(dfd)) != NULL) {
        // skip . and .. is redundant
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) continue;
        if (strlen(dir) + strlen(dp->d_name)+2 > sizeof (name)) puts("Error: name too long!");
        else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

void fsize(char *name) {
    struct stat stbuf;
    if (stat(name, &stbuf) == -1) {
        puts("Error: cant get file stats!\n");
        return;
    }

    if ((stbuf.st_mode & S_IFMT) == S_IFDIR) dirwalk(name, fsize);
    struct passwd *pwd = getpwuid(stbuf.st_uid);
    //print file name, size and owner
    printf("%81ld %s owner: %s\n", (int)stbuf.st_size, name, pwd->pw_name);
}
