/**
 * C keyword counting program - pointer version
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
struct key *binarysearch(char *, struct key *, int);
struct key *binarysearchv2(char *, struct key *, int);
int getch(void);
void ungetch(int);

int main() {
    int n;
    char word[MAXWORD];
    struct key *p;

    while (getword(word, MAXWORD) != '$') {
        if (isalpha(word[0])) {
            if ((p = binarysearchv2(word, keytab, NKEYS)) != NULL)
                p->count++;
        }
    }
    for (p=keytab; p<keytab+NKEYS; p++) {
        printf("%4d %s\n", p->count, p->word);
    }
    return 0;
}

/* binarysearch: find word in tab[0] ... tab[n-1] */
struct key * binarysearch(char *word, struct key *tab, int n) {
    int cond;
    struct key *low = &tab[0];
    struct key *high = &tab[n];
    struct key *mid;

    while (low < high) {
        mid = low + (high-low)/2;
        if ((cond = strcmp(word, mid->word)) < 0)
            high = mid;
        else if (cond > 0)
            low = mid+1;
        else
            return mid;
    }
    return NULL;
}

/* binarysearch: find word in tab[0] ... tab[n-1] */
struct key * binarysearchv2(char *word, struct key *tab, int n) {
    int cond;
    struct key *low = &tab[0];
    struct key *high = &tab[n-1];
    struct key *mid;

    while (low <= high) {
        mid = low + (high-low)/2;
        if ((cond = strcmp(word, mid->word)) < 0)
            high = mid-1;
        else if (cond > 0)
            low = mid+1;
        else
            return mid;
    }
    return NULL;
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
