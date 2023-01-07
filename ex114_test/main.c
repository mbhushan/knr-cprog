#include <stdio.h>

#define MAX 122
#define MIN 97
#define DIFF 32

int main(){
    int c = EOF;
    int i, j;
    int array[MAX - MIN];

    printf("max-min: %d\n", (MAX-MIN));
    for (i = MIN; i <= MAX; i++){
        printf("%d ", i);
        array[i] = 0;
    }
    printf("\n\n size of array: %d\n\n", sizeof(array));
    for (i = MIN; i <= MAX; i++){
        printf("%d ", array[i]);
    }
    printf("\n\n");

    while ((c = getchar()) != '$'){
        if (c >= MIN)
            ++array[c];
        else {
            ++array[c + DIFF];
        }
    }

    for (i = MIN; i <= MAX; i++){
        printf("|%c%c|", i - DIFF, i);
        for (j = 1; j <= array[i]; j++){
            putchar('*');
        }
        putchar('\n');
    }

    return 0;
}
