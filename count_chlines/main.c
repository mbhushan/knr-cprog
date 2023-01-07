#include <stdio.h>

int main() {
    int nc, nl, ch;

    for (nc=0; (ch = getchar()) != '1'; ++nc) {
        if (ch == '\n') ++nl;
    }
    printf("total chars: %d\n", nc);
    printf("total lines: %d\n", nl);
    printf("value of EOF is: %d\n", EOF);

    return 0;
}
