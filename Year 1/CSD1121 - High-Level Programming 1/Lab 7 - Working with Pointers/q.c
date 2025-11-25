/*! 
@file     q.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@lab      7
@date     20/10/2023
@brief    The file contains the definitions of five functions that find
          the 3rd greatest integer number in an input sequence provided
          by the user.
*//*______________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>

/*! 
@brief This function takes in an array of type double and the
       maxinum size of the array, returns the number of values
       in the array.

@param void
@return result - total count of numbers in the input sequence
*//*______________________________________________________________*/
size_t read_total_count(void)
{
    size_t value;

    printf("Please enter the number of integers: ");
    scanf("%lu", &value);
    if (value < 3)
    {
        printf("There is no third largest number.\n");
        exit(EXIT_FAILURE);
    }

    return value;
}

/*! 
@brief This function takes in 3 pointers to int and reads the first
       numbers into them

@param *first - Pointer to first number
@param *second - Pointer to second number
@param *third - Pointer to third number
@return void
*//*______________________________________________________________*/
void read_3_numbers(int *first, int *second, int *third)
{
    scanf("%d %d %d", first, second, third);
}

/*! 
@brief This function takes in 2 pointers to int and swap the values 
       that they point to

@param *lhs - Pointer to left hand side number
@param *rhs - Pointer to right hand side number
@return void
*//*______________________________________________________________*/
void swap(int *lhs, int *rhs)
{
    int swap;
    swap = *lhs;
    *lhs = *rhs;
    *rhs = swap;
}

/*! 
@brief This function takes in 3 pointers to int and sorts the
       the values pointed to by them, *first will become the
       largest, *second will become the second largest and
       *third will become the third largest

@param *first - Pointer to first number
@param *second - Pointer to second number
@param *third - Pointer to third number
@return void
*//*______________________________________________________________*/
void sort_3_numbers(int *first, int *second, int *third)
{
    if (*second > *first)
    {
        swap(first, second);
    }
    if (*third > *first)
    {
        swap(first, third);
    }
    if (*third > *second)
    {
        swap(second, third);
    }
    
}

/*! 
@brief This function takes in 3 pointers to int and a number other
       than the first three in the input sequence. It compares
       the number's value to the values pointed to by the parameters
       and if necessary assigns the number's value to one of the
       values pointed to by the parameters so that the relative
       ordering of the int values pointed to by the parameters is
       maintained when the function returns

@param number - Number other than the first three
@param *first - Pointer to first number
@param *second - Pointer to second number
@param *third - Pointer to third number
@return void
*//*______________________________________________________________*/
void maintain_3_largest(int number, int *first, int *second, int *third)
{
    if (number > *first)
    {
        *third = *second;
        *second = *first;
        *first = number;
    }
    else if (number > *second)
    {
        *third = *second;
        *second = number;
    }
    else if (number > *third)
    {
        *third = number;
    }
}
