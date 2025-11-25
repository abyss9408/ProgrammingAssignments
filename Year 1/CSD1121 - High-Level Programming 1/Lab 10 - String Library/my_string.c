/*! 
@file     my_strings.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@lab      10
@date     10/11/2023
@brief    The file contains the definitions of five functions that are
          similar to some of those in string.h
*//*______________________________________________________________________*/

#include <stddef.h>

/*! 
@brief This function takes in a string str and returns the number of
       chars in str, not including the null char.

@param str - String to be computed
@return size_t - Number of chars in str, not including the null char.
*//*______________________________________________________________*/
size_t my_strlen(const char* str)
{
    size_t len = 0;
    
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        len++;
    }

    return len;
}

/*! 
@brief This function takes in two strings dest and src. It copies
       the chars(including null character) in src to dest and returns
       dest.

@param src - String to be copied
@param dest - Destination of copy
@return char* - dest
*//*______________________________________________________________*/
char* my_strcpy(char* dest, const char* src)
{
    size_t i;
    for (i = 0; ; i++)
    {
        dest[i] = src[i];
        if (dest[i] == '\0')
        break;
    }

    return dest;
}

/*! 
@brief This function takes in two strings dest and src. It
       contenates both strings by replacing the null character in
       dest with src and returns dest

@param src - String to be appended to dest
@param dest - Destination of append
@return char* - dest
*//*______________________________________________________________*/
char* my_strcat(char* dest, const char* src)
{
    size_t null_i;
    // identify position of null char in dest
    for (size_t i = 0; ; i++)
    {
        if (dest[i] == '\0')
        {
            null_i = i;
            break;
        }
    }

    for (size_t src_i = 0, dest_i = null_i; ; src_i++, dest_i++)
    {
        dest[dest_i] = src[src_i];
        if (dest[dest_i] == '\0')
        break;
    }
    return dest;
}

/*! 
@brief This function takes in two strings lhs and rhs. It
       compares both strings by comparing each corresponding
       char. It returns the difference in ASCII value between the
       first pair of characters that does not match or 0 if both
       strings are equal.

@param lhs - First string to be compared
@param rhs - Second string to be compared
@return int - Difference in ASCII value between the first pair of
        characters that does not match or 0 if both strings are
        equal.
*//*______________________________________________________________*/
int my_strcmp(const char* lhs, const char* rhs)
{
    int result = 0;
    for (size_t i = 0; lhs[i] != '\0' || rhs[i] != '\0'; i++)
    {
        if (lhs[i] != rhs[i])
        {
            result = lhs[i] - rhs[i];
            break;
        }
    }

    return result;
}

/*! 
@brief This function takes in two strings str and substr. It
       looks for the first occurance of substr in str and returns
       the pointer to it or NULL if substr is not found in str.

@param str - String to be scanned
@param substr - String containing the sequence of characters to match
@return char* - Pointer to the first occurance of substr in str or
        NULL if substr is not found in str
*//*______________________________________________________________*/
char* my_strstr(const char* str, const char* substr)
{
    int found = 0;
    int found_index;
    int str_i = 0;
    int sub_i = 0;
    
    while (str[str_i] != '\0')
    {
        // first occurance of first char of substr is found in str
        if (str[str_i] == substr[sub_i])
        {
          found_index = str_i;
          found = 1;
          while (substr[sub_i] != '\0')
          {
            // any of the following chars in sub not found in str
            if (str[str_i] != substr[sub_i])
            {
              sub_i = 0;
              found = 0;
              break;
            }
            sub_i++;
            str_i++;
          }
          
        }
        str_i++;
    }
    
    if (found)
    return (char*)str + found_index;
    else
    return NULL;
}
