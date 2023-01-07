#include <stdio.h>

/* squeeze:  delete all c from s */
void squeeze(char s[], int c) {
    int i,j;
    for (i=j=0; s[i] != '\0'; i++) {
        if (s[i] != c) s[j++] = s[i];
    }
    s[j] = '\0';
}

void strcat(char s[], char t[]) {
    int i=0, j=0;

    while(s[i++] != '\0');
    --i;
    while((s[i++] = t[j++]) != '\0');
}

int main() {
    char s[] = "mani bhushan";
    char c = 'a';
    printf("input string: %s\n", s);
    squeeze(s, c);
    printf("post squeeze: %s\n", s);
    char x[] = "shreyansh";
    char y[] = "vedansh";
    strcat(x, y);
    printf("post concat: %s\n", x);
    return 0;
}
