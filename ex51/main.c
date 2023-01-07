/**
 * Exercise 5-1. As written, getint treats a + or - not followed by a digit as a valid representation of zero.
 * Fix it to push such a character back on the input.
 */

#include <stdio.h>
#include <ctype.h>

#define MAXBUF 100

static int bufp=0;
int buf[MAXBUF];

int getint(int *iptr);
int getch(void);
void ungetch(int);

int main() {
    int p;
    int c;
    while ((c = getint(&p)) != '$') {
        printf("getint: %d\n", p);
    }
    return 0;
}

int getint(int *iptr) {
   int c, d, sign;
   sign = 1;

   /* skip the whitespace */
   while(isspace(c = getch()))
       ;
   if (!isdigit(c) && c != '$' && c != '+' && c != '-') {
       ungetch(c);
       return 0;
   }
   sign = (c == '-') ? -1 : 1;
   if (c == '+' || c == '-') {
       d = c;
       while (!isdigit(c = getch()))
           ;
       if (c == '$') ungetch(d);
   }
   for (*iptr=0; isdigit(c); c = getch()) {
       *iptr = *iptr * 10 + (c - '0');
   }
   *iptr = *iptr * sign;

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