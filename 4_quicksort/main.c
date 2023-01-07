/* quicksort: sorting algorithm with worst case of O(n^2) and average case of nlogn. Its in place */

#include <stdio.h>

void qsort(int v[], int left, int right);
void swap(int v[], int i, int j);

int main() {
    int v[] = {9,8,7,6,5,4,1,2,3};
    int left = 0;
    int right = 8;
    int i;

    qsort(v, left, right);

    for (i=left; i<=right; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    return 0;
}

void qsort(int v[], int left, int right) {
    int i, last;
    int mid;

    if (left >= right) return;
    mid = left + (right - left)/2;
    swap(v, left, mid);
    last = left;

    for (i=left+1; i<=right; i++) {
        if (v[i] < v[left]) swap(v, ++last, i);
    }
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);

}

void swap(int v[], int i, int j) {
    int t = v[i];
    v[i] = v[j];
    v[j] = t;
}