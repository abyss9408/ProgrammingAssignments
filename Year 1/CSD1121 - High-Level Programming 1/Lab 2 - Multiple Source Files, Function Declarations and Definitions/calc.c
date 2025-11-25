/*!
calc.c
Bryan Ang Wei Ze (bryanweize.ang)
CSD1121
Section b
Lab 2
08/09/2023
This file contains a collection of functions definitions
*//*______________________________________________________________________*/
#include <stdio.h>
#include "calc.h"

int squared(int num){
    int result;
    result = num * num;
    return result;
}

double cubed(double num){
    double result;
    result = num * num * num;
    return result;
}

double minus(double num){
    double result;
    result = -num;
    return result;
}
