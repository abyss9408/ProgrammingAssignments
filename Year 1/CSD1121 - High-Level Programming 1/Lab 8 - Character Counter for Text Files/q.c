/*! 
@file     q.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@lab      8
@date     27/10/2023
@brief    The file contains the definitions of three functions that counts
          frequencies of characters in a text file
*//*______________________________________________________________________*/

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
void initialize(int latin_freq[], int size, int *ctrl_cnt, int *non_latin_cnt)
{
    for (int i = 0; i < size; i++)
    {
        latin_freq[i] = 0;
    }

    *ctrl_cnt = 0;
    *non_latin_cnt = 0;
}

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
void wc(FILE *ifs, int latin_freq[], int *ctrl_cnt, int *non_latin_cnt)
{
    char ch;
    char lower;
    char upper;
    while ((ch = (char)fgetc(ifs)) != EOF)
    {
        lower = 'a';
        upper = 'A';
        // if read character is latin alphabet
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {            
            for (int i = 0; i < 26; ++i)
            {
                if (ch==lower || ch==upper)
                {
                    ++latin_freq[i];
                    break;
                }
                else
                {
                    ++lower;
                    ++upper;
                }
            }
        }
        // if read character is a control character
        else if (ch == '\a' || ch == '\b' || ch == '\f' || ch == '\n' || ch == '\r' || ch == '\t' || ch == '\v')
        {
            ++*ctrl_cnt;
        }
        // non latin characters
        else
        {
            ++*non_latin_cnt;
        }
    }
}

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
void print_freqs(int const latin_freq[], int size, int const *ctrl_cnt, int const *non_latin_cnt)
{
    int sum_latin_freq = 0;
    for (char lower = 'a'; lower <= 'z'; ++lower)
    {
        printf("%-10c", lower);
    }
    printf("\n");
    for (int i = 0; i < size; ++i)
    {
        sum_latin_freq += latin_freq[i];
        printf("%-10d", latin_freq[i]);
    }
    printf("\n");
    printf("\n");
    printf("Latin Letters     :%8d\n", sum_latin_freq);
    printf("Non-Latin Letters :%8d\n", *non_latin_cnt);
    printf("Control Letters   :%8d\n", *ctrl_cnt);
}

// For each function -

// Add documentation [for yourself and not for grading] for the function ...
