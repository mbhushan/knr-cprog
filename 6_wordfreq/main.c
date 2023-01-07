/**
 * word frequency program
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

#define MAXWORD 100
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
char *stringdup(char *);
int getch(void);
void ungetch(int);

int main() {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != '$') {
        if (isalpha(word[0])) {
            root = addtree(root, word);
        }
    }
    treeprint(root);
    return 0;
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
/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
    if (p == NULL) {
        p = talloc();
        p->word = stringdup(w);
        p->count = 1;
        p->left = p->right = NULL;
        return p;
    }
    int cond = strcmp(w, p->word);
    if (cond == 0) {
        p->count += 1;
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
       p->right = addtree(p->right, w);
    }
    return p;
}

/* treeprint: inorder tree print */
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}
struct tnode * talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char * stringdup(char *s) {
    char *p;
    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}
