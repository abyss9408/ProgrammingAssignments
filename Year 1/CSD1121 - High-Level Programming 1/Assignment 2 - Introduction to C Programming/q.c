/*!
@file     q.c
@author   Bryan Ang Wei Ze (bryanweize.ang)
@course   CSD1121
@section  B
@tutorial Assignment 2
@date     09/09/2023
@brief    This file contains 2 functions that draws a tree and an animal. 
*//*______________________________________________________________________*/

#include <stdio.h> // for printf

/*! @brief This function draws a tree using printf

@param void
@return void
*//*______________________________________________________________*/
void draw_tree(void){
    printf("    *\n");
    printf("   ***\n");
    printf("  *****\n");
    printf(" *******\n");
    printf("*********\n");
    printf("    #\n");
    printf("    #\n");
    printf("    #\n");
    printf("    #\n");
}

/*! @brief This function draws an animal using printf

@param void
@return void
*//*______________________________________________________________*/
void draw_animal(void){
    printf("  /\\     /\\\n");
    printf(" /  \\___/  \\\n");
    printf("(           )    -------\n");
    printf("(   '   '   )   / Hello  \\\n");
    printf("(     _     )  <  Junior  |\n");
    printf("(           )   \\ Coder! /\n");
    printf(" |         |     -------\n");
    printf(" |    |    |\n");
    printf(" |    |    |\n");
    printf("(_____|_____)\n");
}
