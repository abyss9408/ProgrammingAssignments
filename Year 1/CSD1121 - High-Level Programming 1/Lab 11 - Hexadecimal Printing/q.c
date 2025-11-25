// @todo: Add a file documentation header as explained in the specs ...

// @todo: Add necessary C standard library headers here ...
#include <stdio.h>
#include "q.h"

// You should document [not necessary for grading but an excellent habit
// to acquire] your implementation of functions to aid
// in debugging and maintenance not only by yourself but by others in
// your software development team ...

// Remember, the function-level documentation header in q.h is primarily
// meant for your clients. The documentation header here is primarily for
// use by you [and other on your team] solely to aid maintenance and
// debugging tasks ...


// @todo: Provide the definition(s) of function(s) that
// match the declaration(s) in q.h ...
void print_data(const void* ptr, size_t size, size_t span)
{
    const DATUM* obj = (DATUM*)ptr;
    const unsigned char* byte;
    
    for (size_t i = 0, j = 4; i < size/4; i++, j+=4)
    {
        byte = (const unsigned char*)&obj[i].value;

        // print 4 bytes per iteration
        printf("%x %x %x %x   ", byte[1], byte[0], byte[0], byte[1]);
        
        // after printing span bytes in one line
        if (j == span)
        {
            j=4;
            printf("|   ");

            // (span/4-1) is index offset
            for (size_t k = i-(span/4-1);; k++, j+=4)
            {
                // print 4 chars per iteration
                printf("%c %c %c %c   ", obj[k].upper, obj[k].lower, obj[k].lower, obj[k].upper);
                
                // after printing span chars in one line
                if (j == span)
                {
                    printf("\n");
                    j=0;
                    break;
                }
            }
        }
    }
}

// For each function -

// Add documentation [for yourself and not for grading] for the function ...

// @todo: Provide the definition of the function(s) that
// match(es) the declaration(s) in q.h ...