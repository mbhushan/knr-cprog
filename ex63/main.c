/**
 * Write a cross-referencer that prints a list of all words in a document, and, for each word, a list of the line
 * numbers on which it occurs. Remove noise words like "the", "and," and so on.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 10

struct tnode {
    char *word;
    struct tnode *left;
    struct tnode *right;
    unsigned lines[MAXLINES];
};

struct tnode *addtree(struct tnode *node, char *word, int line_num);
void treeprint(struct tnode * node);
char *getword(void);
int isnoiseword(char *word);

int main() {
    struct tnode *root;
    char *word;
    unsigned int line = 1;
    root = NULL;
    while ((word = getword()) != NULL) {
        if (isalpha(word[0]) && !isnoiseword(word)) {
            root = addtree(root, word, line);
        } else if (word[-1] == '\n') {
           line++;
        }
    }
    treeprint(root);
    return 0;
}

void treeprint(struct tnode *p) {
    int i;
    if (p != NULL) {
        treeprint(p->left);
        printf("%-16s", p->word);
        for (i=0; i<MAXLINES && p->lines[i]; i++) {
            printf("%s%d", i==0 ? "": ", ", p->lines[i]);
        }
        putchar('\n');
        treeprint(p->right);
    }
}

struct tnode *addtree(struct tnode *p, char *word, int line_num) {
    int cond, i;

    if (p == NULL) {
        p = (struct tnode *) malloc(sizeof(struct tnode));
        p->word = strdup(word);
        p->lines[0] = line_num;
        for(i=1; i<MAXLINES; i++)
            p->lines[i] = 0;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(word, p->word)) == 0) {
        i=0;
        while (p->lines[i] != 0 && i < MAXLINES)
            ++i;
        p->lines[i] = line_num;
    } else if (cond < 0) {
        p->left = addtree(p->left, word, line_num);
    } else {
        p->right = addtree(p->right, word, line_num);
    }
    return p;
}

int isnoiseword(char *word) {
    if (word == NULL || strlen(word) <=2)
        return 1;
    static char *nw[] = {
            "a",
            "an",
            "and",
            "are",
            "for",
            "from",
            "in",
            "is",
            "it",
            "not",
            "of",
            "on",
            "or",
            "that",
            "the",
            "this",
            "to",
            "was",
            "with",
    };

    int cond;
    int low, high, mid;
    low = 0;
    high = (sizeof(nw) / sizeof (nw[0])) - 1;
    while (low <= high) {
        mid = low + (high-low) / 2;
        if ((cond = strcmp(word, nw[mid])) < 0)
            high = mid-1;
        else if (cond > 0)
            low = mid+1;
        else
            return 1;
    }
    return 0;
}

char * getword(void) {
    static char word[100];
    int c, lim=100;
    char *w = word;

    while(isspace(c = getchar()) && c != '\n')
        ;
    if (c != '$') {
        *w++ = tolower(c);
    }
    if (isalpha(c)) {
        for (; --lim > 1; w++) {
            if (!isalpha(*w = tolower(getchar())) && *w != '_')
                break;
        }
    }
    *w = '\0';

    return c == '$' ? NULL: word;
}
