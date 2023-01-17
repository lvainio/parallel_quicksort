/*
 * A parallelized implementation of the famous quicksort algorithm.
 * 
 * Author: Leo Vainio
 * 
 * Compile: gcc -o quicksort main.c -pthread
 * Run: ./quicksort <size>
 */

#include <pthread.h>
#include <stdio.h> 
#include <stdlib.h>

#include "main.h"

int n;
int* nums;

// main
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Invalid argument, usage: ./quicksort <len>\n");
        return 0;
    }
    
    n = atoi(argv[1]);
    if (n < 0) {
        printf("Invalid length of array, can't have negative length\n");
        return 0;
    }

    generate_array();

    // TIME
    // print_array();
    // quick_sort((Args){0, n-1});
    // print_array();
    // END TIME
    // print time taken to execute with normal quicksort

    // TIME
    Args args = {0, n-1};
    print_array();
    parallel_quicksort(&args);
    print_array();
    // END TIME
    // PRINT TIME WITH PARALLEL

    free(nums);
    fflush(stdin);
    return 0;
}

// parallel_quicksort is a parallelized implementation of quicksort. 
void* parallel_quicksort(void* arg) {
    Args *args = arg;

    int pivot = partition((Args){args->left, args->right}); // maybe parallelize partition later on.

    if(args->right - args->left > 20) { // maybe have this one based on respective partition size instead. 
        pthread_t t_left;
        pthread_t t_right;

        Args left_args = {args->left, pivot - 1};
        if(pthread_create(&t_left, NULL, parallel_quicksort, &left_args) != 0) {
            fprintf(stderr, "Creating thread failed");
        } 

        Args right_args = {pivot + 1, args->right};
        if(pthread_create(&t_right, NULL, parallel_quicksort, &right_args) != 0) {
            fprintf(stderr, "Creating thread failed");
        } 

        if(pthread_join(t_left, NULL) != 0) {
            fprintf(stderr, "Joining thread failed");
        }

        if(pthread_join(t_right, NULL) != 0) {
            fprintf(stderr, "Joining thread failed");
        }
    } else {
        quick_sort((Args){args->left, pivot - 1});
        quick_sort((Args){pivot + 1, args->right});
    }
}

// quick_sort is a standard non-parallelized fixed pivot implementation of quicksort.
void quick_sort(Args args) {
    if(args.left < args.right) {
        int pivot = partition((Args){args.left, args.right});
        quick_sort((Args){args.left, pivot - 1});
        quick_sort((Args){pivot + 1, args.right});
	}
}

// partition picks the last element of the subarray as pivot and places
// lower elements to the "left" and higher elements to the "right" of the pivot.
int partition(Args args) {
    int pivot = nums[args.right];
    int i = args.left - 1;
    for(int j = args.left; j < args.right; j++) {
        if(nums[j] <= pivot) {
            i++;
            swap(i, j);
        }
    }
    swap(i + 1, args.right);
    return i + 1;
}

// swap swaps two elements of the array nums.
void swap(int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

// generate_array fills nums with random integers ranging from 0 to RAND_MAX.
void generate_array() {
    srand(time(NULL));
    nums = (int*) malloc(n * sizeof(int));
    for (size_t i = 0; i < n; i++) {
        nums[i] = rand() % 500;
    }
}

// print_array prints out the contents of nums.
void print_array() {
    printf("nums: {");
    for (size_t i = 0; i < n; i++) {
        printf("%d", nums[i]);
        if (i != n-1) {
            printf(", ");
        }
    }
    printf("}\n");
}



// ----- SOME SIMPLE TESTS ----- //

// test
void test() {
    // maybe copy array and then run built in sort on it and compare arrays. 
    // some edge cases. 
}