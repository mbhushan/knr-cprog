/**
Exercise 2-5. Write the function any(s1,s2), which returns the first location in the string s1 where any character
from the string s2 occurs, or −1 if s1 contains no characters from s2.
(The standard library function strpbrk does the same job but returns a pointer to the location.)
*/

#include <stdio.h>

int any(char s1[], char s2[]) {
    int i=0, j=0;

    for (i=0; s2[i] != '\0'; i++) {
        j = 0;
        while (s1[j] != '\0') {
            if (s1[j] == s2[i]) {
                return j;
            }
            ++j;
        }
    }
    return -1;
}
int main() {
    char s1[] = "csapp_book_is_awesome!";
    char s2[] = "pbook";
    char s3[] = "xyz";

    printf("first test: %d\n", any(s1, s2));
    printf("second test: %d\n", any(s1, s3));

    return 0;
}
