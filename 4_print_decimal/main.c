#include <stdio.h>


/* print_decimal: print n in decimal */
void print_decimal(int n);

int main() {
    int A[] = {1234, -4321, 91827364};
    int len = 3;

    while (len > 0) {
        print_decimal(A[len-1]);
        printf("\n");
        --len;
    }
    return 0;
}

void print_decimal(int n) {
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n/10) print_decimal(n/10);

    putchar(n%10 + '0');
}