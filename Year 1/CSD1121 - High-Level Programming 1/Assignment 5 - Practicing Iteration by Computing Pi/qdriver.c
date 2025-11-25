/*
filename    qdriver.c
author      pghali@digipen.edu
course      High-Level Programming Language 1
assignment  computing pi using three algorithms ...

This file contains the main function for the pi assignment. It is used as
a "driver" to test trapezoid_pi, montecarlo_pi, and leibniz_pi functions.
This function prints three tables of PI values from each of the three
algorithms. The first table consists of small number of iterations, the
second table consists of medium number of iterations, while the third and
final table contains a large count of iterations.
To print the appropriate table, the user should provide either the s or m
or l option to the program, as in:
./qsample.out s
*/
#include <stdio.h>  // scanf, printf
#include <stdlib.h> // atoi
#include "q.h"      // trapezoid_pi, montecarlo_pi, leibniz_pi

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: Provide option s or m or l for small or medium "
          "or large iteration counts\n");
    return 0;
  }

  // print table header ...
  printf("Approximations for pi\n");
  printf("Iterations      Trapezoid         Monte Carlo          Leibniz\n");
  printf("-------------------------------------------------------------------\n");
  int choice = (char)argv[1][0]; // convert user option to int value
  switch (choice) {
    case 's': // small iteration count  
      for (int i = 1; i <= 20; i+=2) {      
        printf("%-10i%18.12f%19.12f%19.12f\n", 
              i, trapezoid_pi(i), montecarlo_pi(123456789U, i), leibniz_pi(i));
      }
    break;
    case 'm': // medium iteration count 
      for (int i = 1, j = 1; i <= 1000; i = 100*j, ++j) {           
        printf("%-10i%18.12f%19.12f%19.12f\n", 
              i, trapezoid_pi(i), montecarlo_pi(123456789U, i), leibniz_pi(i));
      }
    break;
    case 'l': // large iteration count
      for (int i = 1, j = 5; i <= 100000000; i *= j, j = j==5?2:5) {
        printf("%-10i%18.12f%19.12f%19.12f\n", 
              i, trapezoid_pi(i), montecarlo_pi(123456789U, i), leibniz_pi(i));
      }
    break;
  }
  return 0;
}
