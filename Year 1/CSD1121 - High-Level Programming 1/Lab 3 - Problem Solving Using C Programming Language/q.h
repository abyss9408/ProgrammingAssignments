/*!
@file     q.h
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  B
@tutorial Lab 3
@date     15/09/2023
@brief    This file contains 2 declarations of functions tile() and dispense_change()
*//*______________________________________________________________________*/

/*
@brief This function calculates the number of tiles and gap at each end based on the wall length and tile width
@param wall length and tile width
@return void
*//*______________________________________________________________*/
void tile(double wall_length, double tile_width);

/*
@brief This function displays the number of loonies, half-loonies, quarters, dimes, nickels and pennies dispensed based on purchase price and dollar bill denomination
@param void
@return void
*//*______________________________________________________________*/
void dispense_change(void);
