/*! 
@file     q.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@lab      4
@date     22/09/2023
@brief    The file contains a collection of functions that break down
          monetary value into cash denominations.
*//*______________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "q.h"

/*! 
@brief This function prints a single line of output table.

@param index - Index of the line
@param rest - number of cents remaining for break-down into denominations
@param denomination - denomination in cents that is currently being considered
@return void
*//*______________________________________________________________*/
void print_line(int index, int rest, int denomination)
{
    int count;
    int dollars;
    int cents;
    count = rest/denomination;
    dollars = denomination/100;
    cents = denomination%100;
    printf("| %-2d | %9d.%02d | %5d |\n", index, dollars, cents, count);
}

/*! 
@brief This function takes in a monetary value in cents and outputs
       the value broken down into the respective denominations

@param cents - amount to be broken down into cash denominations
@return void
*//*______________________________________________________________*/
void break_down(int cents)
{
    printf("\n+----+--------------+-------+\n");
    printf("| #  | Denomination | Count |\n");
    printf("+----+--------------+-------+\n");
    print_line(1, cents, 10000);
    print_line(2, cents%10000, 5000);
    print_line(3, cents%10000%5000, 1000);
    print_line(4, cents%10000%5000%1000, 500);
    print_line(5, cents%10000%5000%1000%500, 200);
    print_line(6, cents%10000%5000%1000%500%200, 100);
    print_line(7, cents%10000%5000%1000%500%200%100, 50);
    print_line(8, cents%10000%5000%1000%500%200%100%50, 20);
    print_line(9, cents%10000%5000%1000%500%200%100%50%20, 10);
    print_line(10, cents%10000%5000%1000%500%200%100%50%20%10, 5);
    print_line(11, cents%10000%5000%1000%500%200%100%50%20%10%5, 1);
    printf("+----+--------------+-------+\n");
}

/*! 
@brief This function validates user input by ensuring that the format
       is correct and the value entered is non-negative.

@param void
@return void
*//*______________________________________________________________*/
void go(void)
{
    int dollars;
    char cents_in_string[20];
    int cents;
    int amount_in_cents;
    bool input_valid = true;

    while (true)
    {
        printf("Please enter total value: ");
        if (scanf("%d.%s", &dollars, cents_in_string) != 2)
        {
            input_valid = false;
        }
        else if (dollars < 0 || atoi(cents_in_string) < 0)
        {
            input_valid = false;
        }
        else if (getc(stdin) == EOF)
        {
            input_valid = false;
        }
        else if (strlen(cents_in_string) != 2)
        {
            input_valid = false;
        }
        
        if (input_valid)
        {
            cents = atoi(cents_in_string);
            amount_in_cents = dollars*100+cents;
            break_down(amount_in_cents);
            continue;
        }
        else
        {
            printf("You did not type in the correct format in terms of dollars and cents.\n");
            break;
        }
    }
}