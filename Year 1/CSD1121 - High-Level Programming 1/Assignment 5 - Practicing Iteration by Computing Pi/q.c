/*! 
@file     q.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  b
@assignment 5
@date     29/09/2023
@brief    The file contains the definitions of three functions that
          compute the value of pi.
*//*______________________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*! 
@brief This function takes in the number of rectangles, divides
       a quadrant with a radius of 2 by it and computes pi by 
       calculating the total area of the rectangles in the quadrant.

@param num_of_rects - The number of rectangles which the quadrant
       will be divided into
@return pi - The total area of the rectangles
*//*______________________________________________________________*/
double trapezoid_pi(int num_of_rects)
{
    int radius=2;
    double distance_of_mid_from_circle_center;
    double width;
    double height;
    double accumulated_height;
    double pi;
    width = (double)radius/num_of_rects;

    for (int i = 1; i <= num_of_rects; ++i)
    {
        distance_of_mid_from_circle_center = (double)(width*i) - (width/2);
        height = sqrt((radius*radius) - (distance_of_mid_from_circle_center*distance_of_mid_from_circle_center));
        accumulated_height += height;
    }

    pi = width * accumulated_height;
    return pi;
}

/*! 
@brief This function takes in a seed for the srand() function and
       and the num_of_trails which is the number of darts thrown
       at a random position. It computes pi by dividing
       the number of darts that land inside the quadrant by the
       number of trails then multipled by 4.

@param seed - Argument for srand()
@param num_of_trails - Number of darts thrown.
@return pi - number of darts that land in the quadrant divided by 
        number of trails then multipled by 4.
*//*______________________________________________________________*/
double montecarlo_pi(unsigned int seed, int num_of_trails)
{
    double random_x;
    double random_y;
    int count;
    int radius=1;
    double result;
    double pi;

    srand(seed);

    for (int i = 1; i <= num_of_trails; ++i)
    {
        random_x = (double)rand() / (double)RAND_MAX;
        random_y = (double)rand() / (double)RAND_MAX;
        if ((random_x*random_x) + (random_y*random_y) <= radius*radius)
        {
            count+=1;
        }
    }

    result = (double)count/(double)num_of_trails;
    pi = 4 * result;
    return pi;
}

/*! 
@brief This function takes in a number of elements. An element of 
       nth iteration = 1/(1+2*(n-1)).In odd iterations, the elements 
       will be added and elements will be subtracted in even 
       iterations. Pi is computed by multiplying the summation 
       of the elements by 4.

@param num_elements - Number of elements to be added and subtracted.
@return pi - Summation of the elements multiplied by 4.
*//*______________________________________________________________*/
double leibniz_pi(int num_elements)
{
    double current_element;
    double sum_of_elements;
    double pi;

    for (int i = 1; i <= num_elements; ++i)
    {
        current_element = (double)1/(1+2*(i-1));
        if (i%2==0)
        {
            sum_of_elements -= current_element;
        }
        else
        {
            sum_of_elements += current_element;
        }
        
    }
    
    pi = 4 * sum_of_elements;
    return pi;
}
