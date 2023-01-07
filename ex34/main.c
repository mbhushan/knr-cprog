/**
 Exercise 3-4. In a two’s complement number representation, our version of itoa does not handle the largest negative
 number, that is, the value of n equal to −(2wordsize−1). Explain why not. Modify it to print that value correctly,
 regardless of the machine on which it runs.
 */

#include <stdio.h>
#include <string.h>

#define abs(x) ((x) < 0 ? -x: x)


void reverse(char s[]) {
    int i, j, c;
    i = 0;
    j = strlen(s)-1;

    while (i < j) {
        c = s[i]; s[i] = s[j]; s[j] = c;
        ++i;
        --j;
    }
}

/* itoa: convert n characters in s - modified */
void itoa(int n, char s[]) {
    int i, sign;
    sign = n;
    i=0;
    do {
        s[i++] = abs(n%10) + '0';
    } while ((n/=10) != 0);
    if (sign < 0) s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main() {
    int n = -1234567;
    char s[100];
    itoa(n, s);
    printf("n: %d\ns: %s\n", n, s);
    return 0;
}
