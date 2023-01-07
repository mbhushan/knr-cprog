/**
Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted
(i.e., 1 changed into 0 and vice versa), leaving the others unchanged.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

char * int2bin(int i)
{
    size_t bits = sizeof(int) * CHAR_BIT;

    char * str = malloc(bits + 1);
    if(!str) return NULL;
    str[bits] = 0;

    // type punning because signed shift is implementation-defined
    unsigned u = *(unsigned *)&i;
    for(; bits--; u >>= 1)
        str[bits] = u & 1 ? '1' : '0';

    return str;
}

int invert(unsigned x, int p, int n) {
    x = x ^ ((~(~0 << n)) << (p-n+1));
    return x;
}

int main() {
    unsigned int x = 203;
    int p = 4;
    int n = 3;
    printf("x: %s\n", int2bin(x));
    printf("p: %s\n", int2bin(p));
    printf("n: %s\n\n", int2bin(n));

    int z = invert(x, p, n);

    printf("z: %s\n\n", int2bin(z));

    return 0;
}
