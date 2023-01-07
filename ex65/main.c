/**
 * Write a function undef that will remove a name and definition from the table maintained by lookup and install.
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
static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void printhashtab(void);
void undef(char *name);
void undefv2(char *name);

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

    return 0;
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


