#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "clock.h"
using namespace std;

void opt_col_convert_single_threaded(int *G, int dim);

typedef void (*test_func) (int *, int);

const int TIMES = 10;

#define MAX_DIM 1000

typedef enum {
    BASIC = 0,
    OPT,
    ORIGINAL,
    END
} ARRAY_STATE;

void init_array(int *G, int dim)
{

    for (int i = 0; i < dim; ++i)

        for (int j = 0; j < dim; ++j)

            G[i * dim + j] = rand() % 2 > 0? 0: 1;

}

bool check_correctness(int *G, int *H, int dim)
{

    for (int i = 0; i < dim; ++i)

        for (int j = 0; j < dim; ++j)

            if (G[i * dim + j] != H[i * dim + j]) {

                return false;

            }

    return true;

}


void basic_col_convert(int *G, int dim)
{

    int i, j;

    for (i = 0; i < dim; ++i)

        for (j = 0; j < dim; ++j) {

            G[j * dim + i] = G[j * dim + i] || G[i * dim + j];

        }

}

int main(int argc, char **argv)
{

    prof_time_t start, end;

    prof_time_t base_time;

    double cycles[2] {0.0,0.0};
    
    test_func tf_array[] = {

        basic_col_convert,
        opt_col_convert_single_threaded,
    };
#ifdef DEBUG
    const char *output_strings[] = {
        "Basic",
        "Optimal Single Threaded",
    };

    std::cerr << sizeof(unsigned) << std::endl;

    std::cerr << get_clock_speed() << std::endl;
#endif
    unsigned int nDim = 10;
    
    cin >> nDim;
    
    if (nDim > MAX_DIM)
        nDim = MAX_DIM;
        
    start_read(start);

    end_read(end);

    base_time = end - start;

    int *arrays[END];

    arrays[BASIC] = new int[MAX_DIM * MAX_DIM];

    arrays[OPT] = new int[MAX_DIM * MAX_DIM];

    arrays[ORIGINAL] = new int[MAX_DIM * MAX_DIM];

    init_array(arrays[ORIGINAL], MAX_DIM);


    /*
       Goes through every version from BASIC to OPT_MULTI

       Right now, every implementation is the same as the basic.
     */

    for (int which_func = BASIC; which_func < ORIGINAL; ++which_func) {
#ifdef DEBUG
        std::cout << output_strings[which_func] << std::endl;
#endif        
        int i = nDim;

        //for (int i = 10; i <= nDim; i += 30) {

            prof_time_t acc_t;

            acc_t = 0;

            memcpy(arrays[which_func], arrays[ORIGINAL],
                   sizeof(int) * MAX_DIM * MAX_DIM);

            do {

                start_read(start);

                tf_array[which_func] (arrays[which_func], i);

                end_read(end);

                acc_t = end - start - base_time;
            }
            while (!find_convergence(acc_t, 500, 0.01));

            if (which_func != BASIC) {

                memcpy(arrays[BASIC], arrays[ORIGINAL],
                       sizeof(int) * MAX_DIM * MAX_DIM);

                tf_array[BASIC] (arrays[BASIC], i);

                if (!check_correctness
                    (arrays[BASIC], arrays[which_func], i)) {

                    std::cerr << "Incorrect!" << std::endl;
                    return -1;
                }

            }

#ifdef DEBUG             
            /*
               Prints out the number of elements and cycles taken.
             */
            std::cout << i * i << "\t" << acc_t << std::endl;
#endif
            cycles[which_func - BASIC] = acc_t;         
        
//            cout << which_func - BASIC << "    " << cycles[which_func - BASIC] << endl;
        //}
    }

    double result = 100.0*(cycles[0]-cycles[1])/cycles[0];//result=%age diff between basic & opt 
#if 1    
    if ((nDim <=2 && result > 20.0) || 
        (nDim > 2 && nDim < 10 && result >= 25.0) || 
        (nDim >= 10 && nDim < 100 && result >= 30.0) ||
        (nDim >= 100 && result >= 40.0))
        std::cout << "ok" << endl;
    else
        std::cout << result << endl;
#else    
        std::cout << result << endl;
#endif    
    return 0;

}
