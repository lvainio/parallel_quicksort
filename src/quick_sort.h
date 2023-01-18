#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#define MAX_LEVEL 2

typedef struct {
    int* arr;
    int left;
    int right;
    int level;
} Args;

void* parallel_quick_sort(void*);
void quick_sort(Args*);
int partition(Args*);
void swap(int*, int, int);

#endif