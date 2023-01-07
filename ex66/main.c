/**
 * Implement a simple version of the #define processor (i.e., no arguments) suitable for use with C programs,
 * based on the routines of this section. You may also find getch and ungetch helpful.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

#define HASHSIZE 101
#define MAXLEN 1000
#define MAXWORD 100

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void printhashtab(void);
void undef(char *name);
void undefv2(char *name);
int readline(char *s, int lim);

int main() {
    char *names[] = {
            "name",
            "address",
            "phone",
            "money"
    };
    char *defn[] = {
            "james bond",
            "mansion",
            "007",
            "billionaire"
    };
    int n = 4;
    int i = 0;
    while (n > 0) {
        install(names[i], defn[i]);
        ++i;
        --n;
    }
    printhashtab();

    printf("\nundef money from hashtable\n");
    undef("money");
    printhashtab();

    printf("\nundef phone from hashtable\n");
    undefv2("phone");
    printhashtab();

    char line[MAXLEN], name[MAXWORD], definition[MAXWORD];
    int len=0, j=0;

    while ((len = readline(line, MAXLEN)) > 0) {
        char *ptr = strtok(line, " ");
        char *key, *val;
        if (ptr != NULL && !strcmp(ptr, "#define")) {
            key = strtok(NULL, " ");
            val = (ptr != NULL) ? strtok(NULL, " ") : NULL;
            install(key, val);
        }
    }
    printhashtab();
    return 0;
}

int readline(char *s, int lim) {
    int c;
    char *p = s;
    while (--lim > 0 && (c = getchar()) != '$' && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - p;

}
void undefv2(char *name) {
    unsigned hashval;
    struct nlist *prev, *np;

    prev = NULL;
    hashval = hash(name);
    for (np = hashtab[hashval]; np != NULL; np = np->next) {
        if (strcmp(name, np->name) == 0)
            break;
        prev = np;
    }

    if (np != NULL) {
        if (prev == NULL) {
            hashtab[hashval] = np->next;
        } else {
            prev->next = np->next;
        }
        free((void *) np->name);
        free((void *) np->defn);
        free((void *) np);
    }
}

/* undef: remove a name, defn from the hash table */
void undef(char *name) {
    struct nlist *np;
    struct nlist *curr;
    unsigned hashval;
    if ((np = lookup(name)) != NULL) { /* found */
        hashval = hash(np->name);
        curr = hashtab[hashval];
        if (strcmp(curr->name, np->name) == 0) {
            hashtab[hashval] = hashtab[hashval]->next;
            free((void *)curr);
        } else {
            while ((curr != NULL) && strcmp(curr->next->name, np->name) != 0) {
                curr = curr->next;
            }
            curr->next = np->next;
            free((void *)np);
        }
    }
}

/* printhashtab: print hash table */
void printhashtab(void) {
    int i=0;
    struct nlist *np;
    for (i=0; i<HASHSIZE; i++) {
        for (np = hashtab[i]; np != NULL; np=np->next) {
            printf("%s => %s\n", np->name, np->defn);
        }
    }
}

/* install: put(name, defn) in hashtab */
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *) np->defn);
    }
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

/* hash: form hash value for string s */
unsigned hash(char *s) {
    unsigned hashval;

    for (hashval=0; *s != '\0'; s++) {
        hashval = *s + (31 * hashval);
    }
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np=hashtab[hash(s)]; np != NULL; np=np->next) {
        if (strcmp(s, np->name) == 0)
            return np;
    }
    return NULL;
}


