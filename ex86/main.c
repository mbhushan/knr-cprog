/**
 * Exercise 8.6. The standard library function calloc(n, size) returns a pointer to n objects
		  of size size, with the storage initialised to zero. Write calloc, by calling
		  malloc or by modifying it.
 */
#include <stdio.h>
#include <malloc.h>
#include "syscall.h"

void * callocx(unsigned n, unsigned size) {
    unsigned i, nb;
    char *p, *q;

    nb = n * size;
    if ((p = q = malloc(nb)) != NULL) {
        for (i=0; i<nb; i++) {
            *(p++) = 0;
        }
    }
    return q;
}
int main() {
    int *iptr = callocx(10, 4);
    for (int i=0; i<10; i++) {
        printf("%d\n", *iptr++);
    }
    return 0;
}
