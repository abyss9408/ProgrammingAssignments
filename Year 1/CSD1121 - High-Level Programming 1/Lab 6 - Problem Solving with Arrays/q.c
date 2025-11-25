/*! 
@file     q.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@lab      6
@date     10/10/2023
@brief    The file contains the definitions of six functions that compute
          data of arrays
*//*______________________________________________________________________*/

#include <stdio.h>
#include <math.h>

/*! 
@brief This function takes in an array of type double and the
       maxinum size of an array that can be read, returns the
       number of values in the array.

@param array[] - Array to be read
@param max_array_size - Maxinum size of array that can be read
@return i - Number of values in the array
*//*______________________________________________________________*/
int read_data(double array[], int max_array_size)
{
    int i = 0;
    double num;
    while ((scanf("%lf", &num) != EOF) && i < max_array_size)
    {
        array[i++] = num;
    }

    return i;
}

/*! 
@brief This function takes in an array of type double and the
       size of the array, returns the index of the maxinum value
       in the array.

@param arr[] - Array to be looped through
@param size - Size of array
@return max_index - Index of the maxinum value in the array
*//*______________________________________________________________*/
int max_index(double const arr[], int size)
{
    double max_val;
    int max_index = 0;
    max_val = arr[max_index];
    for (int i = 1; i < size; ++i)
    {
        if (arr[i] > max_val)
        {
            max_val = arr[i];
            max_index = i;
        }
    }
    
    return max_index;
}

/*! 
@brief This function takes in an array of type double and the
       size of the array, returns the index of the minimum value
       in the array.

@param arr[] - Array to be looped through
@param size - Size of array
@return min_index - Index of the minimum value in the array
*//*______________________________________________________________*/
int min_index(double const arr[], int size)
{
    double min_val;
    int min_index = 0;
    min_val = arr[min_index];
    for (int i = 1; i < size; ++i)
    {
        if (arr[i] < min_val)
        {
            min_val = arr[i];
            min_index = i;
        }
    }
    
    return min_index;
}

/*! 
@brief This function takes in an array of type double and the
       number of values in the array, computes the mean of the
       values in the array.

@param arr[] - Array to be looped through
@param size - Number of values in array
@return avg - Mean of the values in array
*//*______________________________________________________________*/
double mean(double const arr[], int n)
{
    double sum = 0;
    double avg;
    for (int i = 0; i < n; ++i)
    {
        sum += arr[i];
    }

    avg = (double)sum/n;

    return avg;
}

/*! 
@brief This function takes in an array of type double and the
       size of the array, computes the variance of the
       values in the array.

@param arr[] - Array to be looped through
@param size - Size of array
@return sigma_square - Variance of the values in array
*//*______________________________________________________________*/
double variance(double const arr[], int size)
{
    double avg;
    double sum = 0;
    double sigma_square;
    avg = mean(arr, size);

    for (int i = 0; i < size; ++i)
    {
        sum += (arr[i]-avg) * (arr[i]-avg);
    }
    
    sigma_square = sum / (size-1);

    return sigma_square;
}

/*! 
@brief This function takes in an array of type double and the
       size of the array, computes the standard deviation of the
       values in array

@param arr[] - Array to be looped through
@param size - Size of array
@return sigma - Standard deviation of the values in array
*//*______________________________________________________________*/
double std_dev(double const arr[], int size)
{
    double sigma_square;
    double sigma;
    sigma_square = variance(arr, size);
    sigma = sqrt(sigma_square);

    return sigma;
}
