/**
 * write a program for alloc and free methods.
 */

#include <stdio.h>

#define ALLOCSIZE 10000 /* size of available space */
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free ptr */

char *alloc(int);
void afree(char *);

int main() {
    int mem[] = {100, 1000, 10000, 1000000};
    int n = 4, i=0;
    char *p = NULL;

    for (i=0; i<n; i++) {
        p = alloc(mem[i]);
        printf("allocated: %d\n", p);
        afree(p);
    }
    return 0;
}

/* alloc: return ptrs to n characters */
char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp-n;
    } else return 0;
}

/* free storage pointed to by p */
void afree(char *p) {
    if (p >= allocbuf && p < allocbuf+ALLOCSIZE) allocp = p;
}