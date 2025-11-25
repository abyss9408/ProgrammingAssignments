/*!
@file     q.h
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@assignment 10
@date     11/11/2023
@brief    The file contains the declarations of nine functions that
          analyzes an unknown number of course grades stored in a data file. 
*//*______________________________________________________________________*/

#ifndef Q_H
#define Q_H

enum {
    A_GRADE,
    B_GRADE,
    C_GRADE,
    D_GRADE,
    F_GRADE,
    TOT_GRADE
};

/*!
@brief This function takes in a file name and a pointer to number
       of values in the file. It opens a text filee, determines the
       number of double-precision floating-point values in the file
       and writes the count to the location pointed to by parameter
       ptr_cnt. Next, it allocates the exact amount of heap memory
       to contain these values and copies the values from file to
       this heap memory. If successful, it returns the ddress of
       the first byte of allocated heap memory. Otherwise, it
       returns NULL.

@param file_name - Name of the file to be read
@param ptr_cnt - Pointer to number of values in file
@return double* - Address of the first byte of allocated heap
                  memory containing the values read from the file
                  or NULL if the allocation is unsuccessful.
*//*______________________________________________________________*/
double* read_data(char const *file_name, int *ptr_cnt);

/*!
@brief This function takes in a pointer to start of a half-open
       range of values and another that points to the end of it.
       It returns the maximum value in the range of values.

@param begin - Pointer to start of range
@param end - Pointer to end of range
@return double - Maxinum value in the range
*//*______________________________________________________________*/
double max(double const *begin, double const *end);

/*!
@brief This function takes in a pointer to start of a half-open
       range of values and another that points to the end of it.
       It returns the minimum value in the range of values.

@param begin - Pointer to start of range
@param end - Pointer to end of range
@return double - Minimum value in the range
*//*______________________________________________________________*/
double min(double const *begin, double const *end);

/*!
@brief This function takes in a pointer to start of a half-open
       range of values and another that points to the end of it.
       It returns the average of the range of values.

@param begin - Pointer to start of range
@param end - Pointer to end of range
@return double - Average of the range
*//*______________________________________________________________*/
double average(double const *begin, double const *end);

/*!
@brief This function takes in a pointer to start of a half-open
       range of values and another that points to the end of it.
       It returns the variance of the range of values.

@param begin - Pointer to start of range
@param end - Pointer to end of range
@return double - Variance of the range
*//*______________________________________________________________*/
double variance(double const *begin, double const *end);

/*!
@brief This function takes in a pointer to start of a half-open
       range of values and and another that points to the end of it.
       It returns the standard Deviation of the range of values.

@param begin - Pointer to start of range
@param end - Pointer to end of range
@return double - Standard Deviation of the range
*//*______________________________________________________________*/
double std_dev(double const *begin, double const *end);

/*!
@brief This function takes in a pointer to start of a half-open
       range of values and and its size. It returns the median of
       the range of values.

@param base - Pointer to start of range
@param size - Number of values in the range
@return double - Median of the range
*//*______________________________________________________________*/
double median(double *base, int size);

/*!
@brief This function takes in a pointer to start of a half-open
       range of values and and its size. It sorts the values in
       the range in ascending order.

@param base - Pointer to start of range
@param size - Number of values in the range
@return void
*//*______________________________________________________________*/
void selection_sort(double *base, int size);

/*!
@brief This function takes in a pointer to start of a half-open
       range of values and another that points to the end of it
       as well as an array that contains percentages of grades.
       It determines the percentage of values in the ange that
       map to a letter grade and writes these percentages to the
       array whose first element is specified by parameter ltr_grades.
       
@param begin - Pointer to start of range
@param end - Pointer to end of range
@param ltr_grades - Array that contains percentages of grades
@return void
*//*______________________________________________________________*/
void ltr_grade_pctg(double const *begin, double const *end, double *ltr_grades);

#endif // #ifndef Q_H
