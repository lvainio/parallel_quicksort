/*
 * A parallelized implementation of the famous quicksort algorithm.
 * 
 * Author: Leo Vainio
 * 
 * Compile: gcc -o quicksort parallel_quicksort.cpp -lstdc++
 * Run: ./quicksort <size>
 */

#include <cstdlib>
#include <iostream>
#include <string>

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
    print_array();
    quick_sort(0, n-1);
    print_array();

    free(nums);
    return 0;
}

// generate_array fills nums with random integers ranging from 0 to RAND_MAX.
void generate_array() {
    nums = (int*) malloc(n * sizeof(int));
    for (size_t i = 0; i < n; i++) {
        nums[i] = rand();
    }
}

// print_array prints out the contents of nums.
void print_array() {
    for (size_t i = 0; i < n; i++) {
        std::cout << nums[i];
    }
}

// quick_sort is a standard non-parallelized implementation of quick_sort.
void quick_sort(int left, int right) {
    if(left < right) {
        int pivot = partition(left, right);
        quick_sort(left, pivot - 1);
        quick_sort(pivot + 1, right);
	}
}

int partition(int left, int right) {
    int pivot = nums[right];
    int i = left - 1;
    for(int j = left; j < right; j++) {
        if(nums[j] <= pivot) {
            i++;
            swap(i, j);
        }
    }
    swap(i + 1, right);
    return i + 1;
}

void swap(int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}



// parallel_quicksort is a parallelized implementation of the famous quicksort algorithm. 
void parallel_quicksort() {
    std::cout << "hej" << std::endl;
}

// google test.
void testing() {

}