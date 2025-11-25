/*! 
@file     q.h
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@lab      8
@date     27/10/2023
@brief    The file contains the declarations of three functions that counts
          frequencies of characters in a text file
*//*______________________________________________________________________*/
#ifndef QH
#define QH

#include <stdio.h>
/*! 
@brief This function takes in an array of type int, size of the
       array and two pointers to int. It initializes all latin_freq
       elements to 0 as well as values pointed to by *ctrl_cnt and
       *non_latin_cnt to 0.

@param latin_freq - Address holder for array the stores the number
       of each respective latin character
@param size - size of latin_freq
@param *ctrl_cnt - Pointer to int that holds the number of control
       charcters
@param *non_latin_cnt - Pointer to int that holds the number of
       non-latin characters
@return void
*//*______________________________________________________________*/
void initialize(int latin_freq[], int size, int *ctrl_cnt, int *non_latin_cnt);

/*! 
@brief This function takes in a FILE pointer, an array of type int
       and two pointers to int. It computes the number of respective
       latin charcters, control characters and non-latin characters
       inside a text file.

@param ifs - FILE pointer that holds the input stream of text file
@param latin_freq - Address holder for array the stores the number
       of each respective latin character
@param *ctrl_cnt - Pointer to int that holds the number of control
       charcters
@param *non_latin_cnt - Pointer to int that holds the number of
       non-latin characters
@return void
*//*______________________________________________________________*/
void wc(FILE *ifs, int latin_freq[], int *ctrl_cnt, int *non_latin_cnt);

/*! 
@brief This function takes in an array of type int, size of the
       array and two pointers to int. It prints out the number of
       respective latin charcters, control characters, non-latin
       characters and total number of latin characters in a text
       file.

@param latin_freq - Address holder for array the stores the number
       of each respective latin character
@param size - size of latin_freq
@param *ctrl_cnt - Pointer to int that holds the number of control
       charcters
@param *non_latin_cnt - Pointer to int that holds the number of
       non-latin characters
@return void
*//*______________________________________________________________*/
void print_freqs(int const latin_freq[], int size, int const *ctrl_cnt, int const *non_latin_cnt);
#endif
