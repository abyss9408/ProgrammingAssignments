/*!
@file     q.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  B
@tutorial Lab 3
@date     15/09/2023
@brief    This file contains 2 definitions of functions tile() and dispense_change()
*//*______________________________________________________________________*/

#include <stdio.h>
#include <math.h>
#include "q.h"

/*
@brief This function calculates the number of tiles and gap at each end based on the wall length and tile width
@param wall length and tile width
@return void
*//*______________________________________________________________*/
void tile(double wall_length, double tile_width)
{
    int pairs;
    int tiles;
    double gap_at_each_end;
    pairs = (wall_length - tile_width) / (tile_width * 2);
    tiles = 1 + 2 * pairs;
    gap_at_each_end = (wall_length-tiles*tile_width) / 2;

    printf("Wall length: %4.2f | Tile width: %4.2f\n", wall_length, tile_width);
    printf("Number of tiles: %d\n", tiles);
    printf("Gap at each end: %4.2f\n", gap_at_each_end);
}


/*
@brief This function displays the number of loonies, half-loonies, quarters, dimes, nickels and pennies dispensed based on the inputs of purchase price and dollar bill denomination
@param void
@return void
*//*______________________________________________________________*/
void dispense_change(void)
{
    int purchase_dollars;
    int purchase_cents;
    int dollar_bill_denomination;
    int purchase_price_in_cents;
    int change_in_cents;
    int no_of_loonies;
    int no_of_half_loonies;
    int no_of_quarters;
    int no_of_dimes;
    int no_of_nickels;
    int no_of_pennies;

    scanf("%d.%d %d",&purchase_dollars, &purchase_cents, &dollar_bill_denomination);
    purchase_price_in_cents = purchase_dollars*100+purchase_cents;
    change_in_cents = (dollar_bill_denomination*100)-purchase_price_in_cents;

    no_of_loonies = (int)floor(change_in_cents/100);
    no_of_half_loonies = (int)floor((change_in_cents - no_of_loonies*100)/50);
    no_of_quarters = (int)floor((change_in_cents - no_of_loonies*100 - no_of_half_loonies*50)/25);
    no_of_dimes = (int)floor((change_in_cents - no_of_loonies*100 - no_of_half_loonies*50 - no_of_quarters*25)/10);
    no_of_nickels = (int)floor((change_in_cents - no_of_loonies*100 - no_of_half_loonies*50 - no_of_quarters*25 - no_of_dimes*10)/5);
    no_of_pennies = (int)floor((change_in_cents - no_of_loonies*100 - no_of_half_loonies*50 - no_of_quarters*25 - no_of_dimes*10 - no_of_nickels*5)/1);
    printf("%d loonies + %d half-loonies + %d quarters + %d dimes + %d nickels + %d pennies\n", no_of_loonies, no_of_half_loonies, no_of_quarters, no_of_dimes, no_of_nickels, no_of_pennies);
}
