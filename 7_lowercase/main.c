#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char *str = "C PROGRAMMING!";
    int len = strlen(str);
    for (int i=0; i<len; i++) {
        putchar(tolower(str[i]));
    }
    int c;
    while ((c = getchar()) != '$') {
        putchar(tolower(c));
    }
    return 0;
}
