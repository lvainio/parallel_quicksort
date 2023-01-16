/*
 * A parallelized implementation of the famous quicksort algorithm.
 * 
 * Author: Leo Vainio
 * 
 * Compile: gcc -o quicksort main.cpp -lstdc++
 * Run: ./quicksort <size>
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "main.h"

int n;
int* nums;

// main
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Invalid argument, usage: ./quicksort <len>" << std::endl;
        return 0;
    }

    try {    
        n = std::stoi(argv[1]);
    } catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument, usage: ./quicksort <len>" << std::endl;
        return 0;
    } catch (const std::out_of_range& ofr) {
        std::cerr << "Integer out of range" << std::endl;
        return 0;
    }

    if (n < 0) {
        std::cerr << "Invalid length of array, can't have negative length" << std::endl;
        return 0;
    }

    generate_array();
    quick_sort(0, n-1);

    free(nums);
    return 0;
}

// generate_array fills nums with random integers ranging from 0 to RAND_MAX.
void generate_array() {
    srand(time(NULL));
    nums = (int*) malloc(n * sizeof(int));
    for (size_t i = 0; i < n; i++) {
        nums[i] = rand();
    }
}

// print_array prints out the contents of nums.
void print_array() {
    std::cout << "nums: {";
    for (size_t i = 0; i < n; i++) {
        std::cout << nums[i];
        if (i != n-1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
}

// quick_sort is a standard non-parallelized implementation of quick_sort.
void quick_sort(int left, int right) {
    if(left < right) {
        int pivot = partition(left, right);
        quick_sort(left, pivot - 1);
        quick_sort(pivot + 1, right);
	}
}

// partition picks the last element of the subarray as pivot and partitions
// lower elements to the "left" and higher elements to the "right" of the pivot.
int partition(int left, int right) {
    int pivot = nums[right];
    int i = left - 1;
    for(int j = left; j < right; j++) {
        if(nums[j] <= pivot) {
            i++;
            std::swap(nums[i], nums[j]);
        }
    }
    std::swap(nums[i + 1], nums[right]);
    return i + 1;
}

// parallel_quicksort is a parallelized implementation of the famous quicksort algorithm. 
void parallel_quicksort() {
    // the calls to quick_sort can be done in threads. 
    // maybe have a cutoff point? at like size 20 subarray or more. cuz of overhead

    // call the two threads then wait(). or join().

    // this will depend alot on how the join() functions. because if it is a global thing then
    // this will not work and we will need some other way of synchronizing. 
}

// google test.
void testing() {

}