/*! 
@file     q.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@assignment 9
@date     08/11/2023
@brief    The file contains the definitions of seven functions that
          scan through bytes performing various operations,
*//*______________________________________________________________________*/

#define NULL ((void*)0) 

char const* find(char const *begin, char const *end, char val)
{
    for (int i = 0; *(begin + i) != *(end); i++)
    {
        if (*(begin+i) == val)
        {
            return begin + i;
        }
    }

    return NULL;
}

char const* find_any(char const *begin, char const *end,
                     char const *vals, int len)
{
    for (int j = 0; *(begin + j) != *(end); j++)
    {
        for (int i = 0; i < len; i++)
        {
            if (*(begin+j) == *(vals+i))
            {
                return begin + j;
            }
        }
    }

    return NULL;
}

int count(char const *begin, char const *end, char val)
{
    int count_elements = 0;
    for (int i = 0; *(begin + i) != *(end); i++)
    {
        if (*(begin+i) == val)
        {
            ++count_elements;
        }
    }

    return count_elements;
}

int count_any(char const *begin, char const *end, char const *vals, int len)
{
    int count_elements = 0;
    for (int j = 0; *(begin + j) != *(end); j++)
    {
        for (int i = 0; i < len; i++)
        {
            if (*(begin+j) == *(vals+i))
            {
                ++count_elements;
            }
        }
    }

    return count_elements;
}

int compare(char const *begin1, char const *begin2, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (*(begin1+i) < *(begin2+i))
        {
            return -1;
        }
        else if (*(begin1+i) > *(begin2+i))
        {
            return 1;
        }
    }

    return 0;
}

void exchange(char *begin1, char *begin2, int len)
{
    char tmp;
    for (int i = 0; i < len; i++)
    {
        tmp = *(begin1+i);
        *(begin1+i) = *(begin2+i);
        *(begin2+i) = tmp;
    }
}

void copy(char *dst, char *src, int len)
{
    // Copy char values from last to first
    for (int i = len-1; i >= 0; i--)
    {
        *(dst+i) = *(src+i);
    }
}
