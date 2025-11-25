/*! 
@file     q.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@assignment 7
@date     25/10/2023
@brief    The file contains the defintions of two functions that
          encrypts and decrypts each char(as int) read respectively
*//*______________________________________________________________________*/

#include "q.h" // included because q.c requires access to ASCII_COUNT

void encrypt(int *letter, char key)
{
    *letter += key;
    if (*letter >= ASCII_COUNT)
    {
        *letter -= ASCII_COUNT;
    }
}

void decrypt(int *letter, char key)
{
    *letter -= key;
    if (*letter < 0)
    {
        *letter += ASCII_COUNT;
    }
}