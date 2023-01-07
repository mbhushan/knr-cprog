/**
 * Exercise 3-1. Our binary search makes two tests inside the loop, when one would suffice
 * (at the price of more tests outside). Write a version with only one test inside the loop
 * and measure the difference in run-time.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int binsearch(int x, int v[], int n); /* original KnR function */
int binsearch31(int x, int v[], int n); /* new binsearch function as per requirement in exercise 3.1 */
int genrand(int lower, int upper);

#define MAX_ELEMENT 2000000

int main() {
    int data[MAX_ELEMENT];
    int i=0;
    clock_t time_taken;

    while(i<MAX_ELEMENT){
        data[i] = i+1;
        ++i;
    }

    int r = genrand(1, MAX_ELEMENT);
//    printf("is key %d present? %d\n", r, binsearch(r,data, MAX_ELEMENT));
//    printf("is key %d present? %d\n", r, binsearch31(r,data, MAX_ELEMENT));

    /* calc approx time taken for 1million iterations of binserach */
    for(i=0, time_taken=clock(); i<MAX_ELEMENT; ++i){
        binsearch(r, data, MAX_ELEMENT);
    }
    time_taken = clock() - time_taken;
    printf("binsearch took %lu clocks (%lu seconds)\n",
           (unsigned long)time_taken, (unsigned long)time_taken/CLOCKS_PER_SEC);

    /* calc approx time taken for 1million iterations of binserach31 */
    for(i=0, time_taken=clock(); i<MAX_ELEMENT; ++i){
        binsearch31(r, data, MAX_ELEMENT);
    }
    time_taken = clock() - time_taken;
    printf("binsearch31 took %lu clocks (%lu seconds)\n",
           (unsigned long)time_taken, (unsigned long)time_taken/CLOCKS_PER_SEC);

    return 0;
}

int binsearch31(int x, int v[], int n) {
    int low, high, mid, idx;
    low=0;
    high=n-1;
    idx = -1;
    mid = low + (high-low)/2;
    while((low<=high) && (v[mid]!=x)) {
        if (x < v[mid]) {
            high=mid-1;
        } else {
            low=mid+1;
        }
        mid = low + (high-low)/2;
    }

    idx = (x==v[mid])? mid: -1;

    return idx;
}

int binsearch(int x, int v[], int n) {
    int low, high, mid;
    low=0;
    high=n-1;
    while(low<=high) {
        mid = low + (high-low)/2;
        if (x < v[mid]) high = mid-1;
        else if (x > v[mid]) low = mid+1;
        else return mid;
    }
    return -1;
}

int genrand(int lower, int upper){
    srand(time(0));
    return (rand()%(upper-lower+1)) + lower;
}
