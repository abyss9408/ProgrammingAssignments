/*! 
@file     q.h
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@assignment 7
@date     25/10/2023
@brief    The file contains the declarations of two functions that
          encrypts and decrypts each char(as int) read respectively
*//*______________________________________________________________________*/

#ifndef Q_H
#define Q_H

#define ASCII_COUNT 128

/*! 
@brief This function takes in a pointer *letter and char key. It 
       encrypts the value that *letter points to by adding ASCII 
       value of key to it.

@param *letter - Pointer to char(as int) to be encrypted
@param key - Corresponding char of keyword
@return void
*//*______________________________________________________________*/
void encrypt(int *letter, char key);

/*! 
@brief This function takes in a pointer *letter and char key. It 
       decrypt the value that *letter points to by subtracting ASCII 
       value of key from it.

@param *letter - Pointer to char(as int) to be decrypted
@param key - Corresponding char of keyword
@return void
*//*______________________________________________________________*/
void decrypt(int *letter, char key);


#endif // Q_H
