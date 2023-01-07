/**
 Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the
 rightmost n bits of y, leaving the other bits unchanged.
 */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

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

int setbits(int x, int p, int n, int y) {
    int mask = -1, ymask = 0;

    mask = mask << n;
    ymask = ((~mask) & y) << (p-n);
    mask = (~mask) << (p-n);

    x = (x & (~mask)) | ymask;
    return x;
}

int main() {
    int res = 0;
    res = setbits(93, 4, 3, 211);
    printf("res: %d\n", res);
    return 0;
}
