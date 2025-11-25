#include <stdio.h>
#include "q.h"

int main(void)
{
    int value;
    while (1 == scanf("%d", &value))
    {
        if (value < 1 || value > 3999)
        {
            continue;
        }
        else
        {
            decimal_to_roman(value);
        }

    }
    return 0;
}