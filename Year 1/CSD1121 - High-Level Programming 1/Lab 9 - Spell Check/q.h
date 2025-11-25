/*! 
@file     q.h
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@lab      9
@date     03/11/2023
@brief    The file contains the declarations of five functions that access
          words for correct spelling based on a selected dictionary file.
*//*______________________________________________________________________*/

typedef int WordCount;
typedef unsigned char WordLength;
typedef int ErrorCode;

struct DictionaryInfo
{
    // Length of the shortest word
    WordLength shortest;
    // Length of the longest word
    WordLength longest;
    // Number of words in the dictionary
    WordCount count;
};
typedef struct DictionaryInfo DictionaryInfo;


enum ErrorCode
{
    FILE_OK = -1, // The file was opened successfully.
    FILE_ERR_OPEN = -2, // The file was not opened.
    WORD_OK = -3, // The word was found in the dictionary.
    WORD_BAD = -4 // The word was not found in the dictionary.
};
enum
{
    LONGEST_WORD = 50
};
/*! 
@brief This function takes in a string and converts it to uppercase.

@param string - String to be converted to uppercase
@return char* - String with all uppercase letters
*//*______________________________________________________________*/
char* str_to_upper(char* string);

/*! 
@brief This function takes in a dictionary file name and a char
       letter. It computes the name of words in the dictionary
       that begins with the letter

@param dictionary - File name of the dictionary
@return WordCount - Number of words that begins with the letter
*//*______________________________________________________________*/
WordCount words_starting_with(const char* dictionary, char letter);

/*! 
@brief This function takes in a dictionary file name and a word
       to be searched for in the dictionary.

@param dictionary - File name of the dictionary
@return ErrorCode - File cannot open, word found or word not found
*//*______________________________________________________________*/
ErrorCode spell_check(const char* dictionary, const char* word);

/*! 
@brief This function takes in a dictionary file name, an array
       lengths and the maxinum word length to be counted. It
       computes the number of words in the dictionary with the
       respective lengths and store them in array lengths.

@param dictionary - File name of the dictionary
@param lengths - Array that stores the number of words with the
       resepective lengths
@param count - Maxinum word length to be counted
@return ErrorCode - File cannot open or file opens
*//*______________________________________________________________*/
ErrorCode word_lengths(const char* dictionary, WordCount lengths[], WordLength count);

/*! 
@brief This function takes in a dictionary file name and a pointer
       to structure that contains information of the
       dictionary. It computes the number of words, shortest and
       longest word length in the dictionary.

@param dictionary - File name of the dictionary
@param info - Pointer to structure that contains information of the
       dictionary such as number of words, shortest and longest
       word length
@return ErrorCode - File cannot open or file opens
*//*______________________________________________________________*/
ErrorCode info(const char* dictionary, DictionaryInfo* info);
