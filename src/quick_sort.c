
#include "quick_sort.h"

// quick_sort is a standard non-parallelized fixed pivot implementation of quicksort.
// The last element in the subarray is used as pivot.
void quick_sort(Args* args) {
    int left = args->left;
    int right = args->right;
    if(left < args) {
        int pivot = partition(args);
        Args left_args = {args->arr, left, pivot-1};
        Args right_args = {args->arr, pivot+1, right};
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
