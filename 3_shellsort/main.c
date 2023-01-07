/**
 * shellsort: sort v[0] .. v[n-1] into increasing order
 */

#include <stdio.h>

void shellsort(int v[], int n) {
    int gap, i, j, temp;

    for (gap = n/2; gap > 0; gap /= 2) {
        for(i=gap; i<n; i++) {
            for (j=i-gap; j>=0 && v[j] > v[j+gap]; j -= gap) {
                temp = v[j]; v[j] = v[j+gap]; v[j+gap] = temp;
            }
        }
    }
}

int main() {
    int v[] = {9,8,7,6,5,3,2};
    int i=0;
    printf("input numbers:\n");
    for (i=0; i<7; i++) printf("%d ", v[i]);
    printf("\n");

    printf("after shell sorting: \n");
    shellsort(v, 7);
    for (i=0; i<7; i++) printf("%d ", v[i]);
    printf("\n");

    return 0;
}
