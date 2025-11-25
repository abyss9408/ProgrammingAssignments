#ifndef MEDIAN_FUNCTIONS_H
#define MEDIAN_FUNCTIONS_H

#include <vector>

int find_median(std::vector<int> &a, int start, int end);
std::vector<int> find_group_medians(std::vector<int> &a, int start, int end, int k);
int find_median_of_medians(std::vector<int> &a, int start, int end, int k);

#endif
