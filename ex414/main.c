/**
 * Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments of type t. (Block structure will help.)
 */

#include <stdio.h>

#define swap(t, x, y) { t _z; _z = x; x = y; y = _z; }

int main() {
    int x = 3;
    int y = 7;

    printf("before swap: x=>%d, y=>%d\n", x, y);
    swap(int, x, y);
    printf("after swap: x=>%d, y=>%d\n", x, y);

    return 0;
}
