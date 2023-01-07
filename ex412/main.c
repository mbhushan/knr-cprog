/**
 * Exercise 4-12. Adapt the ideas of printd to write a recursive version of itoa; that is, convert an integer into
 * a string by calling a recursive routine.
 */

#include <stdio.h>
#include <stdlib.h>

#define LIMIT 100

/* itoa: convert n to characters in s: recursive */
void itoa(int n, char s[]);

int main() {
    int A[] = {-12345, 54321, -9182};
    int len = 3;
    int i=0;
    char s[LIMIT];

    for (i=0; i<len; i++) {
        itoa(A[i], s);
        printf("itoa on %d: %s\n", A[i], s);
        s[0] = '\0';
    }
    return 0;
}

void itoa(int n, char s[]) {
    static int i;
    if (n/10) itoa(n/10, s);
    else {
        i=0;
        if (n < 0) s[i++] = '-';
    }
    s[i++] = abs(n)%10 + '0';
    s[i] = '\0';
}