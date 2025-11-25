/*!
@file     q.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@assignment 10
@date     11/11/2023
@brief    The file contains the definitions of nine functions that
          analyzes an unknown number of course grades stored in a data file. 
*//*______________________________________________________________________*/

#include "q.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double* read_data(char const *file_name, int *ptr_cnt)
{
    // open file to determine the number of values
    FILE* open = fopen(file_name, "r");
    double *values;
    double value;
    int i = 0;

    *ptr_cnt = 0;

    while (fscanf(open, "%lf ", &value) != EOF)
    {
        ++*ptr_cnt;
    }

    fclose(open);

    // reopen file to read the values to allocated heap memory
    FILE* open_again = fopen(file_name, "r");

    // allocate heap memory for x number of values in file
    values = (double*)malloc(sizeof(double)*(*ptr_cnt));

    if (values == NULL)
    {
        return NULL;
    }

    while (fscanf(open_again, "%lf ", &value) != EOF)
    {
        *(values + i) = value;
        i++;
    }
    
    fclose(open_again);
    return values;
}

double max(double const *begin, double const *end)
{
    double max_val;
    max_val = *begin;

    for (int i = 1; i < end-begin; i++)
    {
        if (*(begin + i) > max_val)
        {
            max_val = *(begin + i);
        }
    }
    
    return max_val;
}

double min(double const *begin, double const *end)
{
    double min_val;
    min_val = *begin;

    for (int i = 1; i < end-begin; i++)
    {
        if (*(begin + i) < min_val)
        {
            min_val = *(begin + i);
        }
    }
    
    return min_val;
}

double average(double const *begin, double const *end)
{
    double sum = 0;
    double avg;
    int num_elements = end - begin;

    for (int i = 0; i < num_elements; i++)
    {
        sum += *(begin + i);
    }

    avg = (double)sum / num_elements;

    return avg;
}

double variance(double const *begin, double const *end)
{
    double avg;
    double sum = 0;
    double sigma_square;
    int num_elements = end - begin;

    avg = average(begin, end);

    for (int i = 0; i < num_elements; ++i)
    {
        sum += (*(begin + i)-avg) * (*(begin + i)-avg);
    }
    
    sigma_square = sum / (num_elements-1);

    return sigma_square;
}

double std_dev(double const *begin, double const *end)
{
    double sigma_square;
    double sigma;

    sigma_square = variance(begin, end);
    sigma = sqrt(sigma_square);

    return sigma;
}

double median(double *base, int size)
{
    double med;
    int mid = size/2;
    selection_sort(base, size);

    // even number of elements
    if (size%2 == 0)
    {
        med = (*(base + mid - 1) + *(base + mid)) / 2;
    }
    // odd number of elements
    else
    {
        med = *(base + mid);
    }

    return med;
}

void selection_sort(double *base, int size)
{
    double swap;

    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (*(base + j) < *(base + i))
            {
                swap = *(base + i);
                *(base + i) = *(base + j);
                *(base + j) = swap;
            }
        }
    }
}

void ltr_grade_pctg(double const *begin, double const *end, double *ltr_grades)
{
    int num_grades = end - begin;
    for (int i = 0; i < num_grades; i++)
    {
        if (*(begin + i) >= 90.0)
        {
            ltr_grades[A_GRADE] += (double) 100 / num_grades;
        }
        else if (*(begin + i) >= 80.0 && *(begin + i) < 90.0)
        {
            ltr_grades[B_GRADE] += (double) 100 / num_grades;
        }
        else if (*(begin + i) >= 70.0 && *(begin + i) < 80.0)
        {
            ltr_grades[C_GRADE] += (double) 100 / num_grades;
        }
        else if (*(begin + i) >= 60.0 && *(begin + i) < 70.0)
        {
            ltr_grades[D_GRADE] += (double) 100 / num_grades;
        }
        else
        {
            ltr_grades[F_GRADE] += (double) 100 / num_grades;
        }
    }
}
