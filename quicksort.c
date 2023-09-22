#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

//Struct containing the arguments for the quicksort function. 
struct qsargs {
    int *list;
    int iLeft;
    int iRight;
};

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

void quicksort(struct qsargs args) {
    int *list = args.list;
    int iLeft = args.iLeft;
    int iRight = args.iRight;
    if (args.iRight - args.iLeft > 24) {
        int pivot = split(list, iLeft, iRight);
        args.iRight = pivot - 1;
        quicksort(args);
        args.iRight = iRight;
        args.iLeft = pivot + 1;
        quicksort(args);
    } else { //At 25 elements, the algorithm switches to insertionsort. 
        insertionSort(list, iLeft, iRight);
    }
}

int isSortedCorrectly(int *list, int length) {
    if (length < 2) return 1;
    for (int i = 0; i < length - 1; i++) {
        if (list[i] > list[i + 1]) return 0;
    }
    return 1;
}

//This function runs the left side of the array in a new thread, then runs regular quicksort on the right side. Afterwards, it waits for the child thread to finish up. 
void startSorting(int *list, int l, int r) {
    if (r - l > 24) {
        int pivot = split(list, l, r);
        struct qsargs args;
        args.list = list;
        args.iLeft = l;
        args.iRight = pivot - 1;
        pthread_t thread;
        pthread_create(&thread, NULL, quicksort, &args);
        struct qsargs args2;
        args2.iLeft = pivot + 1;
        args2.iRight = r;
        args2.list = list;
        quicksort(args2);
        pthread_join(thread, NULL);
    } else insertionSort(list, l, r);
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
        startSorting(test, 0, listLength - 1);
        if (!isSortedCorrectly(test, listLength)) {
            printf("Incorrect sort!");
            break;
        }
        end = clock();
        rounds++;
    }
    printf("%.2f ms per round.\n", ((double) (end - start)) / rounds);
    return 0;
}