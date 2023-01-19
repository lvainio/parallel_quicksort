#include <pthread.h>
#include <stdio.h> 
#include <stdlib.h>

#include "quick_sort.h"

// TODO: make sure the attribute level is set for all things in this file and main, set to 0 first
// TODO: cleanup

// parallel_quicksort is a parallelized implementation of quicksort. 
void* parallel_quick_sort(void* arg) {
    Args *args = arg;
    int left = args->left;
    int right = args->right;
    int level = args->level;
    int pivot = partition(args);
    Args left_args = {args->arr, left, pivot-1, level+1}; // TODO: make sure we konw exactly how many threads are created. 
    Args right_args = {args->arr, pivot+1, right, level+1};

    if(left < right) {
        if((right - left > 20) && (args->level <= MAX_LEVEL)) { // TODO: maybe do this as a per partition thing instead. i.e pivot-left, right-pivot, right - left > 20) because correctness maybe an issue here
            pthread_t t_left;
            pthread_t t_right;

            if(pthread_create(&t_left, NULL, parallel_quick_sort, &left_args) != 0) {
                fprintf(stderr, "Creating thread failed");
            } 
            if(pthread_create(&t_right, NULL, parallel_quick_sort, &right_args) != 0) {
                fprintf(stderr, "Creating thread failed");
            } 

            if(pthread_join(t_left, NULL) != 0) {
                fprintf(stderr, "Joining thread failed");
            }
            if(pthread_join(t_right, NULL) != 0) {
                fprintf(stderr, "Joining thread failed");
            }

        } else {
            quick_sort(&left_args); // TODO: we could just call parallel quicksort here as well maybe and make sure level is above
            quick_sort(&right_args);
        }
    }
} 


// quick_sort is a standard non-parallelized fixed pivot implementation of quicksort.
// The last element in the subarray is used as pivot.
void quick_sort(Args* args) {
    int left = args->left;
    int right = args->right;
    if(left < right) {
        int pivot = partition(args);
        Args left_args = {args->arr, left, pivot-1, 0};
        Args right_args = {args->arr, pivot+1, right, 0};
        quick_sort(&left_args);
        quick_sort(&right_args);
	}
}

// partition picks the last element of the subarray as pivot and places
// lower elements to the "left" and higher elements to the "right" of the pivot.
int partition(Args* args) {
    int left = args->left;
    int right = args->right;
    int pivot = args->arr[right];
    int i = left - 1;
    for(int j = left; j < right; j++) {
        if(args->arr[j] <= pivot) {
            i++;
            swap(args->arr, i, j);
        }
    }
    swap(args->arr, i + 1, right);
    return i + 1;
}

// swap swaps two elements of the array.
void swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// ----- BENCHMARKS ----- //

// standard implementation:

// n = 100 000:     0.011496, 0.011918, 0.012469 (seconds)
// n = 1 000 000:   0.163922, 0.152957, 0.16318 (seconds)
// n = 10 000 000:  2.06777, 1.92765, 1.82644 (seconds)
// n = 100 000 000: 21.7889, 22.7262, 22.9358 (seconds)

// parallel implementation: (MAX_LEVEL = 4)
// n = 100 000:     0.004884, 0.005622, 0.004693 (seconds)
// n = 1 000 000:   0.04353, 0.091076, 0.049347 (seconds)
// n = 10 000 000:  0.401032, 0.526276, 0.558398 (seconds)
// n = 100 000 000: 6.10673, 12.3149, 4.88736 (seconds)
// n = 1 000 000 000 : 124.951 (seconds)

// parallel implementation: (MAX_LEVEL = 8)
// n = 100 000 000: 5.06814, 4.50018, 3.91338

// parallel implementation: (MAX_LEVEL = 12)
// n = 100 000 000: 4.51871, 3.94922, 4.3525

// parallel implementation: (MAX_LEVEL = 2)
// n = 100 000 000: 15.0405