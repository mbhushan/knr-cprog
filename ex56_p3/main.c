#include <stdio.h>
#include <ctype.h>

/* atof: convert string s to double: pointer version */
double atof(char *s);

int main() {
    char s[] = "-123.456";
    printf("atof: %.3f\n", atof(s));
    return 0;
}

double atof(char *s) {
    double val, power = 1.0;
    int sign = 1;
    while (isspace(*s)) s++;

    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-') s++;

    while(isdigit(*s)) {
        val = val*10 + (*s - '0');
        s++;
    }
    if (*s == '.') s++;
    while(isdigit(*s)) {
        val = val*10 + (*s - '0');
        power = power * 10;
        s++;
    }

    return sign * val / power;
}