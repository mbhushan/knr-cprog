/**
Exercise 3-2. Write a function escape(s,t) that converts characters like newline and tab into visible escape
sequences like \n and \t as it copies the string t to s. Use a switch. Write a function for the other direction
as well, converting escape sequences into the real characters.
*/

#include <stdio.h>

void escape(char s[], char t[]);
void rev_escape(char s[], char t[]);
void get_line(char t[]);

int main() {
    char s[1000];
    char t[1000];

    get_line(t);
    printf("original: %s\n", t);

    escape(s, t);
    printf("escaped: %s\n", s);

    rev_escape(t, s);
    printf("rev escaped: %s\n", t);

    return 0;
}

void rev_escape(char s[], char t[]) {
    int i=0, j=0;
    int ch;

    while(t[i] != '\0') {
        switch (t[i]) {
            case '\\':
                ++i;
                switch (t[i]) {
                    case 'n':
                        s[j] = '\n';
                        break;
                    case 't':
                        s[j] = '\t';
                        break;
                    default:
                        break;
                }
                ++j;
                break;
            default:
                s[j] = t[i];
                ++j;
                break;
        }
        ++i;
    }
    s[j] = '\0';
}

void get_line(char t[]) {
    int ch, i=0;
    while ((ch = getchar()) != '$') {
        t[i++] = ch;
    }
    t[i] = '\0';
}

void escape(char s[], char t[]) {
    int i=0,j=0;

    while(t[i] != '\0') {
        switch (t[i]) {
            case '\n':
                s[j++] = '\\';
                s[j] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j] = 't';
                break;
            default:
                s[j] = t[i];
                break;
        }
        ++i;
        ++j;
    }
    s[j] = '\0';
}