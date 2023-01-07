/**
 Exercise 2-9. In a two’s complement number system, x &= (x−1) deletes the rightmost 1-bit in x.
 Explain why. Use this observation to write a faster version of bitcount.
 */

#include <stdio.h>

int bitcount(unsigned x) {
    int cnt = 0;
    while(x) {
        ++cnt;
        x &= (x-1);
    }
    return cnt;
}
int main() {
    unsigned int x = 203;
    unsigned int y = 15;
    unsigned int z = ~0U;
    unsigned int x1 = 86;
    printf("num of bits: %d\n", bitcount(x));
    printf("num of bits: %d\n", bitcount(x1));
    printf("num of bits: %d\n", bitcount(y));
    printf("num of bits: %d\n", bitcount(z));
    return 0;
}
