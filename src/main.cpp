/*
 * A parallelized implementation of the famous quicksort algorithm.
 * 
 * Author: Leo Vainio
 * 
 * Compile: gcc -o quicksort main.cpp -lstdc++ -pthread
 * Run: ./quicksort <size>
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <pthread.h>
#include <string>

#include "main.hpp"

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

    // TIME
    quick_sort((Args){0, n-1});
    // END TIME
    // print time taken to execute

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
void quick_sort(Args args) {
    if(left < right) {
        int pivot = partition((Args){args.left, args.right});
        quick_sort((Args){args.left, pivot - 1});
        quick_sort((Args){pivot + 1, args.right});
	}
}

// partition picks the last element of the subarray as pivot and partitions
// lower elements to the "left" and higher elements to the "right" of the pivot.
int partition(Args args) {
    int pivot = nums[args.right];
    int i = args.left - 1;
    for(int j = args.left; j < args.right; j++) {
        if(nums[j] <= pivot) {
            i++;
            std::swap(nums[i], nums[j]);
        }
    }
    std::swap(nums[i + 1], nums[args.right]);
    return i + 1;
}

// parallel_quicksort is a parallelized implementation of the famous quicksort algorithm. 
void parallel_quicksort() {
    pthread_t t_right;
    pthread_t t_left;


    // the calls to quick_sort can be done in threads. 
    // maybe have a cutoff point? at like size 20 subarray or more. cuz of overhead

    // call the two threads then wait(). or join().

    // this will depend alot on how the join() functions. because if it is a global thing then
    // this will not work and we will need some other way of synchronizing. 

    // we do however have the Thread ID so it might be possible. 

    // maybe just make this implementation and see what happens cuz then i wlil realise what the problem is. if any
}