#ifndef Q_H
#define Q_H

/*! 
@file     q.h
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@assignment 8
@date     30/10/2023
@brief    The file contains the declarations of five functions that
          read formatted tsunami data from a file into a structure array,
          prints read data, computes max height of tsunamis, computes
          average height of tsunamis, print height and location of tsunamis
          greater than average height respectively.
*//*______________________________________________________________________*/
#include <stdio.h>

struct Tsunami
{
    int day;
    int month;
    int year;
    int fatalities;
    double wave_height;
    char location[80];
};

/*! 
@brief This function takes in a string file_name, an array of struct
       and maxinum number of tsunami events. It reads tsunami
       events data from file_name and stores the respective data in
       arr.

@param file_name - File to be read
@param arr - Array of struct for data from file to be stored into
@param max_cnt - Maxinum number of tsunami events to be read
@return num_tsunami - Number of tsunami events read from file
*//*______________________________________________________________*/
int read_data(char const *file_name, struct Tsunami *arr, int max_cnt);

/*! 
@brief This function takes in an array of struct, size of the array 
       and a file stream out_stm. It prints all tsunami events data
       stored in the array of struct into out_stm

@param arr - Array of struct for data to be printed
@param size - Size of the array of struct
@param out_stm - Output stream for tsunami events data to be printed
       into.
@return void
*//*______________________________________________________________*/
void print_info(struct Tsunami const *arr, int size, FILE *out_stm);

/*! 
@brief This function takes in an array of struct and size of the
       array. It computes the max height out of all tsunami events
       stored in the array.

@param arr - Array of struct for data to be printed
@param size - Size of the array of struct
@return max_height - Maxinum height of out all tsunami events in arr
*//*______________________________________________________________*/
double get_max_height(struct Tsunami const *arr, int size);

/*! 
@brief This function takes in an array of struct and size of the
       array. It computes the average height of all tsunami events
       stored in the array.

@param arr - Array of struct for data to be printed
@param size - Size of the array of struct
@return average_height - Average height of all tsunami events in arr
*//*______________________________________________________________*/
double get_average_height(struct Tsunami const *arr, int size);

/*! 
@brief This function takes in an array of struct, size of the
       array, a height of tsunami and file stream out_stm. It
       prints the heights and locations of tsunami events with
       height greater than the specified height.

@param arr - Array of struct for data to be printed
@param size - Size of the array of struct
@param height - Height of tsunami to be compared with
@param out_stm - Output stream for tsunami events with heights greater
       than specified height to be printed into.
@return void 
*//*______________________________________________________________*/
void print_height(struct Tsunami const *arr, int size, double height, FILE *out_stm);
#endif
