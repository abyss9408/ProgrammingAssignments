/*! 
@file     q.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@assignment 4
@date     24/09/2023
@brief    The file contains the definition of a function that converts
          decimal numbers to roman numerals.
*//*______________________________________________________________________*/

#include <stdio.h>
#include <string.h>

void decimal_to_roman(int convert)
{
    int no_of_thousands;
    int no_of_hundreds;
    int no_of_tens;
    int no_of_ones;
    char result[20] = "";

    no_of_thousands = convert/1000;
    no_of_hundreds = (convert%1000)/100;
    no_of_tens = ((convert%1000)%100)/10;
    no_of_ones = ((convert%1000)%100)%10;



    if (no_of_thousands*1000 == 3000)
    {
        strcat(result, "MMM");
    }
    else if (no_of_thousands*1000 == 2000)
    {
        strcat(result, "MM");
    }
    else if (no_of_thousands*1000 == 1000)
    {
        strcat(result, "M");
    }



    if (no_of_hundreds*100 == 900)
    {
        strcat(result, "CM");
    }
    else if (no_of_hundreds*100 == 800)
    {
        strcat(result, "DCCC");
    }
    else if (no_of_hundreds*100 == 700)
    {
        strcat(result, "DCC");
    }
    else if (no_of_hundreds*100 == 600)
    {
        strcat(result, "DC");
    }
    else if (no_of_hundreds*100 == 500)
    {
        strcat(result, "D");
    }
    else if (no_of_hundreds*100 == 400)
    {
        strcat(result, "CD");
    }
    else if (no_of_hundreds*100 == 300)
    {
        strcat(result, "CCC");
    }
    else if (no_of_hundreds*100 == 200)
    {
        strcat(result, "CC");
    }
    else if (no_of_hundreds*100 == 100)
    {
        strcat(result, "C");
    }


    if (no_of_tens*10 == 90)
    {
        strcat(result, "XC");
    }
    else if (no_of_tens*10 == 80)
    {
        strcat(result, "LXXX");
    }
    else if (no_of_tens*10 == 70)
    {
        strcat(result, "LXX");
    }
    else if (no_of_tens*10 == 60)
    {
        strcat(result, "LX");
    }
    else if (no_of_tens*10 == 50)
    {
        strcat(result, "L");
    }
    else if (no_of_tens*10 == 40)
    {
        strcat(result, "XL");
    }
    else if (no_of_tens*10 == 30)
    {
        strcat(result, "XXX");
    }
    else if (no_of_tens*10 == 20)
    {
        strcat(result, "XX");
    }
    else if (no_of_tens*10 == 10)
    {
        strcat(result, "X");
    }


    if (no_of_ones == 9)
    {
        strcat(result, "IX");
    }
    else if (no_of_ones == 8)
    {
        strcat(result, "VIII");
    }
    else if (no_of_ones == 7)
    {
        strcat(result, "VII");
    }
    else if (no_of_ones == 6)
    {
        strcat(result, "VI");
    }
    else if (no_of_ones == 5)
    {
        strcat(result, "V");
    }
    else if (no_of_ones == 4)
    {
        strcat(result, "IV");
    }
    else if (no_of_ones == 3)
    {
        strcat(result, "III");
    }
    else if (no_of_ones == 2)
    {
        strcat(result, "II");
    }
    else if (no_of_ones == 1)
    {
        strcat(result, "I");
    }

    printf("%s\n", result);
}