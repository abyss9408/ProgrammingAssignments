/*---------------------------------------------------------------
  File: main.c
  Project: CSD1100 Assignment 11
  Author: Vadim Surov, vsurov@digipen.edu
 
  Compile: gcc -c -Wall -Wextra -Werror main.c -o main.o
  Link: gcc main.o functions.o -o main.o -lm
 
  Copyright: 2021, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

// See the function description in functions.asm
int f1();
int f2();

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
void test10();

int main(int argc, char* argv[])
{

    void (*f[])() = { test1, test2, test3, test4, test5, test6, test7, test8, test9, test10 };
    const int SIZE = sizeof(f) / sizeof(f[0]);
    int id = -1;

    if (argc == 2)
    {
        if (argv[1][0] == 'i')
        {
            printf("Enter the test number or 0 to run all tests:\n");
            scanf("%d", &id);
        }
        else
            id = atoi(argv[1]);
    }
    else
        scanf("%d", &id);

    if (id == 0)
        for (int i = 0; i < SIZE; ++i)
            f[i]();
    else if (0 < id && id <= SIZE)
        f[id - 1]();
    else
        printf("Test %d not found.\n", id);

    return 0;
} 

void test1()
{
    // Special point/point case
    int actual = f1(0, 0, 0, 0, 0, 0);
    int expected = 1;

    if (actual == expected)
        printf("Test 1 : Pass\n");
    else
        printf("Test 1 : Failed (%d)\n", actual);
}

void test2()
{
    // Point/circle intersecting case
    int actual = f1(0, 0, 0, 0, 0, 10);
    int expected = 1;

    if (actual == expected)
        printf("Test 2 : Pass\n");
    else
        printf("Test 2 : Failed (%d)\n", actual);
}

void test3()
{
    // Circle/point non-intersecting case
    int actual = f1(10, 10, 3, 1, 1, 0);
    int expected = 0;

    if (actual == expected)
        printf("Test 3 : Pass\n");
    else
        printf("Test 3 : Failed (%d)\n", actual);
}

void test4()
{
    // Circle/circle non-intersecting case
    int actual = f1(0, 1, 3, 5, 1, 1);
    int expected = 0;

    if (actual == expected)
        printf("Test 4 : Pass\n");
    else
        printf("Test 4 : Failed (%d)\n", actual);
}

void test5()
{
    // Circle/circle intersecting case
    int actual = f1(0, 1, 3, 5, 10, 10);
    int expected = 1;
    
    if (actual == expected)
        printf("Test 5 : Pass\n");
    else
        printf("Test 5 : Failed (%d)\n", actual);
}

void test6()
{
    // Circle/circle intersecting-touching case 3*3 + 4*4 == 5*5
    int actual = f1(0, 1, 3, 5, 2, 3);
    int expected = 1;

    if (actual == expected)
        printf("Test 6 : Pass\n");
    else
        printf("Test 6 : Failed (%d)\n", actual);
}

void test7()
{
    int actual = f2(0, 0, 0);
    int expected = 0; /*   = (0+0)*(0+0)   */

    if (actual == expected)
        printf("Test 7 : Pass\n");
    else
        printf("Test 7 : Failed (%d)\n", actual);
}

void test8()
{
    int actual = f2(10, 20, 0);
    int expected = 200;  /*   = (10+0)*(20+0)   */

    if (actual == expected)
        printf("Test 8 : Pass\n");
    else
        printf("Test 8 : Failed (%d)\n", actual);
}

void test9()
{
    int actual = f2(0, 0, 1);
    int expected = 1;  /*   = (0+0)*(0+0) + (0+1)*(0+1)   */

    if (actual == expected)
        printf("Test 9 : Pass\n");
    else
        printf("Test 9 : Failed (%d)\n", actual);
}

void test10()
{
    int actual = f2(1, 10, 2);
    int expected = 68;  /*   = (1+0)*(10+0) + (1+1)*(10+1) + (1+2)*(10+2) = 10 + 22 + 36   */

    if (actual == expected)
        printf("Test 10 : Pass\n");
    else
        printf("Test 10 : Failed (%d)\n", actual);
}
