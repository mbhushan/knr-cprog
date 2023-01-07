#include <stdio.h>

int main() {
    int ch;
    int r = getchar() != EOF;
    printf("r: %d", r);

    while ((ch = getchar()) != EOF) {
        putchar(ch);
    }


    return 0;
}
