/*---------------------------------------------------------------
  File: main.c
  Project: CSD1100 Assignment 12
  Author: Vadim Surov, vsurov@digipen.edu
 
  Compile: gcc -c -Wall -Wextra -Werror main.c -o main.o
  Link: gcc main.o functions.o -o main.o -lm
 
  Copyright: 2021, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

// See the function description in functions.asm
int len(char*);
int countn(char*);
int counta(char*);
int counts(char*);

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
    char str[] = "";
    int actual = len(str); /* Count the string length */
    int expected = 0;

    if (actual == expected)
        printf("Test 1 : Pass\n");
    else
        printf("Test 1 : Failed (%d)\n", actual);
}

void test2()
{
    char str[] = "Hello World!";
    int actual = len(str); /* Count the string length */
    int expected = 12; 

    if (actual == expected)
        printf("Test 2 : Pass\n");
    else
        printf("Test 2 : Failed (%d)\n", actual);
}

void test3()
{
    char str[] = "";
    int actual = countn(str); /* Count the number of digit letters */
    int expected = 0;

    if (actual == expected)
        printf("Test 3 : Pass\n");
    else
        printf("Test 3 : Failed (%d)\n", actual);
}

void test4()
{
    char str[] = "1 a 2 b 3";
    int actual = countn(str); /* Count the number of digit letters */
    int expected = 3; 

    if (actual == expected)
        printf("Test 4 : Pass\n");
    else
        printf("Test 4 : Failed (%d)\n", actual);
}

void test5()
{
    char str[] = "";
    int actual = counta(str); /* Count the number of alphabet letters */
    int expected = 0;
    
    if (actual == expected)
        printf("Test 5 : Pass\n");
    else
        printf("Test 5 : Failed (%d)\n", actual);
}

void test6()
{
    char str[] = "1 a 2 b 3";
    int actual = counta(str); /* Count the number of alphabet letters */
    int expected = 2; 

    if (actual == expected)
        printf("Test 6 : Pass\n");
    else
        printf("Test 6 : Failed (%d)\n", actual);
}

void test7()
{
    char str[] = "";
    int actual = counts(str); /* Count the number of special characters */
    int expected = 0; 

    if (actual == expected)
        printf("Test 7 : Pass\n");
    else
        printf("Test 7 : Failed (%d)\n", actual);
}

void test8()
{
    char str[] = "1 a 2 b 3";
    int actual = counts(str); /* Count the number of special characters */
    int expected = 4; 

    if (actual == expected)
        printf("Test 8 : Pass\n");
    else
        printf("Test 8 : Failed (%d)\n", actual);
}

void test9()
{
    char str[] = "1234567890abcdefghijklmnopqrstuvwxyz[];',. ]";
    int actual = counts(str); /* Count the number of special characters */
    int expected = 8; 

    if (actual == expected)
        printf("Test 9 : Pass\n");
    else
        printf("Test 9 : Failed (%d)\n", actual);
}

void test10()
{
    char str[] = "ABCDEFGHKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+";
    int actual = counts(str); /* Count the number of special characters */
    int expected = 12; 

    if (actual == expected)
        printf("Test 10 : Pass\n");
    else
        printf("Test 10 : Failed (%d)\n", actual);
}
