#include <stdio.h>

int main() {
    char ch;
    char prev_ch = '0';

    while ((ch = getchar()) != '1') {
        if (ch != ' ' || prev_ch != ' ') {
            putchar(ch);
            prev_ch = ch;
        }
    }
    return 0;
}
