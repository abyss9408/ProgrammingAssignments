/*! 
@file     qdriver.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@assignment 7
@date     25/10/2023
@brief    The file contains the main function for assignment 7. It is used
          to read each char as int from plain.txt, encrypts each of them
          using the Vigenere cipher with the keyword from key.txt and output
          it to cipher.txt. It is also used to read each char as int from 
          cipher.txt, decrypts each of them using the Vigenere cipher with
          the same keyword from key.txt and outputs it to out-plain.txt
*//*______________________________________________________________________*/

#include "q.h"     // encrypt and decrypt function declarations
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
#ifdef ENCRYPT

  FILE *plain = fopen("plain.txt", "r");
  FILE *key = fopen("key.txt", "r");
  FILE *cipher = fopen("cipher.txt", "w");

  int ch;
  char key_array[255] = {'\0'};
  int key_index = 0;

  if (plain == NULL)
  {
    fputs("Unable to open file plain.txt\n", stderr);
    exit(EXIT_FAILURE);
  }
  else if (key == NULL)
  {
    fputs("Unable to open file key.txt\n", stderr);
    exit(EXIT_FAILURE);
  }
  else
  {
    // read each char from key.txt file
    for (int i = 0; (key_array[i] = (char)fgetc(key)) != EOF; i++);

    // search for the EOF char written to key_array and change it to null char
    for (int i = 0; i < (int)(sizeof(key_array)/sizeof(key_array[0])); i++)
    {
      if (key_array[i] == EOF)
      key_array[i] = '\0';
    }
  
    while ((ch = fgetc(plain)) != EOF)
    {
      if (key_array[key_index] == '\0')
      {
        key_index = 0;
      }
      encrypt(&ch, key_array[key_index]);
      fputc(ch, cipher);
      key_index++;
    }
  }
  fclose(plain);
  fclose(key);
  fclose(cipher);

#else

  FILE *cipher = fopen("cipher.txt", "r");
  FILE *key = fopen("key.txt", "r");
  FILE *plain = fopen("out-plain.txt", "w");

  int ch;
  char key_array[255] = {'\0'};
  int key_index = 0;
  int word_count = 0;
  int newline_tab_whitespace_count = 0;

  if (cipher == NULL)
  {
    fputs("Unable to open file cipher.txt\n", stderr);
    exit(EXIT_FAILURE);
  }
  else if (key == NULL)
  {
    fputs("Unable to open file key.txt\n", stderr);
    exit(EXIT_FAILURE);
  }
  else
  {
    // read each char from key.txt file
    for (int i = 0; (key_array[i] = (char)fgetc(key)) != EOF; i++);

    // search for the EOF char written to key_array and change it to null char
    for (int i = 0; i < (int)(sizeof(key_array)/sizeof(key_array[0])); i++)
    {
      if (key_array[i] == EOF)
      key_array[i] = '\0';
    }
  
    while ((ch = fgetc(cipher)) != EOF)
    {     
      if (key_array[key_index] == '\0')
      {
        key_index = 0;
      }
      decrypt(&ch, key_array[key_index]);
      fputc(ch, plain);
      key_index++;
      if (ch == '\n' || ch == '\t' || ch == ' ' || ch == '\r')
      {
        newline_tab_whitespace_count++;
        // only count consecutive carriage returns, new lines, tabs and whitespaces once
        if (newline_tab_whitespace_count == 1)
        word_count++;
      }
      else
      {
        newline_tab_whitespace_count = 0;
      }
    }
  }
  fclose(cipher);
  fclose(key);
  fclose(plain);
  fprintf(stderr, "Words: %d\n", word_count);

#endif

  return 0;
}
