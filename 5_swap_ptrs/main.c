#include <stdio.h>

/* swap: swap two integers using ptrs; */
void swap(int *x, int *y);

int main() {
    int x = 4;
    int y = 9;

    printf("before swap: x=%d, y=%d\n", x, y);
    swap(&x, &y);
    printf("after swap: x=%d, y=%d\n", x, y);


}


void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
