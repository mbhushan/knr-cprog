/**
 * Write a program that reads a C program and prints in alphabetical order each group of variable names that are
 * identical in the first 6 characters but different somewhere thereafter. Don't count words within strings and
 * comments. Make 6 a parameter that can be set from the command line.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct tnode {
    char *word;
    int match;
    struct tnode *left;
    struct tnode *right;
};

#define MAXWORD 100
#define BUFSIZE 100
#define YES 1
#define NO 0

char buf[BUFSIZE];
int bufp = 0;
struct tnode *addtree(struct tnode *, char *, int, int *);
int compare(char *, struct tnode *, int , int *);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
char *stringdup(char *);
int getch(void);
void ungetch(int);


int main(int argc, char *argv[]) {
    struct tnode *root;
    char word[MAXWORD];
    int num = 6;
    int found = NO;

//    num = (--argc && isdigit(*++argv[0])) ? atoi(argv[0]) : 6;

    root = NULL;
    while (getword(word, MAXWORD) != '$') {
        if (isalpha(word[0]) && strlen(word) >= num) {
            root = addtree(root, word, num, &found);
        }
        found = NO;
    }
    treeprint(root);
    return 0;
}

/* compare: compare words and update p->match */
int compare(char *s, struct tnode *p, int num, int *found) {
    int i =0;
    char *t = p->word;
    for (i=0; *s == *t; i++, s++, t++) {
        if (*s == '\0')
            return 0;
    }
    if (i >= num) {
        *found = YES;
        p->match = YES;
    }
    return *s - *t;
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
struct tnode *addtree(struct tnode *p, char *w, int num, int *found) {
    int cond;
    if (p == NULL) {
        p = talloc();
        p->word = stringdup(w);
        p->match = *found;
        p->left = p->right = NULL;
    } else if ((cond = compare(w, p, num, found)) < 0) {
        p->left = addtree(p->left, w, num, found);
    } else if (cond > 0){
        p->right = addtree(p->right, w, num, found);
    }
    return p;
}

/* treeprint: inorder tree print */
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        if (p->match)
            printf("%s\n", p->word);
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
