/**
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array
 * indexing. Good possibilities include getline (Chapters 1 and 4), atoi, itoa, and their variants
 * (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop (Chapter 4).
 */

#include <stdio.h>
#include <ctype.h>

/* reverse: reverse a string */
void reverse(char *s);

/* itoa: convert n to characters in s: pointer version */
void itoa(int, char *);
/* readline: read a line into s, return length */
int readline(char *s, int lim);

/* atoi: convert s to integer; pointer version */
int atoi(char *s);

int main() {
    int limit = 500;
    char s[limit];
//    while (readline(s, limit) > 0) {
//        printf("%s\n", s);
//    }
//    printf("%d\n", atoi("-12345"));
//    printf("%d\n", atoi("12345"));

//    char t[] = "program in c";
//    printf("input: %s\n", t);
//    reverse(t);
//    printf("reversed: %s\n", t);

    int n = -54321;
    itoa(n, s);
    printf("itoa: %s\n",  s);
    return 0;
}

void itoa(int n, char *s) {
    int sign;
    char *t = s;
    if ((sign = n) < 0) n = -n;
    while (n > 0) {
        *s++ = n%10 + '0';
        n = n / 10;
    }
    if (sign < 0) *s++ = '-';
    *s = '\0';
    reverse(t);


}

void reverse(char *b) {
    char *e = b;
    char c;

    while(*e) e++;
    --e;
    while (b < e) {
        c = *b; *b = *e; *e = c;
        ++b;
        --e;
    }
//    printf("s: %s\n", s);
}

int atoi(char *s) {
    int n=0, sign=1;
    /* skip whitespace */
    while (isspace(*s)) s++;

    sign = (*s == '-')? -1: 1;
    if (*s == '-' || *s == '+') s++;
    while (isdigit(*s)) {
        n = n*10 + (*s - '0');
        ++s;
    }
    return sign*n;
}

int readline(char *s, int lim) {
    int c;
    char *bs = s;
    while (--lim > 0 && (c = getchar()) != '$' && c != '\n') *s++ = c;

    if (c == '\n') *s++ = '\n';
    *s = '\0';
    return s - bs;
}