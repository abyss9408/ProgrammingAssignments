/******************************************************************************
*@filename   qdriver.c 
*@author(s)  Prasanna Ghali 
*@DP emails  pghali@digipen.edu
*@course     High-Level Programming 1  
 
* Brief Description: 
* This file contains the main function for assignment: structures & file i/o. 
* It uses functionality implemented by the assignment to print a summary of
* tsunami statistics.
******************************************************************************/

#include "q.h"
#include <stdio.h>  // for fprintf
#include <stdlib.h> // for exit

// assume a maximum of 100 events are recorded in a file
enum { MAX_TSUNAMI_EVENTS = 100 };

/******************************************************************************
* @brief The main function uses a command line argument provided by the user
*        that specifies a file name that records tsunami events.
*        It is assumed that there are no more than MAX_TSUNAMI_EVENTS number
*        of tsunami events in the file.
*        It is assumed that the user supplied function read_tsunami_data will
*        perform sanity checks to ensure that the file exists in the current
*        directory.
* @param argc - count of command-line arguments 
* @param argv - vector of pointers to strings recording command-line arguments.
         Each element of array is of type char*. The size of the array is
*        (argc+1) with the last element with subscript argc has a NULL pointer.
******************************************************************************/
int main(int argc, char *argv[]) {
  /*
  The program requires the name of a text file recording tsunami events.
  Without this text file, it is not possible for the program to do anything
  useful. Therefore, it is important to ensure that there is at least one
  more command-line argument in addition to the program's name.
  */
  if (argc < 3) {
    fprintf(stderr,
        "Usage: ./q.out tsunami-data-file your-output-file;\n");
    exit(EXIT_FAILURE);
  } 
  
  /*
  Call user-defined function to load tsunami events from text file
  whose name is pointed to by pointer argv[1].
  Information about each event is stored in an element of type struct tsunami
  and collectively these events are stored in array with name tsun_data.
  */
  struct Tsunami tsun_data[MAX_TSUNAMI_EVENTS];
  int num_events = read_data(argv[1], tsun_data, MAX_TSUNAMI_EVENTS);
  
  // open output text file
  FILE *out_stm = fopen(argv[2], "w");
  if (NULL == out_stm) {
    fprintf(stderr, "Unable to create output file %s\n", argv[2]);
    // exit(): causes program to terminate:
    // see https://en.cppreference.com/w/c/program/exit
    // EXIT_FAILURE and EXIT_SUCCESS are macros that can be used to indicate
    // program execution status to operating system
    exit(EXIT_FAILURE);
  }
  
  // print pretty table of tsunami events
  fprintf(out_stm, "List of tsunamis:\n");
  fprintf(out_stm, "-----------------\n");
  print_info(tsun_data, num_events, out_stm);
  fprintf(out_stm, "\n");
  
  // print certain summaries of tsunami events.
  fprintf(out_stm, "Summary information for tsunamis\n");
  fprintf(out_stm, "--------------------------------\n");
  double max_ht = get_max_height(tsun_data, num_events);
  fprintf(out_stm, "\nMaximum wave height (in meters): %5.2f\n", max_ht);
  double avg_ht = get_average_height(tsun_data, num_events);
  fprintf(out_stm, "\nAverage wave height (in meters): %5.2f\n", avg_ht);
  fprintf(out_stm, "\nTsunamis with greater than average height %.2f:\n", avg_ht);
  print_height(tsun_data, num_events, avg_ht, out_stm);
  
  fclose(out_stm);
  exit(EXIT_SUCCESS);
}
