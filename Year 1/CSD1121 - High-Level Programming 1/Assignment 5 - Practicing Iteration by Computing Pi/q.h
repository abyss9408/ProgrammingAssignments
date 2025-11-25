/*! 
@file     q.h
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@assignment 5
@date     29/09/2023
@brief    The file contains the definitions of three functions that
          compute the value of pi.
*//*______________________________________________________________________*/

#ifndef _Q_H_
#define _Q_H_

/*! 
@brief This function takes in the number of rectangles, divides
       a quadrant with a radius of 2 by it and computes pi by 
       calculating the total area of the rectangles in the quadrant.

@param num_of_rects - The number of rectangles which the quadrant
       will be divided into.
@return pi - The total area of the rectangles
*//*______________________________________________________________*/
double trapezoid_pi(int num_of_rects);

/*! 
@brief This function takes in a seed for the srand() function and
       and the num_of_trails which is the number of darts thrown
       at a random position. It computes pi by dividing
       the number of darts that land inside the quadrant by the
       number of trails then multipled by 4.

@param seed - Argument for srand()
@param num_of_trails - Number of darts thrown.
@return pi - Number of darts that land in the quadrant divided by 
        number of trails then multipled by 4.
*//*______________________________________________________________*/
double montecarlo_pi(unsigned int seed, int num_of_trails);

/*! 
@brief This function takes in a number of elements. An element of 
       nth iteration = 1/(1+2*(n-1)).In odd iterations, the elements 
       will be added and elements will be subtracted in even 
       iterations. Pi is computed by multiplying the summation 
       of the elements by 4.

@param num_elements - Number of elements to be added and subtracted.
@return pi - Summation of the elements multiplied by 4.
*//*______________________________________________________________*/
double leibniz_pi(int num_elements);

#endif
