/*
  simd.cpp
  SIMD implementation of sum and product of a 64-bit ints array
  Author: Bryan Ang Wei Ze
  Date: 2025-10-03
*/

#include "simd.h"

int64_t sumSimd(__m128i const* array, int number_of_ints)
{
    // Initialize accumulator to zero (holds two 64-bit lanes)
    __m128i accumulator = _mm_setzero_si128();

    // Each __m128i holds 2 x 64-bit integers (128 bits / 64 bits = 2)
    // So the number of SIMD vectors is half the number of integers
    int num_vectors = number_of_ints / 2;

    // Process each SIMD vector
    for (int i = 0; i < num_vectors; ++i)
    {
        // Add the two 64-bit integers in array[i] to the two lanes in accumulator
        // This performs parallel addition: accumulator[0] += array[i][0], 
        // accumulator[1] += array[i][1]
        accumulator = _mm_add_epi64(accumulator, array[i]);
    }

    // Extract both 64-bit values from the accumulator
    // Lane 0 contains sum of all even-indexed integers (0, 2, 4, ...)
    int64_t low = _mm_extract_epi64(accumulator, 0);
    // Lane 1 contains sum of all odd-indexed integers (1, 3, 5, ...)
    int64_t high = _mm_extract_epi64(accumulator, 1);

    // Final result is the sum of both lanes
    return low + high;
}

int64_t pdtSimd(__m128i const* array, int number_of_ints)
{
    // Initialize product to 1 (multiplicative identity)
    int64_t product = 1;

    // Each __m128i holds 2 x 64-bit integers (128 bits / 64 bits = 2)
    // So the number of SIMD vectors is half the number of integers
    int num_vectors = number_of_ints / 2;

    // Process each SIMD vector
    for (int i = 0; i < num_vectors; ++i)
    {
        // Extract the lower 64-bit integer from the vector (lane 0)
        int64_t low = _mm_extract_epi64(array[i], 0);
        // Extract the upper 64-bit integer from the vector (lane 1)
        int64_t high = _mm_extract_epi64(array[i], 1);

        // Multiply both values into the running product
        // Since there is no SIMD multiplication for 64-bit integers
        // so extract and multiply sequentially
        product *= low;
        product *= high;
    }

    return product;
}