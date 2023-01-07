/**
 Exercise 3-6. Write a version of itoa that accepts three arguments instead of two. The third argument is a minimum
 field width; the converted number must be padded with blanks on the left if necessary to make it wide enough.
 */

#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void itoa(int n, char s[], int w);

int main() {
    int n = -1234567;
    char s[100];
    int w = 10;

    itoa(n, s, w);
    printf("%s\n", s);
    return 0;
}

void itoa(int n, char s[], int w) {
    int i, sign;
    i = 0;
    if ((sign = n) < 0) n = -n;
    do {
        s[i++] = (n%10) + '0';
    } while ((n/=10) > 0);

    if (sign < 0) s[i++] = '-';
    while (i < w) s[i++] = ' ';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[]) {
    int i, j, c;
    i=0;
    j=strlen(s)-1;

    while(i < j) {
        c = s[i]; s[i] = s[j]; s[j] = c;
        ++i;
        --j;
    }
}