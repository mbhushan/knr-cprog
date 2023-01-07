/* atof: convert string to double */

#include <stdio.h>
#include <ctype.h>

double atof(char s[]);
int readline(char s[], int limit);

int main() {
    char a[] = "-98.2134";
    int maxline = 100;
    char s[maxline];
    double sum = 0.0;

    printf("input: %s\n", a);
    printf("output: %.4f\n", atof(a));

    /* rudimentary calculator */
    while (readline(s, maxline) > 0) {
        sum += atof(s);
        printf("running sum: %.2f\n", sum);
    }

    return 0;
}

int readline(char s[], int lim) {
    int i=0, ch;

    while (lim-- > 0 && (ch = getchar()) != '$' && ch != '\n') {
        s[i++] = ch;
    }
    if (ch == '\n') s[i++] = '\n';

    s[i] = '\0';

    return i;
}

double atof(char s[]) {
    int i=0;
    int sign = 1;
    double val = 0, power = 1;

    while (isspace(s[i])) ++i;

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '-' || s[i] == '+') ++i;

    while (s[i] != '\0' && isdigit(s[i])) {
        val = val*10 + (s[i] - '0');
        ++i;
    }
    if (s[i] == '.') ++i;

    while (s[i] != '\0' && isdigit(s[i])) {
        val = val*10 + (s[i] - '0');
        power = power * 10;
        ++i;
    }

    printf("sign: %d, val: %.1f, pow: %.1f\n", sign, val, power);

    return sign * val / power;
}
