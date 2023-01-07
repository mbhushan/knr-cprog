#include <stdio.h>
#include <ctype.h>

/* atoi: convert s to integer; v2 */
int atoi(char s[]) {
    int i, n, sign;

    for(i=0; isspace(s[i]); i++); /* skip whitespace */

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') ++i; /* skip sign */

    for (n=0; isdigit(s[i]); i++) {
        n = 10 * n + (s[i] - '0');
    }
    return sign * n;
}

int main() {
    char s[] = " -3729";
    printf("string: %s\n", s);
    printf("atoi: %d\n", atoi(s));
    return 0;
}
