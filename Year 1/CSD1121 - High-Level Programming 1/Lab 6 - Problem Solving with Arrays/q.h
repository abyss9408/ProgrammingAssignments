/*! 
@file     q.h
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@lab      6
@date     10/10/2023
@brief    The file contains the declarations of six functions that compute
          data of arrays
*//*______________________________________________________________________*/

/*! 
@brief This function takes in an array of type double and the
       maxinum size of the array, returns the number of values
       in the array.

@param array[] - Array to be read
@param max_array_size - Maxinum size of array that can be read
@return i - Number of values in the array
*//*______________________________________________________________*/
int read_data(double array[], int max_array_size);

/*! 
@brief This function takes in an array of type double and the
       size of the array, returns the index of the maxinum value
       in the array.

@param arr[] - Array to be looped through
@param size - Size of array
@return max_index - Index of the maxinum value in the array
*//*______________________________________________________________*/
int max_index(double const arr[], int size);

/*! 
@brief This function takes in an array of type double and the
       size of the array, returns the index of the minimum value
       in the array.

@param arr[] - Array to be looped through
@param size - Size of array
@return min_index - Index of the minimum value in the array
*//*______________________________________________________________*/
int min_index(double const arr[], int size);

/*! 
@brief This function takes in an array of type double and the
       number of values in the array, computes the mean of the
       values in the array.

@param arr[] - Array to be looped through
@param size - Number of values in array
@return avg - Mean of the values in array
*//*______________________________________________________________*/
double mean(double const arr[], int n);

/*! 
@brief This function takes in an array of type double and the
       size of the array, computes the variance of the
       values in the array.

@param arr[] - Array to be looped through
@param size - Size of array
@return sigma_square - Variance of the values in array
*//*______________________________________________________________*/
double variance(double const[], int size);

/*! 
@brief This function takes in an array of type double and the
       size of the array, computes the standard deviation of the
       values in the array

@param arr[] - Array to be looped through
@param size - Size of array
@return sigma_square - Variance of the values in array
*//*______________________________________________________________*/
double std_dev(double const[], int size);