/*! 
@file     q.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@lab      10
@date     10/11/2023
@brief    The file contains the definitions of four functions that tests
          strings representing directory paths
*//*______________________________________________________________________*/

#include "q.h"

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
const char* build_path(const char* parent, const char* separator, 
    const char* const folders[], size_t count)
{
    size_t folders_len = 0;
    for (size_t i = 0; i < count; i++)
    {
        folders_len += STRLEN(folders[i]);
    }

    char* file_path = (char*)debug_malloc(folders_len + STRLEN(parent) + STRLEN(separator)*count + 1);
    STRCPY(file_path, parent);
    for (size_t i = 0; i < count; i++)
    {
        STRCAT(file_path, folders[i]);
        STRCAT(file_path, separator);
    }
    
    return file_path;
}

/*! 
@brief This function takes in two strings lhs and rhs. It prints
       out a statement about a 3-way comparison of lhs and rhs.

@param lhs - First string to be compared
@param rhs - Second string to be compared
@return void
*//*______________________________________________________________*/
void compare_string(const char* lhs, const char* rhs)
{
    int cmp = STRCMP(lhs, rhs);
    if (cmp < 0)
    {
        printf("Left string goes first.\n");
    }
    else if (cmp > 0)
    {
        printf("Right string goes first.\n");
    }
    else
    {
        printf("Both strings are equal.\n");
    }
}

/*! 
@brief This function takes in a string of text. It prints the length
       of the it.

@param text - String to be computed
@return void
*//*______________________________________________________________*/
void describe_string(const char* text)
{
    int len = (int)STRLEN(text);
    printf("The length of the path \"%s\" is %d.\n", text, len);
}

/*! 
@brief This function takes in a string and a substring. It prints
       out a statement describing a result for searching for
       substring within string.

@param string - String to be scanned
@param substring - String containing the sequence of characters to match
@return void
*//*______________________________________________________________*/
void find_string(const char* string, const char* substring)
{
    char* result = STRSTR(string, substring);
    int substring_len = (int)STRLEN(substring);
    printf("Searching for a string:\n");
    printf("\tText:     %s\n", string);
    printf("\tSub-text: %s\n", substring);
    if (result != NULL)
    {
        printf("\tResult:   found %d characters at a position %ld.\n", substring_len, result-string);
    }
    else
    printf("\tResult:   not found\n");
}