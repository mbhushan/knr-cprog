/*
Exercise 4-2. Extend atof to handle scientific notation of the form
123.45e−6
 */

#include <stdio.h>
#include <ctype.h>

double atof(char s[]);

int main() {

    char s[] = "123.45e-6";
    char t[] = "-123.456E4";

    printf("input: %s, output: %lf\n", s, atof(s));
    printf("input: %s, output: %lf\n", t, atof(t));

    return 0;
}

double atof(char s[]) {
    int i=0;
    int sign = 1;
    double val, power, exp;

    val = 0;
    power = 1;
    exp = 0;

    while(isspace(s[i])) i++;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '-' || s[i] == '+') i++;

    while(isdigit(s[i])) {
        val = val*10 + (s[i] - '0');
        i++;
    }
    if (s[i] == '.') i++;

    while (isdigit(s[i])) {
        val = val * 10 + (s[i] - '0');
        power = power * 10;
        ++i;
    }

    val = sign * (val / power);

    power = 1;
    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '-' || s[i] == '+') i++;
        while (isdigit(s[i])) {
            exp = exp * 10 + (s[i] - '0');
            i++;
        }

        while (exp-- > 0) {
            power = power * 10;
        }
        if (sign > 0) val = val * power;
        else val = val / power;
    }

    return val;
}
