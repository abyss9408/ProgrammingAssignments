/*
* qdriver.c - driver source file for tutorial on "introduction to arrays"
* that contains definition of function main.
* 
* Function main assumes an input text containing data values between 0.0
* and 1000.0 is redirected to standard input stream.
* Further, function main calls function read_data to store the data values
* in standard input stream into an array.
* Next, the function calls the statistical functions declared in q.h
* and prints the return values from these functions to standard output.
*
* Notice that function main checks for malformed input.
* a) If function read_data returns a value 0 [indicating the file is empty
* or contains non-numerical data], there's nothing to do and the program 
* shuts down.
* b) If function read_data returns a value larger than SIZE, it means
* read_data has read more values than can be stored in array grades.
* Rather than have the program behave in an unspecified manner, the
* program is shut down.
* 
* Prasanna Ghali
* Original program written: 02/14/2016
* written for High-Level Programming I
*/
#include <stdio.h>
#include "q.h"

// maximum number of data values that can be stored in array
#define SIZE 1000

int main(void) {
  // define an array to store a maximum of SIZE number of doubles.
  double grades[SIZE];
  // fill the array with grades from standard input file stream with
  // variable npts containing the number of values
  int const npts = read_data(grades, SIZE);
  
  // if the input file stream is empty, there's no data to process ...
  if (npts == 0) {
    fprintf(stdout, "There are no grades to process!!!\n");
    fprintf(stdout, "Shutting program down ...\n");
    return 0;
  }
  // or, if function read_data has erroneously read more than SIZE values,
  // it is better to shut the program down. Otherwise, the program will
  // access out-of-bounds array elements.
  if (npts > SIZE) {
    fprintf(stdout, "You've read more values %d than max array size\n", npts);
    fprintf(stdout, "Shutting program down ...\n");
    return 0;
  }

  // now, print the various summary statistics defined by student in q.c ...
  fprintf(stdout, "Size of data set  : %11d\n",   npts);
  fprintf(stdout, "Maximum grade     : %11.3f\n", grades[max_index(grades, npts)]);
  fprintf(stdout, "Minimum grade     : %11.3f\n", grades[min_index(grades, npts)]);
  fprintf(stdout, "Mean    grade     : %11.3f\n", mean(grades, npts));
  fprintf(stdout, "Variance          : %11.3f\n", variance(grades, npts));
  fprintf(stdout, "Standard deviation: %11.3f\n", std_dev(grades, npts));

  return 0;
}
