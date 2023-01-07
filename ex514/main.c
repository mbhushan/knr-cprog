/**
 * Modify the sort program to handle a -r flag, which indicates sorting in reverse (decreasing) order.
 * Be sure that -r works with -n.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 100
#define MAXLEN 100
#define ALLOCSIZE 10000
#define DEFAULT 3

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
static int totallines = 0;
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptrp[], int nlines);
int readsingleline(char *line, int limit);
char *alloc(int);
void tailprint(char *lineptr[], int nlines, int tail);
void qsort_func(void *lineptr[], int left, int right,
                int (*comp)(void *, void *));
void swap(void *v[], int left, int right);
int numcmp(char *s1, char *s2);
void writelines_v2(char *lineptr[], int nlines, int decr);

int main(int argc, char *argv[]) {
    int nlines = 0;
    int tail = 0;
    int numeric=1, decr=2, option=0;
    int c = 0;

    while(--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch (c) {
                case 'n':
                    option |= numeric;
                    break;
                case 'r':
                    option |= decr;
                    break;
                default:
                    printf("error: sort illegal option %c\n", c);
                    argc = 1;
                    break;
            }
        }
    }
    if (argc) printf("usage: sort -nr\n");
    else {
        if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
            if (option & numeric) {
                printf("\nnumcmp qsort:\n");
                qsort_func(lineptr, 0, nlines-1, numcmp);
            } else {
                printf("\nstrcmp qsort:\n");
                qsort_func(lineptr, 0, nlines-1, strcmp);
            }
            writelines_v2(lineptr, nlines, option & decr);
        }
    }
    return 0;
}

void writelines_v2(char *lineptr[], int nlines, int decr) {
    int i;

    if (decr) {
        for (i=nlines-1; i>=0; i--) {
            printf("%s\n", lineptr[i]);
        }
    } else {
        while(nlines-- > 0) printf("%s\n", *lineptr++);
    }
}

int numcmp(char *s1, char *s2) {
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) return -1;
    else if (v1 > v2) return 1;
    else return 0;
}

void qsort_func(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    swap(v, left, mid);
    last = left;
    for (i=left+1; i<=right; i++) {
        if ((*comp)(v[i], v[left]) < 0){
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort_func(v, left, last-1, comp);
    qsort_func(v, last+1, right, comp);
}

void swap(void *v[], int i, int j) {
    void *tmp;
    tmp = v[i]; v[i] = v[j]; v[j] = tmp;
}

void tailprint(char *lineptr[], int nlines, int tail) {
    int diff = nlines - tail;
    int i;

    printf("tail print:\n\n");
    for (i=diff; i<nlines; i++){
        printf("%s\n", lineptr[i]);
    }
}

int readlines(char *lineptr[], int maxlines) {
    int len = 0, nlines=0;
    char line[MAXLEN], *p;

    while ((len = readsingleline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) return -1;
        else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            ++totallines;
        }
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    while(nlines-- > 0) printf("%s\n", *lineptr++);
}


int readsingleline(char *line, int limit) {
    int c;
    char *beginline = line;

    while(--limit > 0 && (c = getchar()) != '$' && c != '\n') {
        *line++ = c;
    }

    if (c == '\n') *line++ = c;
    *line = '\0';

    return line - beginline;
}

char *alloc (int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else return 0;
}
