/*!
@file q.c
@author Bryan Ang Wei Ze (bryanweize.ang@digipen.edu)
@course CSD1121
@section B
@date 29/09/2023
@brief This file contains the definitions of functions cost and
       rev.
*//*_____________________________________________________________*/

#include <stdio.h>
#include <stdbool.h>

/*! 
@brief This function calculates the total insurance charge based 
       on the driver's age and number of number of accidents
@param void
@return void
*//*______________________________________________________________*/
void cost(void)
{
    int age;
    int no_of_accidents;
    int total_insurance_charge;
    bool input_valid = true;

    if (scanf("%d,%d", &age, &no_of_accidents) != 2)
    {
        input_valid=false;
    }
    else if (age < 0 || no_of_accidents < 0)
    {
        input_valid=false;
    }

    if (input_valid)
    {
        if (age < 16 || no_of_accidents >= 5)
        {
            total_insurance_charge=0;
        }
        else if (age >= 25)
        {
            if (no_of_accidents == 0)
            {
                total_insurance_charge=500;
            }
            else if (no_of_accidents == 1 || no_of_accidents == 2)
            {
                total_insurance_charge=500+100;
            }
            else
            {
                total_insurance_charge=500+225;
            }
        }
        else // driver is 16 and above but below 25
        {
            if (no_of_accidents == 0)
            {
                total_insurance_charge=500+50;
            }
            else if (no_of_accidents == 1 || no_of_accidents == 2)
            {
                total_insurance_charge=500+50+100;
            }
            else
            {
                total_insurance_charge=500+50+225;
            }
        }

        if (total_insurance_charge == 0)
        {
            printf("age = %d, number of accidents = %d, no insurance coverage!\n", age, no_of_accidents);
        }
        else
        {
            printf("age = %d, number of accidents = %d, insurance cost = %d\n", age, no_of_accidents, total_insurance_charge);
        }
    }
    else // invalid input
    {
        printf("You did not type in the correct format in terms of age and no of accidents.\n");
    }
    
}

/*! 
@brief This function reverses a number from the user, includes
       both positive and negative numbers.
@param void
@return void
*//*______________________________________________________________*/
void rev(void)
{
    int num;
    int rev = 0;
    bool is_negative = false;

    scanf("%d", &num);
    if (num < 0)
    {
        num *= -1;
        is_negative = true;
    }
    do
    {
        rev = rev * 10 + num % 10;
        num /= 10;
    }
    while(num > 0);
    if (is_negative)
    {
        printf("%d\n", -rev);
    }
    else
    {
        printf("%d\n", rev);
    }
}