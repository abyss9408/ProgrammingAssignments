/*! 
@file     q.h
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@lab      10
@date     10/11/2023
@brief    The file contains the declarations of four functions that that
          tests strings representing directory paths and two functions that
          prints debug info about memory allocation and deallocation as well
          as allocating/deallocating memory.
*//*______________________________________________________________________*/

#ifndef Q_H
#define Q_H
#include <stdio.h>

#ifdef USE_STRING

#include <string.h>

#define STRLEN strlen
#define STRCPY strcpy
#define STRCAT strcat
#define STRCMP strcmp
#define STRSTR strstr

#else

#include "my_string.h"

#define STRLEN my_strlen
#define STRCPY my_strcpy
#define STRCAT my_strcat
#define STRCMP my_strcmp
#define STRSTR my_strstr


#endif

/*! 
@brief This function takes in the number of bytes of memory to be
       allocated and prints the number.
@param size - Number of bytes of memory to be allocated
@return void
*//*______________________________________________________________*/
void* debug_malloc(
    size_t size
);

/*! 
@brief This function takes in a pointer to a memory block previously
       allocated with malloc, calloc or realloc and deallocates it
       as well as printing info that the memory block is deallocated
       sucessfully.
@param ptr - Pointer to a memory block to be deallocated
@return void
*//*______________________________________________________________*/
void debug_free(
    void* ptr
);

/*! 
@brief The function takes in a path to a parent folder, a path
       separator sequence, and an array of subdirectories with its
       element count. It combines the parent folder and the
       subdirectories into a single path using the separator. It
       returns the combined file path.

@param parent - Path to parent folder
@param separator - Path seperator sequence
@param folders - Array of subdirectories
@param count - Number of subdirectories
@return const char* - Combined file path
*//*______________________________________________________________*/
const char* build_path(
    const char* parent,
    const char* separator,
    const char* const folders[],
    size_t count
);

/*! 
@brief This function takes in two strings, lhs and rhs. It prints
       out a statement about a 3-way comparison of lhs and rhs.

@param lhs - First string to be compared
@param rhs - Second string to be compared
@return void
*//*______________________________________________________________*/
void compare_string(
    const char* lhs,
    const char* rhs
);

/*! 
@brief This function takes in a string of text. It prints the length
       of the it.

@param text - String to be computed
@return void
*//*______________________________________________________________*/
void describe_string(
    const char* text
);

/*! 
@brief This function takes in a string and a substring. It prints
       out a statement describing a result for searching for
       substring within string.

@param string - String to be scanned
@param substring - String containing the sequence of characters to match
@return void
*//*______________________________________________________________*/
void find_string(
    const char* string,
    const char* substring
);
#endif
