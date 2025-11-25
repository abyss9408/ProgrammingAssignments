/*! 
@file     q.h
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@assignment 9
@date     08/11/2023
@brief    The file contains the declarations of seven functions that
          scan through bytes performing various operations,
*//*______________________________________________________________________*/

/*! 
@brief This function takes in two pointers to const char begin and
       end as well as a char val. It returns a pointer to the first
       occurance of val in a half-open range of values. It returns
       NULL if val is not found.

@param begin - Pointer to start of array
@param end - Pointer to end of array
@param val - char to be searched for
@return char const* - pointer to first occurrence of val or NULL
        if val is not found.
*//*______________________________________________________________*/
char const* find(char const *begin, char const *end, char val);

/*! 
@brief This function takes in two pointers to const char begin and
       end, an array of chars val as well as the number of elements
       in vals. It returns a pointer to the first occurance of any
       member vals in a half-open range of values or NULL if none
       of the members of vals are found.

@param begin - Pointer to start of array
@param end - Pointer to end of array
@param vals - Array of chars to be searched for
@param len - Number of elements in vals (excluding NULL char)
@return char const* - pointer to first occurrence of any member of
        val or NULL if none of the members of val is found.
*//*______________________________________________________________*/
char const* find_any(char const *begin, char const *end,
                     char const *vals, int len);

/*! 
@brief This function takes in two pointers to const char begin and
       end as well as a char val. It returns the number of elements
       equivalent to val.

@param begin - Pointer to start of array
@param end - Pointer to end of array
@param val - char to be searched for
@return int - Number of elements equivalent to val
*//*______________________________________________________________*/
int count(char const *begin, char const *end, char val);

/*! 
@brief This function takes in two pointers to const char begin and
       end, an array of chars val as well as the number of elements
       in vals. It returns the number of elements equivalent to any
       member of vals.

@param begin - Pointer to start of array
@param end - Pointer to end of array
@param vals - Array of chars to be searched for
@param len - Number of elements in vals (excluding NULL char)
@return int - Number of elements equivalent to val
*//*______________________________________________________________*/
int count_any(char const *begin, char const *end, char const *vals, int len);

/*! 
@brief This function takes in two pointers to const char begin1 and
       begin2 as well as the number of elements in both arrays.
       It returns 0 if contents of both arrays are exactly similar,
       negative value if an element in array1 has a smaller value
       than the corresponding element in array2. Otherwise, it
       returns a positive value

@param begin1 - Pointer to start of array1
@param begin2 - Pointer to start of array2
@param len - Number of values in both arrays
@return int - 0 if contents of both arrays are exactly
        similar, negative value if an element in array1 has a
        smaller value than the corresponding element in array2.
        Otherwise, it returns a positive value.
*//*______________________________________________________________*/
int compare(char const *begin1, char const *begin2, int len);

/*! 
@brief This function takes in two pointers to char begin1 and
       begin2 as well as the number of elements in both arrays.
       It swaps the values in both arrays.

@param begin1 - Pointer to start of array1
@param begin2 - Pointer to start of array2
@param len - Number of values in both arrays
@return void
*//*______________________________________________________________*/
void exchange(char *begin1, char *begin2, int len);

/*! 
@brief This function takes in two pointers to char dst and src as
       well as the number of elements to be copied. It copies the
       values starting from the element pointed to by src into
       corresponding elements pointed to by dst.

@param dst - Pointer to start of src
@param src - Pointer to start of dst
@param len - Number of values to be copied
@return void
*//*______________________________________________________________*/
void copy(char *dst, char *src, int len);
