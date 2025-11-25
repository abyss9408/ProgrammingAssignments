/*---------------------------------------------------------------
  File: main.c
  Project: CSD1100 Assignment 10
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
int f3();
int f4();
int f5();

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
    int actual = f1(0,1,2,3,4,5);
    int expected = 4;

    if (actual == expected)
        printf("Test 1 : Pass\n");
    else
        printf("Test 1 : Failed (%d)\n", actual);
}

void test2()
{
    int actual = f1(0,1,2,3,44,5);
    int expected = 44;

    if (actual == expected)
        printf("Test 2 : Pass\n");
    else
        printf("Test 2 : Failed (%d)\n", actual);
}

void test3()
{
    int actual = f2(0, 0, 0);
    int expected = 0;

    if (actual == expected)
        printf("Test 3 : Pass\n");
    else
        printf("Test 3 : Failed (%d)\n", actual);
}

void test4()
{
    int actual = f2(10, 20, 30);
    int expected = 60;

    if (actual == expected)
        printf("Test 4 : Pass\n");
    else
        printf("Test 4 : Failed (%d)\n", actual);
}

void test5()
{
    int actual = f3(0, 1, 2, 3);
    int expected = 1;

    if (actual == expected)
        printf("Test 5 : Pass\n");
    else
        printf("Test 5 : Failed (%d)\n", actual);
}

void test6()
{
    int actual = f3(10, 20, 100, 10);
    int expected = 211;

    if (actual == expected)
        printf("Test 6 : Pass\n");
    else
        printf("Test 6 : Failed (%d)\n", actual);
}

void test7()
{
    int actual = f4(0, 0, 0, 0, 0, 0);
    int expected = 0; /* 0*100000 + 0*10000 + 0*1000 + 0*100 + 0*10 + 0*1 */

    if (actual == expected)
        printf("Test 7 : Pass\n");
    else
        printf("Test 7 : Failed (%d)\n", actual);
}

void test8()
{
    int actual = f4(1, 2, 3, 4, 5, 6);
    int expected = 123456; /* 1*100000 + 2*10000 + 3*1000 + 4*100 + 5*10 + 6*1 */

    if (actual == expected)
        printf("Test 8 : Pass\n");
    else
        printf("Test 8 : Failed (%d)\n", actual);
}

void test9()
{
    int actual = f5(100000, 0, 0, 0, 0);
    int expected = 1; /* = 100000/100000 - 0/10000 - 0/1000 - 0/100 - 0/10 */

    if (actual == expected)
        printf("Test 9 : Pass\n");
    else
        printf("Test 9 : Failed (%d)\n", actual);
}

void test10()
{
    int actual = f5(2000000, 20000, 3000, 400, 50);
    int expected = 6;  /* = 2000000/100000 - 20000/10000 - 3000/1000 - 400/100 - 50/10 */

    if (actual == expected)
        printf("Test 10 : Pass\n");
    else
        printf("Test 10 : Failed (%d)\n", actual);
}
