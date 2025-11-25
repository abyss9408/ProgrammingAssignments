#ifndef CLOCK_H
#define CLOCK_H
#include <cstdlib>
//#ifdef __linux
#include "unistd.h"
#include <sched.h>
typedef unsigned long prof_time_t;
/*
#elif defined(_WIN32)
#include <Windows.h>
#include "intrin.h"
typedef unsigned long long prof_time_t;
#endif
*/
inline void start_read(prof_time_t & cycle_read)
{
/*    
#ifdef _WIN32
    SetProcessAffinityMask(GetCurrentProcess(), 1);
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
    int a[4], b = 1;
    __cpuid(a, b);
    cycle_read = __rdtsc();
#else
*/
    unsigned &high = *(((unsigned *) &cycle_read + 1));
    unsigned &low = *(((unsigned *) &cycle_read));

	cpu_set_t mask; /* processors 0 */
	CPU_ZERO(&mask);
	CPU_SET(1, &mask);
	unsigned int len = sizeof(mask);
	if (sched_setaffinity(0, len, &mask) < 0) {
		perror("sched_setaffinity");
	}    
    asm volatile ("cpuid\n\t"
                  "rdtsc\n\t"
                  "movl %%eax, %0\n\t"
                  "movl %%edx, %1\n\t":"=r" (low), "=r"(high)
                  ::"%eax", "%ebx", "%ecx", "%edx");
                  
//#endif
};

void inline end_read(prof_time_t & cycle_read)
{
/*    
#ifdef _WIN32
    unsigned int c;
    cycle_read = __rdtscp(&c);
    int a[4], b = 1;
    __cpuid(a, b);
#else*/
    int &high = *(((int *) &cycle_read + 1));
    int &low = *(((int *) &cycle_read));
    asm volatile ("rdtscp\n\t"
                  "movl %%edx, %0\n\t"
                  "movl %%eax, %1\n\t" "cpuid\n\t":"=r" (high), "=r"(low)
                  ::"%eax", "%ebx", "%ecx", "%edx");
///#endif

};


double inline get_clock_speed()
{
    prof_time_t start, end;

    start_read(start);
#ifdef __linux
    sleep(1);
#elif defined(_WIN32)
    Sleep(1000);
#endif
    end_read(end);
    return (double) (end - start);
}

inline bool find_convergence(prof_time_t & val, int num_of_samples,
                             double epsilon)
{
    static prof_time_t smallest = 0xFFFFFFFFFFFFFFFFL;
    static int num_times = 0;

    if (num_times >= num_of_samples) {
        num_times = 0;
        val = smallest;
        smallest = 0xFFFFFFFFFFFFFFFFL;
        return true;
    }

    num_times++;

    if (llabs(val - smallest) >= (epsilon * val)) {
        if (val < smallest)
            smallest = val;
        return false;
    } else {
        val = smallest;
        {
            smallest = 0xFFFFFFFFFFFFFFFFL;
            num_times = 0;
            return true;
        }
    }
}

#endif
