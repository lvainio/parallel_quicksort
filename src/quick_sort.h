#ifndef QUICK_SORT_H
#define QUICK_SORT_H

typedef struct {
    int* arr;
    int left;
    int right;
} Args;

void quick_sort(Args*);
int partition(Args*);
void swap(int*, int, int);

#endif