/*! 
@file     q.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@lab      9
@date     03/11/2023
@brief    The file contains the definitions of five functions that access
          words for correct spelling based on a selected dictionary file.
*//*______________________________________________________________________*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "q.h"

char* str_to_upper(char* string)
{
    for (size_t i = 0; string[i] != '\0'; i++)
    {
        if (string[i] >= 'a' && string[i] <= 'z')
        string[i] = (char)toupper(string[i]);
    }

    return string;
}

WordCount words_starting_with(const char* dictionary, char letter)
{
    FILE* read = fopen(dictionary, "r");
    char word[LONGEST_WORD];
    WordCount count = 0;

    if (read == NULL)
    {
        return FILE_ERR_OPEN;
    }
    else
    {
        while (fgets(word, sizeof(word), read) != NULL)
        {
            str_to_upper(word);
            str_to_upper(&letter);

            if (word[0] == letter)
            {
                count++;
            }
        }

        fclose(read);
        return count;
    }
}

ErrorCode spell_check(const char* dictionary, const char* word)
{
    FILE* read = fopen(dictionary, "r");
    char dictionary_word[LONGEST_WORD];
    char dic_word_first_uppercase[LONGEST_WORD];
    int found = 0;

    if (read == NULL)
    {
        return FILE_ERR_OPEN;
    }
    else
    {
        while (fscanf(read, "%s\n", dictionary_word) != EOF)
        {
            strcpy(dic_word_first_uppercase, dictionary_word);
            // Convert first letter of each dictionary word to uppercase
            dic_word_first_uppercase[0] = (char)toupper(dic_word_first_uppercase[0]);
            if (!strcmp(dictionary_word, word) || 
            !strcmp(str_to_upper(dictionary_word), word) ||
            !strcmp(dic_word_first_uppercase, word))
            {
                found = 1;
                break;
            }
        }

        fclose(read);

        if (found)
        {
            return WORD_OK;
        }
        else
        {
            return WORD_BAD;
        }
        
    }

}

ErrorCode word_lengths(const char* dictionary, WordCount lengths[], WordLength count)
{
    FILE* read = fopen(dictionary, "r");
    char dictionary_word[LONGEST_WORD];

    if (read == NULL)
    {
        return FILE_ERR_OPEN;
    }
    else
    {
        while (fgets(dictionary_word, sizeof(dictionary_word), read) != NULL)
        {
            for (size_t i = 0; ; i++)
            {
                if (dictionary_word[i] == '\n' || dictionary_word[i] == '\r')
                {
                    dictionary_word[i] = '\0';
                    break;
                }
            }

            for (size_t i = count; i > 0; i--)
            {
                if (strlen(dictionary_word) == i)
                {
                    lengths[i]++;
                    break;
                }
            }
        }
        fclose(read);
        return FILE_OK;
    }   
}

ErrorCode info(const char* dictionary, DictionaryInfo* info)
{
    FILE* read = fopen(dictionary, "r");
    char dictionary_word[LONGEST_WORD];
    WordCount num_words = 0;
    WordLength length_shortest;
    WordLength length_longest;

    if (read == NULL)
    {
        return FILE_ERR_OPEN;
    }
    else
    {
        // read first word from dictionary
        fgets(dictionary_word, sizeof(dictionary_word), read);
        for (size_t i = 0; ; i++)
        {
            if (dictionary_word[i] == '\n' || dictionary_word[i] == '\r')
            {
                dictionary_word[i] = '\0';
                break;
            }
        }
        num_words++;
        // assume first word is both shortest and longest
        length_shortest = (WordLength)strlen(dictionary_word);
        length_longest = (WordLength)strlen(dictionary_word);

        // read all other words from dictionary
        while (fgets(dictionary_word, sizeof(dictionary_word), read) != NULL)
        {
            for (size_t i = 0; ; i++)
            {
                if (dictionary_word[i] == '\n' || dictionary_word[i] == '\r')
                {
                    dictionary_word[i] = '\0';
                    break;
                }
            }
            
            if (strlen(dictionary_word) > length_longest)
            {
                length_longest = (WordLength)strlen(dictionary_word);
            }
            else if (strlen(dictionary_word) < length_shortest)
            {
                length_shortest = (WordLength)strlen(dictionary_word);
            }
            
            num_words++;
            
        }

        fclose(read);
        info->count = num_words;
        info->longest = length_longest;
        info->shortest = length_shortest;
        return FILE_OK;
    }  
}
