#include <stdio.h>

/**
 * write a program to count blanks, tabs, and newlines.
 * @return
 */

int main() {
    int ch;
    int ns, nt, nl;
    ns = nt = nl = 0;

    while ((ch=getchar()) != '1') {
        if (ch == ' ') ++ns;
        if (ch == '\t') ++nt;
        if (ch == '\n') ++nl;
    }
    printf("==========================\n");
    printf("total spaces: %d\n", ns);
    printf("total tabs: %d\n", nt);
    printf("total lines: %d\n", nl);
    return 0;
}
