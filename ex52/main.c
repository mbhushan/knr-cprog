/**
 * Exercise 5-2. Write getfloat, the floating-point analog of getint. What type does getfloat return as
 * its function value?
 */

#include <stdio.h>
#include <ctype.h>

#define MAXBUF 100

int getch(void);
void ungetch(int);
int getfloat(float *fp);

static int bufp = 0;
int buf[MAXBUF];

int main() {
    float f = 0.0;
    while(getfloat(&f) != '$') {
        printf("float: %f\n", f);
    }
    return 0;
}

/* getfloat: get next floating-point number from the input */
int getfloat(float *fp) {
    int c, sign=1;
    float power;

    /* skip the whitespace */
    while(isspace(c = getch()))
        ;
    /* get the sign */
    sign = (c == '-') ? -1 : 1;
    if (c == '-' || c == '+') c = getch();

    /* get the numbers */
    for (*fp = 0.0; isdigit(c); c=getch()) {
        *fp = *fp * 10 + (c - '0'); /* get integer part */
    }
    if (c == '.') c = getch();

    for(power=1.0; isdigit(c); c=getch()) {
        *fp = *fp * 10 + (c - '0'); /* get frational part */
        power = power * 10.0;
    }

    *fp = sign * (*fp)/power;

    if (c != '$') ungetch(c);
    return c;
}

int getch(void) {
    int c;
    if (bufp > 0) c = buf[--bufp];
    else c = getchar();
    return c;
}

void ungetch(int c) {
    if (bufp >= MAXBUF) printf("error ungetch: too many characters in the buffer!");
    else buf[bufp++] = c;
}
