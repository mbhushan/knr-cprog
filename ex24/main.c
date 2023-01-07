/*
 Exercise 2-4. Write an alternate version of squeeze(s1,s2) that deletes each character
 in s1 that matches any character in the string s2.
 */

#include <stdio.h>

int in_string(char s[], int ch) {
    int i=0;
    while (s[i] != '\0') {
        if (s[i] == ch) return 1;
        ++i;
    }
    return 0;
}

void squeeze(char s1[], char s2[]) {
    int i=0, j=0;
    for(i=0; s1[i] != '\0'; i++) {
        if (!in_string(s2, s1[i])) s1[j++] = s1[i];
    }
    s1[j] = '\0';
}

int main() {
    char name[] = "manibhushanoea";
    char vowels[] = "aeiou";

    printf("s1: %s\ns2: %s\n\n", name, vowels);
    squeeze(name, vowels);
    printf("s1: %s\ns2: %s\n", name, vowels);
    return 0;
}
