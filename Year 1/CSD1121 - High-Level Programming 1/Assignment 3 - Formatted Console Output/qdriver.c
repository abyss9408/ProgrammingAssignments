/*!
@file       qdriver.c 
@author     Swavek Wlodkowski (swavek.wlodkowski)
@course     HLP1
@section    All sections
@assignment 3
@date       28/9/2020
@brief      This file contains unit tests that exercise
            the temperature_convertor() function.
            Do not modify or submit this file.
*//*_________________________________________________________________________*/

#include <stdio.h>  // declaration of printf
#include "q.h"      // declaration of temp_converter [to be submitted by student]

int main(void) {
  // test case 1
  temp_converter(0);
  printf("\n");

  // test case 2
  temp_converter(20);
  printf("\n");

  // test case 3
  temp_converter(300);
  printf("\n");

  // test case 4
  temp_converter(-20);
  printf("\n");

  // test case 5
  temp_converter(137);
  printf("\n");

  // test case 6
  temp_converter(-300);
  printf("\n");

  // test case 7
  temp_converter(-1000);
  printf("\n");

  // test case 8
  temp_converter(5000);
  printf("\n");

  // test case 9
  temp_converter(10000);
  printf("\n");

  // test case 10
  temp_converter(100000);

  return 0;
}
