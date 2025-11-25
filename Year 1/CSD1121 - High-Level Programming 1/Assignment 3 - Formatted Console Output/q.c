/*!
@file       q.c
@author     Bryan Ang Wei Ze (bryanweize.ang)
@course     CSD1121
@section    B
@assignment 3
@date       17/9/2023
@brief      This file contains definition of
            the temperature_convertor() function.
*//*_________________________________________________________________________*/

#include <stdio.h>
#include "q.h"
void temp_converter(int temp_in_fahrenheit)
{
    double temp_in_celsius;
    double temp_in_kelvin;

    temp_in_celsius = (double)(temp_in_fahrenheit - 32) * 5/9;
    temp_in_kelvin = (double)(temp_in_fahrenheit + 459.67) * 5/9;

    printf("Fahrenheit     Celsius        Kelvin         \n");
    printf("---------------------------------------------\n");
    printf("%-15d%-15.2f%-15.2f\n", temp_in_fahrenheit, temp_in_celsius, temp_in_kelvin);
}
