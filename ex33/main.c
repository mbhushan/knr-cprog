/**
Ex3-3: Write a function expand(s1,s2) that expands shorthand notations like a-z in the string s1 into the equivalent
complete list abc...xyz in s2 . Allow for letters of either case and digits, and be prepared to handle cases
like a-b-c and a-z0-9 and -a-z . Arrange that a leading or trailing - is taken literally.
*/

#include <stdio.h>

#define MAXLEN 1000

void expand(char s[], char t[]);

int main() {
    char s1[] = "a-z";
    char s2[] = "a-e-i";
    char s3[] = "1-9-1";
    char t1[MAXLEN];
    char t2[MAXLEN];
    char t3[MAXLEN];

    expand(s1, t1);
    printf("%s\n", t1);

    expand(s2, t2);
    printf("%s\n", t2);

    expand(s3, t3);
    printf("%s\n", t3);
}

void expand(char s[], char t[]) {
    char c,i,j;
    i = j = 0;

    while ((c = s[i++]) != '\0') {
        if (s[i] == '-' && s[i+1] >= c) {
            i++;
            while (c < s[i]) t[j++] = c++;
        } else {
            t[j++] = c;
        }
    }
    t[j] = '\0';
}
