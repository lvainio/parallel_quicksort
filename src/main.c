/*
 * A parallelized implementation of the famous quicksort algorithm.
 * 
 * Author: Leo Vainio
 * 
 * Compile: gcc -o quicksort main.c -pthread TODO: UPDATE
 * Run: ./quicksort <size>
 */

#include <pthread.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#include "data.h"
#include "quick_sort.h"

// timer, taken from matrix.c given in the course.
double read_timer() {
    static bool initialized = false;
    static struct timeval start;
    struct timeval end;
    if( !initialized )
    {
        gettimeofday( &start, NULL );
        initialized = true;
    }
    gettimeofday( &end, NULL );
    return (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
}

// main
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Invalid argument, usage: ./quicksort <len>\n");
        return 0;
    }
    int n = atoi(argv[1]);
    if (n < 0) {
        printf("Invalid length of array, can't have negative length\n");
        return 0;
    }

    int* arr = generate_array();
    Args args = {arr, 0, n-1};

    double start_time = read_timer();

    print_array();
    quick_sort(&args);
    print_array();

    // print_array();
    // parallel_quicksort(&args);
    // print_array();

    double end_time = read_timer();
    printf("The execution time is %g sec\n", end_time - start_time);

    free_array();
    return 0;
}

// https://stackoverflow.com/questions/4586405/how-to-get-the-number-of-cpus-in-linux-using-c
// nr of cores^^^ try it out

// parallel_quicksort is a parallelized implementation of quicksort. 
void* parallel_quicksort(void* arg) {
    Args *args = arg;

    // TODO: just parallelise down to a certain level and a cutoff point? say like 4 or 8 threads total. that would be like 3 level
    // 2^3. Look into if pthreads utilizes all cpu cores or if that needs to be set explicitly. 

    // MAYBE CHANGE NR OF CORES ON VIRTUAL MACHINE

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