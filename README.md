# Quicksort with switch into helper algorithm
Both the quicksort and insertion sort algorithms used here are based on the ones written by Hafting and Ljosland (2003)[^1].

### Insertion sort
Insertion sort was chosen as this algorithm is very fast at sorting smaller datasets, which is ideal for this sort of application. It has a time complexity of O(n<sup>2</sup>). In this code the algorithm switches into insertion sort when a sub-array of 25 elements is reached from the quicksort. 

### Time usage compared to regular quicksort
The time usage of the different algorithms were measured over a period of 10 seconds, and finding the average time per iteration. 
With regular quicksort, on an array of 1,000,000 elements, the algorithm took about 107ms per iteration. 
This also included the initialization of the array using rand(), and well as a linear check of the array to ensure correct sorting afterwards. This same process takes about 100ms with the current application, which a roughly 6,5% improvement. 

### Other attempts
In addition to the insertion sort, multithreading was considered as a possible improvement. 
The first attempt was to split off the left side of the array into a separate thread, essentially putting half the work into other threads. This proved to be extremely time-consuming, and was discarded. 
Afterwards, the attempt was made to run just the insertion sort in a separate thread, but this also proved to be quite slow. This is likely due to a poor implementation of threading, as it cause the main thread to wait a lot.  
The branch "pivot-test" also gives an alternative where the pivot is selected by sorting the first, last, 1/4- and 3/4-position elements, and returning the second last one. This approach had no noticable effect on performance. Returning the second element (1/4-position) was the same. 

### Notes
This code was written as part of an assignment at the Norwegian University of Science and Technology. 


[^1]: Hafting, H. and Ljosland, M. (2003) *Algoritmer og datastrukturer*. 1st ed. Oslo: Gyldendal Akademisk.

