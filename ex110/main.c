#include <stdio.h>

int main() {
    int ch;

    while ((ch = getchar()) != '1') {
        if (ch == '\\' || ch == '\t' || ch == '\b') {
            putchar('\\');
            if (ch == '\\') putchar('\\');
            if (ch == '\t') putchar('t');
            if (ch == '\b') putchar('b');
        } else {
            putchar(ch);
        }
    }
    return 0;
}
