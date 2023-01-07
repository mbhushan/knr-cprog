/**
Write the program tail, which prints the last n lines of its input. By default, n is 10, say, but it can be changed
by an optional argument, so that
tail -n
prints the last n lines. The program should behave rationally no matter how unreasonable the input or the value of n.
Write the program so it makes the best use of available storage; lines should be stored as in the sorting program of
Section 5.6, not in a two-dimensional array of fixed size.
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

int main(int argc, char *argv[]) {
    int nlines = 0;
    int tail = 0;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        writelines(lineptr, nlines);
    }
    if (argc == 1)
        tail = DEFAULT;
    else if (argc == 2 && (*++argv)[0] == '-')
        tail = atoi(argv[0]+1);
    else
        printf("error: tail [-n]\n");

    tailprint(lineptr, nlines, tail);

    return 0;
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