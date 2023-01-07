/**
 * C keyword counting program
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct key {
    char * word;
    int count;
}keytab[] = {
        "auto",0,
        "break",0,
        "case",0,
        "char",0,
        "const",0,
        "continue",0,
        "default",0,
        "unsigned",0,
        "void",0,
        "volatile",0,
        "while",0
};

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0])
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getword(char *word, int lim);
int binarysearch(char *, struct key *, int);
int getch(void);
void ungetch(int);

int main() {
    int n;
    char word[MAXWORD];
    while (getword(word, MAXWORD) != '$') {
        if (isalpha(word[0])) {
            if ((n = binarysearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
        }
    }
    for (n =0; n<NKEYS; n++) {
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    }
    return 0;
}

/* binarysearch: find word in tab[0] ... tab[n-1] */
int binarysearch(char *word, struct key tab[], int n) {
   int cond;
   int low, mid, high;
   low = 0;
   high = n-1;
   while (low <= high) {
       mid = low + (high-low)/2;
       if ((cond = strcmp(word, tab[mid].word)) < 0)
           high = mid-1;
       else if (cond > 0)
           low = mid+1;
       else
           return mid;
   }
    return -1;
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != '$')
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++) {
        if (!isalpha(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}