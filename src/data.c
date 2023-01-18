#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

int* nums;
int n;

// generate_array fills nums with random integers ranging from 0 to RAND_MAX.
int* generate_array(int len) {
    n = len;
    srand(time(NULL));
    nums = (int*) malloc(n * sizeof(int));
    for (size_t i = 0; i < n; i++) {
        nums[i] = rand();
    }
    return nums;
}

// free_array frees the allocated memory.
void free_array() {
    free(nums);
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