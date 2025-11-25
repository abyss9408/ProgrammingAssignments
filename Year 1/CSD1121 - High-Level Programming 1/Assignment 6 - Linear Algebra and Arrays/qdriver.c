/*
* qdriver.c - driver source file for exercising vector operations.
* 
* Prasanna Ghali
* Original program written: 02/14/2016
* written for High-Level Programming I
*/
#include <stdio.h>  // printf
#include <stdlib.h> // rand, srand
#include "q.h"      // prototypes for array manipulatons
                    // and math.h for sqrt

// static function declarations
static void print_array(int const a[], int size);
static int  random_int(int low, int high);

static void reverse_tests(int seed);
static void add_tests(int seed);
static void scalar_multiply_tests(int seed);
static void dot_product_tests(int seed);
static void cross_product_tests(int seed);
static void length_tests(int seed);

// driver function
int main(void) {
  reverse_tests(5);
  add_tests(7);  
  scalar_multiply_tests(8);
  dot_product_tests(9);
  cross_product_tests(10);
  length_tests(6);

  return 0;
}

// print all elements of an array
void print_array(int const a[], int size) {
  for (int i = 0; i < size; i++) {
    fprintf(stdout, "%5i", a[i]);
  }
  fprintf(stdout, "\n");
}

// generate random numbers between [low, high]
int random_int(int low, int high) {
  return rand() % (high - low + 1) + low;
}

void reverse_tests(int seed) {
  fprintf(stdout, "\nReverse tests =============================\n");

  #define REV_SIZE 100
  int a[] = {8};
  int b[] = {1, 2, 3};
  int c[] = {1, 2, 3, 4};
  
  // fill array d with random integer values ...
  int d[REV_SIZE];
  srand(seed);
  for (int i = 0; i < REV_SIZE; i++) {
    d[i] = random_int(1, REV_SIZE);
  }

  fprintf(stdout, "The original arrays:\n");
  print_array(a, 1);
  print_array(b, 3);
  print_array(c, 4);
  print_array(d, REV_SIZE);

  fprintf(stdout, "\nLengths of original arrays:\n");
  fprintf(stdout, "Length of array a: %10.3f\n", length(a, 1));
  fprintf(stdout, "Length of array b: %10.3f\n", length(b, 3));
  fprintf(stdout, "Length of array c: %10.3f\n", length(c, 4));
  fprintf(stdout, "Length of array d: %10.3f\n", length(d, REV_SIZE));

  reverse_array(a, 1);
  reverse_array(b, 3);
  reverse_array(c, 4);
  reverse_array(d, REV_SIZE);
 
  fprintf(stdout, "\nThe reversed arrays:\n");
  print_array(a, 1);
  print_array(b, 3);
  print_array(c, 4);
  print_array(d, REV_SIZE);

  fprintf(stdout, "\nLengths of reversed arrays:\n");
  fprintf(stdout, "Length of array a: %10.3f\n", length(a, 1));
  fprintf(stdout, "Length of array b: %10.3f\n", length(b, 3));
  fprintf(stdout, "Length of array c: %10.3f\n", length(c, 4));
  fprintf(stdout, "Length of array d: %10.3f\n", length(d, REV_SIZE));

  fprintf(stdout, "\n");
}

void add_tests(int seed) {
  fprintf(stdout, "\nAdd tests =============================\n");

  #define ADD_SIZE_ONE 1
  int x[ADD_SIZE_ONE] = {1};
  int y[ADD_SIZE_ONE] = {2};
  // add two single-elements arrays into a third array
  fprintf(stdout, "Array x: ");
  print_array(x, ADD_SIZE_ONE);
  fprintf(stdout, "Array y: ");
  print_array(y, ADD_SIZE_ONE);
  int z[ADD_SIZE_ONE];
  add_arrays(x, y, z, ADD_SIZE_ONE);
  fprintf(stdout, "Array z (sum of array x and array y): ");
  print_array(z, ADD_SIZE_ONE);
  fprintf(stdout, "\n");

  #define ADD_SIZE_SMALL 8
  int one[ADD_SIZE_SMALL] = {1, 2, 3, 4, 5, 6, 7, 8};
  int two[ADD_SIZE_SMALL] = {4, 6, 8, 2, 4, 3, 5, 8};
  
  // add two small arrays into a third array
  fprintf(stdout, "Array one: ");
  print_array(one, ADD_SIZE_SMALL);
  fprintf(stdout, "Array two: ");
  print_array(two, ADD_SIZE_SMALL);
  int thr[ADD_SIZE_SMALL];
  add_arrays(one, two, thr, ADD_SIZE_SMALL);
  fprintf(stdout, "Array thr (sum of array one and array two):\n");
  print_array(thr, ADD_SIZE_SMALL);
  fprintf(stdout, "\n");

  // add two medium arrays into a third array ...
  #define ADD_SIZE 100
  int a[ADD_SIZE], b[ADD_SIZE], c[ADD_SIZE];

  srand(seed);
  for (int i = 0; i < ADD_SIZE; i++) {
    a[i] = random_int(-100, 100);
    b[i] = random_int(-100, 100);
  }

  fprintf(stdout, "The original arrays:\n");
  print_array(a, ADD_SIZE);
  fprintf(stdout, "\n");
  print_array(b, ADD_SIZE);
  fprintf(stdout, "\n");
  add_arrays(a, b, c, ADD_SIZE);
 
  fprintf(stdout, "The sum of the two arrays:\n");
  print_array(c, ADD_SIZE);
  fprintf(stdout, "\n");
}

void scalar_multiply_tests(int seed) {
  fprintf(stdout, "\nDot product tests =============================\n");

  #define SCALAR_SIZE_ONE 1
  int x[SCALAR_SIZE_ONE] = {2};
  // add two single-elements arrays into a third array
  fprintf(stdout, "Array x: ");
  print_array(x, ADD_SIZE_ONE);
  int multiplier = 100;
  scalar_multiply(x, SCALAR_SIZE_ONE, multiplier);
  fprintf(stdout, "The array multiplied by %i: ", multiplier);
  print_array(x, ADD_SIZE_ONE);
  fprintf(stdout, "\n");

  #define SCALAR_SIZE 100
  int a[SCALAR_SIZE];
  srand(seed);
  for (int i = 0; i < SCALAR_SIZE; i++) {
    a[i] = random_int(-100, 100);
  }

  fprintf(stdout, "The original array:\n");
  print_array(a, SCALAR_SIZE);

  multiplier = 2;
  scalar_multiply(a, SCALAR_SIZE, multiplier);
  fprintf(stdout, "\nThe array multiplied by %i:\n", multiplier);
  print_array(a, SCALAR_SIZE);

  multiplier = 5;
  scalar_multiply(a, SCALAR_SIZE, multiplier);
  fprintf(stdout, "\nAnd now multiplied by %i:\n", multiplier);
  print_array(a, SCALAR_SIZE);
  fprintf(stdout, "\n");
}

static void dot_product_test_small(int seed);
static void dot_product_test_medium(int seed);
static void dot_product_test_large(int seed);

void dot_product_tests(int seed) {
  fprintf(stdout, "\nDot product tests =============================\n");

  int v1[] = {1, 2, 3}, v2[] = {3, 4, 7};
  int const vsize = sizeof(v1) / sizeof(v1[0]);

  // multiply two arrays: dot product
  fprintf(stdout, "Array v1: ");
  print_array(v1, vsize);
  fprintf(stdout, "Array v2: ");
  print_array(v2, vsize);
  int product = dot_product(v1, v2, vsize);
  fprintf(stdout, "The dot product of v1 * v2 is %i\n", product);

  dot_product_test_small(seed);
  dot_product_test_medium(seed);
  dot_product_test_large(seed);
}

void cross_product_tests(int seed) {
  fprintf(stdout, "\nCross product tests =============================\n");

  #define ARRAY_SIZE_X  3
  #define ITERATIONS   10
  
  // fill arrays with random values and compute their cross products
  int a[ARRAY_SIZE_X], b[ARRAY_SIZE_X], c[ARRAY_SIZE_X];
  srand(seed);
  for (int i = 0; i < ITERATIONS; i++) {
    for (int j = 0; j < ARRAY_SIZE_X; j++) {
      a[j] = random_int(-10, 10);
      b[j] = random_int(-10, 10);
    }

    fprintf(stdout, "The original arrays and cross product are:\n");
    print_array(a, ARRAY_SIZE_X);
    print_array(b, ARRAY_SIZE_X);
    cross_product(a, b, c);
    print_array(c, ARRAY_SIZE_X);
    fprintf(stdout, "\n");
  }
}

void length_tests(int seed) {
  fprintf(stdout, "\nMagnitude test =============================\n");

  // length of array a ...
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int const size = sizeof(a) / sizeof(a[0]);
  fprintf(stdout, "Array a: ");
  print_array(a, size);
  fprintf(stdout, "Magnitude of array a: %10.3f\n", length(a, size));
  // length of array a after reversing ...
  fprintf(stdout, "Array a: ");
  reverse_array(a, size);
  print_array(a, size);
  fprintf(stdout, "Magnitude of array a: %10.3f\n", length(a, size));

  // length of array b ...
  int b[1] = {4};
  fprintf(stdout, "Array b: ");
  print_array(b, 1);
  fprintf(stdout, "Magnitude of array b: %10.3f\n", length(b, 1));
  // length of array b after reversing ...
  fprintf(stdout, "Array b: ");
  reverse_array(b, 1);
  print_array(b, 1);
  fprintf(stdout, "Magnitude of array b: %10.3f\n", length(b, 1));

  // fill array c with random integer values ...
  #define LEN_SIZE 100
  int c[LEN_SIZE];
  srand(seed);
  for (int i = 0; i < REV_SIZE; i++) {
    c[i] = random_int(1, REV_SIZE);
  }
  fprintf(stdout, "Magnitude of array c: %10.3f\n", length(c, LEN_SIZE));
  fprintf(stdout, "\n");
}

// dot product test with 10 elements
void dot_product_test_small(int seed) {
  #define DP_SMALL 10
  int a[DP_SMALL], b[DP_SMALL];

  srand(seed);
  for (int i = 0; i < DP_SMALL; i++) {
    a[i] = random_int(-5, 5);
    b[i] = random_int(-5, 5);
  }

  fprintf(stdout, "\nDot product test for small-sized arrays:\n");
  fprintf(stdout, "-----------------------------------------\n");
  fprintf(stdout, "Array a:");
  print_array(a, DP_SMALL);
  fprintf(stdout, "Array b:");
  print_array(b, DP_SMALL);

  int product = dot_product(a, b, DP_SMALL);
  fprintf(stdout, "The dot product of a and b is %i\n", product);

  product = dot_product(a, a, DP_SMALL);
  fprintf(stdout, "The dot product of a and a is %i\n", product);

  product = dot_product(b, b, DP_SMALL);
  fprintf(stdout, "The dot product of b and b is %i\n", product);
  fprintf(stdout, "\n");
}

// dot product test with arrays having 100 elements
void dot_product_test_medium(int seed) {
  #define DP_MEDIUM 100
  int a[DP_MEDIUM], b[DP_MEDIUM];

  srand(seed);
  for (int i = 0; i < DP_MEDIUM; i++) {
    a[i] = random_int(-10, 10);
    b[i] = random_int(-10, 10);
  }

  fprintf(stdout, "\nDot product test for medium-sized arrays:\n");
  fprintf(stdout, "-----------------------------------------\n");
  fprintf(stdout, "The original arrays:\n");
  print_array(a, DP_MEDIUM);
  print_array(b, DP_MEDIUM);

  int product = dot_product(a, b, DP_MEDIUM);
  fprintf(stdout, "The dot product of a and b is %i\n", product);

  product = dot_product(a, a, DP_MEDIUM);
  fprintf(stdout, "The dot product of a and a is %i\n", product);

  product = dot_product(b, b, DP_MEDIUM);
  fprintf(stdout, "The dot product of b and b is %i\n", product);
  fprintf(stdout, "\n");
}

// dot product test with arrays having 1000 elements
void dot_product_test_large(int seed) {
  #define DP_LARGE 1000
  int a[DP_LARGE], b[DP_LARGE];

  srand(seed);
  for (int i = 0; i < DP_LARGE; i++) {
    a[i] = random_int(-10, 10);
    b[i] = random_int(-10, 10);
  }

  // Too much to print out
#if 0
  fprintf(stdout, "Array a:\n");
  print_array(a, DP_LARGE);
  fprintf(stdout, "Array b:\n");
  print_array(b, DP_LARGE);
#endif

  fprintf(stdout, "\nDot product test for large-sized arrays:\n");
  fprintf(stdout, "-----------------------------------------\n");

  int product = dot_product(a, b, DP_LARGE);
  fprintf(stdout, "The dot product of a * b is %i", product);
  fprintf(stdout, "\n");
}

