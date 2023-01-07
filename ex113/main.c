#include <stdio.h>

#define IN 1 /* inside word */
#define OUT 0 /* outside word */
#define MAXWORDLEN 45 /* max len of the word */

 int main() {

    int ch = EOF;
    int i, j, maxlen, maxcnt;
    i = j = 0;
    int word_len[MAXWORDLEN+1];
    int state = IN;
    int nc = 0;
    maxlen = 0;
    maxcnt = 0;

    for (i=0; i<=MAXWORDLEN; i++) word_len[i] = 0;

    while ((ch = getchar()) != '$') {
        ++nc;
        if (ch == ' ' || ch == '\t' || ch == '\n') {
            state = OUT;
            --nc;
        }
        if (state == OUT) {
            if (nc != 0 && nc <= MAXWORDLEN) {
                ++word_len[nc];
                maxlen = nc > maxlen ? nc: maxlen;
                maxcnt = word_len[nc] > maxcnt ? word_len[nc] : maxcnt;
            }
            state = IN;
            nc = 0;
        }
    }
    for (i=1; i<=maxlen; ++i) {
        printf("|%2d|", i);
        for (j=0; j<word_len[i]; ++j) putchar('*');
        printf("\n");
    }
    printf("\n\n================================================================================\n\n");

    for (i=maxcnt; i>0; i--) {
        printf("%4d|", i);
        for (j=0; j<maxlen; j++) {
            if (word_len[j] >= i)  printf("*  ");
            else printf("   ");
        }
        printf("\n");
    }
     printf("    +");
    for (j=0; j<=maxlen; j++) printf("---");
    printf("\n       ");
    for (j=0; j<maxlen; j++) printf("%2d ", j+1);

    return 0;
}
