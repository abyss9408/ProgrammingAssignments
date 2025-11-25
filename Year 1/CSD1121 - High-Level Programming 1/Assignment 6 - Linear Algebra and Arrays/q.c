/*! 
@file     q.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@assignment 6
@date     20/10/2023
@brief    The file contains the definitions of six functions that
          manipulate arrays using linear algebraic functions
*//*______________________________________________________________________*/

#include <math.h>

/*! 
@brief This function takes in an array and its size.
       It reverses the order of the array

@param a[] - Array to be reversed
@param size - Size of the array
@return void
*//*______________________________________________________________*/
void reverse_array(int a[], int size)
{
    int swap;
    for (int i = 0; i < size/2; ++i)
    {
        swap = a[i];
        a[i] = a[size-i-1];
        a[size-i-1] = swap;
    }
}

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
void add_arrays(int const a[], int const b[], int c[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        c[i] = a[i] + b[i];
    }
}

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
void scalar_multiply(int a[], int size, int multiplier)
{
    for (int i = 0; i < size; ++i)
    {
        a[i] *= multiplier;
    }
}

/*! 
@brief This function takes in two arrays and the size of the
       arrays and a multiplier. It computes the dot product of
       the arrays and returns the result

@param a[] - First array
@param b[] - Second array
@param size - Size of the arrays
@return result - Dot product of the arrays
*//*______________________________________________________________*/
int dot_product(int const a[], int const b[], int size)
{
    int result = 0;
    for (int i = 0; i < size; ++i)
    {
        result += a[i]*b[i];
    }

    return result;
}

/*! 
@brief This function takes in three arrays. It computes the cross
       product of the first two arrays and places it into the
       third array

@param a[] - First array
@param b[] - Second array
@param c[] - Third array
@return void
*//*______________________________________________________________*/
void cross_product(int const a[], int const b[], int c[])
{
    c[0] = a[1]*b[2] - a[2]*b[1];
    c[1] = -(a[0]*b[2] - a[2]*b[0]);
    c[2] = a[0]*b[1] - a[1]*b[0];
}

/*! 
@brief This function takes in an array and its size. It computes
       and returns the magnitude of the array

@param a[] - Array to be computed
@param size - Size of the array
@return result - Magnitude of the array
*//*______________________________________________________________*/
double length(int const a[], int size)
{
    int sum = 0;
    double result;
    for (int i = 0; i < size; ++i)
    {
        sum += a[i]*a[i];
    }
    result = sqrt((double)sum);
    return result;
}
