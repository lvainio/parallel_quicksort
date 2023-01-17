#ifndef HEADERFILE_H
#define HEADERFILE_H

struct Args {
    int left;
    int right;
};

int partition(Args);
void generate_array();
void print_array();
void quick_sort(Args);

#endif