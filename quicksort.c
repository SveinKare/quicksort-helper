#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Swaps the places of the values at i and j
void swap(int *i, int *j) {
    int k = *j;
    *j = *i;
    *i = k;
}

//Checks if the given array is sorted correctly. 
int isSortedCorrectly(int *list, int l, int r) {
    for (int i = l; i < r; i++) {
        if (list[i] > list[i + 1]) return 0;
    }
    return 1;
}

//This function is a bit wonky, but it essentially works as an insertion sort for 4 discontiguous elements. 
int sort4(int *list, int iLeft, int iRight) {
    int diff = iRight - iLeft;
    int mid = iLeft + (diff >> 2)*3;
    int quart = iLeft + (diff >> 2);
    if (list[quart] < list[iLeft]) swap(&list[quart], &list[iLeft]);
    if (list[mid] < list[quart]) {
        swap(&list[mid], &list[quart]);
        if (list[quart] < list[iLeft]) swap(&list[quart], &list[iLeft]);
    }
    if (list[iRight] < list[mid]) {
        swap(&list[iRight], &list[mid]);
        if (list[mid] < list[quart]) {
            swap(&list[mid], &list[quart]);
            if (list[quart] < list[iLeft]) swap(&list[quart], &list[iLeft]);
        }
    }
    return mid; //Returns the index of the pivot
}

void insertionSort(int *list, int iLeft, int iRight) {
    for (int j = iLeft + 1; j <= iRight; ++j) {
        int current = list[j];
        int i = j - 1;
        while (i >= 0 && list[i] > current) {
            list[i + 1] = list[i];
            --i;
        }
        list[i + 1] = current;
    }
}

int split(int *list, int iLeft, int iRight) {
    int leftPointer, rightPointer;
    int mid = sort4(list, iLeft, iRight);
    int pivotValue = list[mid];
    swap(&list[mid], &list[iRight - 1]);
    for (leftPointer = iLeft, rightPointer = iRight - 1;;) {
        while (list[++leftPointer] < pivotValue);
        while (list[--rightPointer] > pivotValue);
        if (leftPointer >= rightPointer) break;
        swap(&list[leftPointer], &list[rightPointer]);
    }
    swap(&list[leftPointer], &list[iRight - 1]);
    return leftPointer; //This is the current index of the pivot, and is used for the recursive calls. 
}

void quicksort(int *list, int iLeft, int iRight) {
    if (iRight - iLeft > 24) {
        int pivot = split(list, iLeft, iRight);
        quicksort(list, iLeft, pivot - 1);
        quicksort(list, pivot + 1, iRight);
    } else { //At 25 elements, the algorithm switches to insertionsort. 
        insertionSort(list, iLeft, iRight);
    }
}



int main() {
    const int listLength = 1000000;
    int *test = (int *) malloc(listLength * sizeof(int));
    clock_t start, end;
    int rounds = 0;
    start = clock();

    while ( ((double) (end - start)) / CLOCKS_PER_SEC < 10.0 ) {
        for (int i = 0; i < listLength; i++) {
            test[i] = rand();
        }
        quicksort(test, 0, listLength - 1);
        if (!isSortedCorrectly(test, 0, listLength - 1)) {
            printf("Incorrect sort!\n");
            break;
        }
        end = clock();
        rounds++;
    }
    printf("%.2f ms per round.\n", ((double) (end - start)) / rounds);
 
/*     int test[] = {9, 2, 3, 4, 5, 6, 7, 8, 9, 9};
    if (isSortedCorrectly(test, 0, 9)) printf("Success!\n");
    else printf("Failure!\n"); */

    return 0;
}