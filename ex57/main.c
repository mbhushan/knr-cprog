#include <stdio.h>
#include <string.h>

#define MAXLINES 500
#define MAXLEN 50
#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char * allocp = allocbuf;
// char *lineptr[MAXLEN];

int readlines(char *lineptr[], int nlines);
int readlines_v2(char lines[][MAXLEN], int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
char *alloc(int);
int readline(char *, int);
void swap(char *v[], int, int);

int main() {
    int nlines;
    char lines[MAXLINES][MAXLEN];
    char *lineptr[MAXLEN];
    if ((nlines = readlines_v2(lines, MAXLINES)) >= 0) {
      //  qsort(lines[MAXLINES], 0, nlines-1);
        writelines(lines[MAXLINES], nlines);
    } else {
        printf("error: input too big to sort\n");
    }
    return 0;
}

void qsort(char *v[], int left, int right) {
    int i, last;
    if (left >= right) return;
    int mid = left + (right - left)/2;
    swap(v, left, mid);
    last = left;
    for (i=left+1; i<=right; i++) {
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

void swap(char *v[], int i, int j) {
    char *tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}

//void writelines(char *lineptr[], int nlines) {
//    int idx = 0;
//    while (idx < nlines){
//       printf("%s\n", lineptr[idx++]);
//    }
//}

int readlines_v2(char lines[MAXLINES][MAXLEN], int maxlines) {
    int len, nlines=0;
    while ((len = readline(lines[nlines], MAXLEN)) > 0) {
        if (nlines >= maxlines || len > MAXLEN) return -1;
        else {
            lines[nlines++][len-1] = '\0';
        }
    }
    return nlines;
}

int readlines(char *lineptr[], int maxlines) {
    int len, lineidx = 0;
    char *p, line[MAXLEN];

    while((len = readline(line, MAXLEN)) > 0) {
        if (lineidx >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[lineidx++] = p;
        }
    }
    return lineidx;
}

int readline(char *s, int lim) {
    int c, len;
    char *t = s;
    while (--lim > 0 && (c = getchar()) != '$' && c != '\n') *s++ = c;
    if (c == '\n') *s++ = c;
    *s = '\0';
    len = s - t;
    s = t;
    return len;
}

char * alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else {
        return 0;
    }
}

