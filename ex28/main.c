/**
 Exercise 2-8. Write a function rightrot(x,n) that returns the value of the
 integer x rotated to the right by n bit positions.
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

unsigned int rightrot(unsigned int  x, int n) {
    while (n > 0) {
        if ((x & 1) == 1) {
            x = ((x >> 1) | ~(~0U >> 1));
            printf("i: %s\n", int2bin(x));
        }
        else x = (x >> 1);
        --n;
    }
    return x;
}

int main() {
    unsigned int x = 203;
    int n = 3;
    printf("x: %s\n", int2bin(x));
    printf("n: %s\n", int2bin(n));
    printf("x: %s\n", int2bin(rightrot(x, n)));

    int m = 0;
    int a = ~m >> 1;
    printf("a: %s\n", int2bin(a));
    int b = ~0U >> 1;
    printf("b: %s\n", int2bin(b));


    return 0;
}
