/**
 * binary search: find x in v[0] <= v[1] <= ... <= v[n-1]
 */

#include <stdio.h>

int binsearch(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n-1;
    while (low <= high) {
        mid = low + (high-low)/2;
        if (x < v[mid]) high = mid-1;
        else if (x > v[mid]) low = mid+1;
        else return mid; /* found match */
    }
    return -1;
}

int main() {
    int v[] = {1, 2,3, 4, 5,6,7,8,9};
    int x[] = {3, 7, 0, 11};

    int n1 = 9;
    int n2 = 4;
    int i=0;
    for (i=0; i<n2; i++) {
        printf("key %d found? %d\n", x[i], binsearch(x[i], v, n1));
    }
    return 0;
}
