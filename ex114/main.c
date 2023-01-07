#include <stdio.h>

#define MAX_CHARS 255
#define MIN 33
#define MAX 127

int main() {
    int ch;
    int i, j;
    int freq_arr[MAX+1];

    for (int i=0; i<=MAX; i++) freq_arr[i] = 0;

    while ((ch = getchar()) != '$') {
        if (ch >= MIN && ch <= MAX) ++freq_arr[ch];
    }

    for (i=MIN; i<=MAX; i++) {
        printf("%4c (%4d)|", i, i);
        for (j=0; j<freq_arr[i]; j++) printf("*");
        printf("\n");
    }
    return 0;
}
