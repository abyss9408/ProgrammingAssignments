/*! 
@file     q.h
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@assignment 6
@date     20/10/2023
@brief    The file contains the declarations of six functions that
          manipulate arrays using linear algebraic functions
*//*______________________________________________________________________*/

#ifndef QH
#define QH

/*! 
@brief This function takes in an array and its size.
       It reverses the order of the array

@param a[] - Array to be reversed
@param size - Size of the array
@return void
*//*______________________________________________________________*/
void reverse_array(int a[], int size);

/*! 
@brief This function takes in three arrays and the size of the
       arrays. It adds elements of first two arrays and put the
       sum in third array

@param a[] - First array
@param b[] - Second array
@param c[] - Third array that will contain the sum of the elements
       of first and second arrays
@param size - Size of the arrays
@return void
*//*______________________________________________________________*/
void add_arrays(int const a[], int const b[], int c[], int size);

/*! 
@brief This function takes in an array, the size of the
       arrays and a multiplier. It multiplies each element by
       the multiplier

@param a[] - Array to be scalar multiplied
@param size - Size of the array
@param multiplier - Scalar that each element of the array will be
       multiplied by
@return void
*//*______________________________________________________________*/
void scalar_multiply(int a[], int size, int multiplier);

/*! 
@brief This function takes in two arrays and the size of the
       arrays and a multiplier. It computes the dot product of
       the arrays and returns the result

@param a[] - First array
@param b[] - Second array
@param size - Size of the arrays
@return result - Dot product of the arrays
*//*______________________________________________________________*/
int dot_product(int const a[], int const b[], int size);

/*! 
@brief This function takes in three arrays. It computes the cross
       product of the first two arrays and places it into the
       third array

@param a[] - First array
@param b[] - Second array
@param c[] - Third array
@return void
*//*______________________________________________________________*/
void cross_product(int const a[], int const b[], int c[]);

/*! 
@brief This function takes in an array and its size. It computes
       and returns the magnitude of the array

@param a[] - Array to be computed
@param size - Size of the array
@return result - Magnitude of the array
*//*______________________________________________________________*/
double length(int const a[], int size);

#endif
