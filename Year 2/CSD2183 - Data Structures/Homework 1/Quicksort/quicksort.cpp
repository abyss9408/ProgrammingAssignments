#include "quicksort.h"

int partition(std::vector<int> &a, int start, int end, int initial_pivot) {
    // Partitions the array around an initial pivot element and returns the
    // index of the pivot element after partitioning. In our case, the initial
    // pivot element is the median of medians returned by the function in the
    // previous step.

    // Find the index of the pivot element.
    int pivotIndex = start;
    for (int i = start; i <= end; i++)
    {
        if (a[i] == initial_pivot)
        {
            pivotIndex = i;
            break;
        }
    }
    // Move the pivot element to the end.
    std::swap(a[pivotIndex], a[end]);

    // Partition the array: all elements less than the pivot are moved to the left.
    int storeIndex = start;
    for (int i = start; i < end; i++)
    {
        if (a[i] < initial_pivot)
        {
            std::swap(a[i], a[storeIndex]);
            storeIndex++;
        }
    }
    // Place the pivot in its correct position.
    std::swap(a[storeIndex], a[end]);
    return storeIndex;
}

void quicksort(std::vector<int> &a, int start, int end, int k)
{
    // Performs the quicksort algorithm with median-of-medians pivot
    // selection. The parameter `k` represents the group size used in the
    // pivot selection process.

    if (start < end)
    {
        // Use median-of-medians to select a robust pivot.
        int pivotCandidate = find_median_of_medians(a, start, end, k);
        // Partition the array around the pivotCandidate.
        int pivotIndex = partition(a, start, end, pivotCandidate);
        // Recursively sort the left and right subarrays.
        quicksort(a, start, pivotIndex - 1, k);
        quicksort(a, pivotIndex + 1, end, k);
    }
}
