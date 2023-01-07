/*
 Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into a base b character representation in the
 string s. In particular, itob(n,s,16) formats n as a hexadecimal integer in s.
 */

#include <stdio.h>
#include <string.h>

/* reverse: reverse a string */
void reverse(char s[]) {
    int i=0;
    int j = strlen(s)-1;
    char c;

    while(i < j) {
        c = s[i]; s[i] = s[j]; s[j] = c;
        ++i;--j;
    }
}

/* itob: convert n to characters in s - base b */
void itob(int n, char s[], int b) {
    int i, j, sign;
    if ((sign = n) < 0) n = -n;
    i=0;
    do {
        j = n%b;
        s[i++] = (j <= 9) ? j+'0' : 'a' + (j-10);
    } while ((n/=b) > 0);

    if (sign < 0) s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main() {
    int A[] = {590, 100, 188, 921, 256, 1128, -200, -48, -12, -3};
    int i = 0;
    char s[100];
    int b = 16;
    for(i=0; i<10; i++) {
        itob(A[i], s, b);
        printf("%d to hex: %s\n", A[i], s);
    }

    return 0;
}
