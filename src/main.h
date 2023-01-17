#ifndef HEADERFILE_H
#define HEADERFILE_H

typedef struct {
    int left;
    int right;
} Args;

int partition(Args);
void generate_array();
void print_array();
void quick_sort(Args);
void* parallel_quicksort(void*);
void swap(int, int);
void test();

#endif