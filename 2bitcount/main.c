#include <stdio.h>

int bitcount(unsigned x) {
    int cnt;
    for(cnt = 0; x != 0; x >>= 1) {
        if (x & 1) ++cnt;
    }
    return cnt;
}
int main() {
    unsigned int x = 203;
    printf("num bits: %d\n", bitcount(x));
    return 0;
}
