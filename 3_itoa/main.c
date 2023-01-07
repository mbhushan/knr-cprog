
#include <stdio.h>
#include <string.h>

/* reverse: reverse string s in place */
void reverse(char s[]) {
    int c, i, j;

    for(i=0, j=strlen(s)-1; i<j; i++, j--) {
        c = s[i]; s[i] = s[j]; s[j] = c;
    }
}

/** itoa: convert n to characters in s */
void itoa(int n, char s[]) {
    int i, sign;

    if ((sign = n) < 0) n = -n; /* record sign and make n positive */

    i=0;
    do {
        s[i++] = n%10 + '0';
    } while ((n/=10) > 0);

    if (sign < 0) s[i++] = '-';
    s[i] = '\0';

    reverse(s);
}
int main() {
    char s[] = "-344821";
    printf("%s\n", s);

    int n = -51423;
    char t[100];

    itoa(n, t);
    printf("n: %d\n", n);
    printf("s: %s\n", t);
    return 0;
}
