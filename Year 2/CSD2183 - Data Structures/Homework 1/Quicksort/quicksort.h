#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include "median_functions.h"

int partition(std::vector<int> &a, int start, int end, int initial_pivot);
void quicksort(std::vector<int> &a, int start, int end, int k);

#endif
