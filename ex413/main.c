/**
 * Exercise 4-13. Write a recursive version of the function reverse(s), which reverses the string s in place.
 */

#include <stdio.h>
#include <string.h>

/* reverse: reverse a string in place recursively */
void reverse(char s[], int left, int right);
void reverse_1(char s[], int left, int right);

int main() {
    char s[] = "C programming is fun!";
    int len = strlen(s);

    printf("input: %s\n", s);
    reverse(s, 0, len-1);
    printf("reversed: %s\n", s);
    reverse(s, 0, len-1);
    printf("reversed: %s\n", s);

    return 0;
}

void reverse_1(char s[], int left, int right) {
    int tmp = 0;
    if (left < right) {
        tmp = s[left];
        s[left] = s[right];
        s[right] = tmp;
        reverse(s, left+1, right-1);
    }
}
void reverse(char s[], int left, int right) {
    int tmp = 0;
    if (left < right) {
        reverse(s, left+1, right-1);
        tmp = s[left];
        s[left] = s[right];
        s[right] = tmp;
    }
}