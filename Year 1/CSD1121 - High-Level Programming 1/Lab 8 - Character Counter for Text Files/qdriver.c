// Program to count the number of times each letter in a file occurs
#include "q.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <assert.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stdout, "Usage: ./q.out text-file\n");
    return 0;
  }

  FILE *input_file_stream = fopen(argv[1], "r");
  if (input_file_stream == NULL) {
    printf("Unable to open input file %s\n", argv[1]);
    return 0;
  }

  #define ALPHA_COUNT 26
  int alpha_freq[ALPHA_COUNT];
  int non_ltr_cnt, ctrl_char_cnt;
  initialize(alpha_freq, ALPHA_COUNT, &ctrl_char_cnt, &non_ltr_cnt);
  wc(input_file_stream, alpha_freq, &ctrl_char_cnt, &non_ltr_cnt);
  print_freqs(alpha_freq, ALPHA_COUNT, &ctrl_char_cnt, &non_ltr_cnt);
  fclose(input_file_stream);

  // postcondition: test students function to ensure that their function
  // has accounted for all the characters in the file ...
  // this is done by comparing the total frequency count reported by student with
  // the size of the file.
  // Read the tutorial handout to learn more about the assert macro.
  int file_size = non_ltr_cnt + ctrl_char_cnt;
  for (int i = 0; i < ALPHA_COUNT; ++i) {
    file_size += alpha_freq[i];
  }
  struct stat st; 
  if (stat(argv[1], &st) == 0) {
    assert((int)st.st_size == file_size);
  }

  return 0;
}
