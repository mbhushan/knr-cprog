#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void printhashtab(void);

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

    return 0;
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


