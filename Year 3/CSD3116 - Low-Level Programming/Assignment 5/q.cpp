#include <stdio.h>
#include <sstream>
#include <iostream>
#include "q.h"

char ar[200]={0};
std::istringstream str;

void f(C c)
{   
    sprintf(ar, "%d %d %d %d %d");
    str.str(ar);
    std::cout << str.str() << '\n';
}