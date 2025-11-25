/*! 
@file     q.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@assignment 8
@date     30/10/2023
@brief    The file contains the definitions of five functions that
          read formatted tsunami data from a file into a structure array,
          prints read data, computes max height of tsunamis, computes
          average height of tsunamis, print height and location of tsunamis
          greater than average height respectively.
*//*______________________________________________________________________*/

#include <stdio.h>
#include "q.h"

int read_data(char const *file_name, struct Tsunami *arr, int max_cnt)
{
    FILE *in_stm = fopen(file_name, "r");
    int num_tsunami = 0;
    if (in_stm != NULL)
    {
        for (int i = 0; i < max_cnt; i++)
        {
            if(fscanf(in_stm, "%d %d %d %d %lf %[^\n]",
                &arr[i].day,
                &arr[i].month,
                &arr[i].year,
                &arr[i].fatalities,
                &arr[i].wave_height,
                arr[i].location) != EOF)
            {
                num_tsunami++;
            }
        }
              
        fclose(in_stm);
        return num_tsunami;
        
    }
    else
    {
        printf("File does not exist\n");
        return -1;
    }
}

void print_info(struct Tsunami const *arr, int size, FILE *out_stm)
{
    for (int i = 0; i < size; i++)
    {
        fprintf(out_stm, "%02d %02d %4d %6d %5.2lf %s\n", 
            arr[i].day,
            arr[i].month,
            arr[i].year,
            arr[i].fatalities,
            arr[i].wave_height,
            arr[i].location);
    }   
}

double get_max_height(struct Tsunami const *arr, int size)
{
    double max_height = arr[0].wave_height;
    for (int i = 1; i <= size; i++)
    {
        if (arr[i].wave_height > max_height)
        {
            max_height = arr[i].wave_height;
        }      
    }  
    return max_height;
}

double get_average_height(struct Tsunami const *arr, int size)
{
    double sum_height = 0;
    double average_height;
    for (int i = 0; i < size; i++)
    {
        sum_height += arr[i].wave_height;      
    }
    average_height = sum_height / size;  
    return average_height;
}

void print_height(struct Tsunami const *arr, int size, double height, FILE *out_stm)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i].wave_height > height)
        {
            fprintf(out_stm, "%5.2lf %s\n", arr[i].wave_height, arr[i].location);
        }
    }
}
