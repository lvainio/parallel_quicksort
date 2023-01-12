/*
 * A parallelized implementation of the famous quicksort algorithm.
 * 
 * Author: Leo Vainio
 * 
 * Compile: gcc -o quicksort parallel_quicksort.cpp -lstdc++
 * Run: ./quicksort <size>
 */

#include <iostream>

// a global array probs. or not even global but it has to be shared atleast 

// main
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./quicksort <len>" << std::endl;
        return 0;
    }

    int n;
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
        std::cout << "Invalid length of array, can't have negative length" << std::endl;
    }

    return 0;
}

// shared mem and blablabla
void setup() {

}

// generate array of ints
void generate_array() {

}

// parallel_quicksort is a parallelized implementation of the famous quicksort algorithm. 
void parallel_quicksort() {
    std::cout << "hej" << std::endl;
}

// google test.
void testing() {

}