#include "median_functions.h"
#include <algorithm>

int find_median(std::vector<int> &a, int start, int end)
{
    // Sorts a subarray of `a` from index `start` to `end` using insertion
    // sort and returns the median of the sorted portion.
    for (int i = start + 1; i <= end; ++i)
    {
        int key = a[i];
        int j = i - 1;

        // Move elements of a[start..i-1] that are greater than key to one position ahead
        while (j >= start && a[j] > key)
        {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
    
    // Find median
    int length = end - start + 1;
    int mid = start + (end - start) / 2;

    return a[mid];
}

std::vector<int> find_group_medians(std::vector<int> &a, int start, int end, int k)
{
    // Splits the subarray `a[start:end]` into groups of size `k`, computes
    // the median of each group, and returns a vector containing these
    // medians. The last group may have fewer than `k` elements.
    std::vector<int> medians;
    
    // Process the subarray in chunks of size k
    for (int i = start; i <= end; i += k)
    {
        int group_start = i;
        int group_end = std::min(i + k - 1, end); // Ensure we don't go beyond the end

        // Find the median of the current group
        int median = find_median(a, group_start, group_end);

        // Add the median to the result vector
        medians.push_back(median);
    }
    
    return medians;
}

int find_median_of_medians(std::vector<int> &a, int start, int end, int k)
{
    // Computes the **median-of-medians** by:  
    // a.  Calling `find_group_medians()` to obtain the set of group medians.  
    // b.  Recursively calling `find_median_of_medians()`.

    // Base case: If the subarray contains a single element, return it.
    if (start == end)
    {
        return a[start];
    }

    // Compute medians for each group of size k.
    std::vector<int> medians = find_group_medians(a, start, end, k);
    
    // If there is only one median, return it.
    if (medians.size() == 1)
    {
        return medians[0];
    }

    // Recursively compute the median of the medians.
    return find_median_of_medians(medians, 0, medians.size() - 1, k);
}
