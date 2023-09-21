#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

//Swaps the places of the values at i and j
void swap(int *i, int *j) {
    int k = *j;
    *j = *i;
    *i = k;
}

int median3Sort(int *list, int iLeft, int iRight) {
    int mid = (iLeft + iRight) / 2;
    if (list[iLeft] > list[mid]) swap(&list[iLeft], &list[mid]);
    if (list[mid] > list[iRight]) {
        swap(&list[mid], &list[iRight]);
        if (list[iLeft] > list[mid]) swap(&list[iLeft], &list[mid]);
    }
    return mid; //Returns the index of the pivot
}

int split(int *list, int iLeft, int iRight) {
    int leftPointer, rightPointer;
    int mid = median3Sort(list, iLeft, iRight);
    int pivotValue = list[mid];
    swap(&list[mid], &list[iRight - 1]);
    for (leftPointer = iLeft, rightPointer = iRight - 1;;) {
        while (list[++leftPointer] < pivotValue);
        while (list[--rightPointer] > pivotValue);
        if (leftPointer >= rightPointer) break;
        swap(&list[leftPointer], &list[rightPointer]);
    }
    swap(&list[leftPointer], &list[iRight - 1]);
    return leftPointer; //This is the current index of the pivot, and is used to split the list. 
}

void quicksort(int *list, int iLeft, int iRight) {
    if (iRight - iLeft > 2) {
        int pivot = split(list, iLeft, iRight);
        quicksort(list, iLeft, pivot - 1);
        quicksort(list, pivot + 1, iRight);
    } else median3Sort(list, iLeft, iRight);
}

int isSortedCorrectly(int *list, int length) {
    for (int i = 0; i < length - 1; i++) {
        if (list[i] > list[i + 1]) return 0;
    }
    return 1;
}

int main() {
    int *test = (int *) malloc(1000000 * sizeof(int));
    clock_t start, end;
    int rounds = 0;
    start = clock();

    while ( ((double) (end - start)) / CLOCKS_PER_SEC < 10.0 ) {
        for (int i = 0; i < 1000000; i++) {
            test[i] = rand();
        }
        quicksort(test, 0, 999999);
        if (!isSortedCorrectly(test, 1000000)) break;
        end = clock();
        rounds++;
    }
    printf("%.2f ms per round.\n", ((double) (end - start)) / rounds);
    return 0;
}