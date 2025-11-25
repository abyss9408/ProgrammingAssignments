#include <stdio.h>
#include <stdarg.h>

unsigned int compute_square_root(unsigned int value)
{
    unsigned int root = 0;
    unsigned int odd = 1;
    while (value >= odd)
    {
        value -= odd;
        odd += 2;
        ++root;
    }

    return root;
}

void sq_root_compute_array(int num_of_elements, unsigned int *array_of_elements)
{
    for(int i = 0; i < num_of_elements; ++i)
    {
        unsigned int value = array_of_elements[i];
        unsigned int root = compute_square_root(value);
        printf("Square root of %u is %u\n", value, root);
    }
}

void sq_root_compute_varargs(unsigned int n1, ...)
{
    va_list args;
    va_start(args, n1);

    unsigned int value = n1;
    while (value != 0)
    {
        unsigned int root = compute_square_root(value);
        printf("Square root of %u is %u\n", value, root);
        value = va_arg(args, unsigned int);
    }

    va_end(args);
}
