/*
Exercise 2-2. Write a loop equivalent to the for loop above without using && or ¦¦.
for(i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
s[i] = c;
 */

#define MAX_LINE_LENGTH 1000
#include <stdio.h>

int main() {
    int i=0, lim = MAX_LINE_LENGTH, ch=0;
    char line[MAX_LINE_LENGTH];

    while (i < (lim-1)) {
        ch = getchar();
        if (ch == '$') break;
        if (ch == '\n') break;

        line[i++] = ch;
    }

    line[i] = '\0';
    return 0;
}
