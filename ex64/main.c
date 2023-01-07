/**
 * Write a program that prints the distinct words in its input sorted into decreasing order of frequency of
 * occurrence. Precede each word by its count.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

#define MAXWORDS 100
#define BUFSIZE 100
#define MAXSUPWORDS 1000

struct tnode *addtree(struct tnode *, char *);
void arrayprint(void);
int getword(char *, int);
struct tnode *talloc(void);
char *mystrdup(char *);
int getch(void);
void ungetch(int);
void qsortd(struct tnode *v[], int left, int right);
void swap(struct tnode *v[], int i, int j);

char buf[BUFSIZE];
int bufp;
struct tnode *treenodes[MAXSUPWORDS] = {0};
int treep = 0;

int main() {
    struct tnode *root;
    char word[MAXWORDS];
    root = NULL;

    while (getword(word, MAXWORDS) != '$') {
        if (isalpha(word[0]) || word[0] == '_')
            root = addtree(root, word);
    }
    qsortd(treenodes, 0, treep-1);
    arrayprint();
    return 0;
}

struct tnode *addtree(struct tnode *p, char *w) {
    int result;
    if (p == NULL) {
        p = talloc();
        p->word = mystrdup(w);
        p->count = 1;
        p->left = p->right = NULL;
        treenodes[treep++]=p;
    } else if ((result = strcmp(w, p->word)) == 0) {
        p->count++;
    } else if (result < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}

void arrayprint(void) {
    int i;
    for (i=0; i<treep; i++) {
        printf("%4d %s\n", treenodes[i]->count, treenodes[i]->word);
    }
}

struct tnode *talloc(void) {
    return (struct tnode *)malloc(sizeof(struct tnode));
}

char *mystrdup(char *s) {
    char *p = (char *)malloc(strlen(s)+1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

int getword(char *word, int lim) {
    int c;
    char *w = word;
    while ((c = tolower(getch())) == '\t' || c == ' ')
        ;
    if (c != '$')
        *w++ = c;
    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }
    for(; --lim > 0; w++) {
        if (!isalnum(*w = tolower(getch())) && *w != '_'){
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

void qsortd(struct tnode *v[], int left, int right) {
    int i, last;
    if (left >= right)
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for(i=left+1; i<=right; i++) {
        if (v[i]->count > v[left]->count)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    qsortd(v, left, last-1);
    qsortd(v, last+1, right);
}

void swap(struct tnode *v[], int i, int j) {
    struct tnode *tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

int getch(void) {
    return (bufp>0) ? buf[--bufp]: getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("error ungetch: too many characters!");
    else
        buf[bufp++] = c;
}