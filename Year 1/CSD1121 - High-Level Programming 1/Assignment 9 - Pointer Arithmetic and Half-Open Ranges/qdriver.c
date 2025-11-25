/*!__________________________________________________________________________
@filename   qdriver.c 
@author(s)  Prasanna Ghali 
@DP emails  pghali@digipen.edu
@course     High-Level Programming 1 
@assignment Assignment on pointer arithmetic and half-open ranges
@due date   see course web page
 
Brief Description: 
This file contains the driver main function for assignment on pointer
arithmetic and half-open ranges  
*//*_________________________________________________________________________*/

/*                                                                  includes
_____________________________________________________________________________*/
#include <stdio.h>   // printf
#include <string.h>  // strlen
#include <stdlib.h>  // atoi
#include "q.h"       // assignment prototypes

/*                                                                  functions
The static specifier means these functions are private to this source file.
More specifically, the static specifier is used by programmers to tell the
compiler to not export the function name to the linker, thereby keeping the
function name private to this source file.
_____________________________________________________________________________*/
static void test1(FILE *output_stm);  // unit tests for find
static void test2(FILE *output_stm);  // unit tests for find_any
static void test3(FILE *output_stm);  // unit tests for count 
static void test4(FILE *output_stm);  // unit tests for count_any
static void test5(FILE *output_stm);  // unit tests for compare
static void test6(FILE *output_stm);  // unit tests for exchange
static void test7(FILE *output_stm);  // unit tests for copy

static unsigned ut_rand(void);            // returns a random 32-bit integer
static void ut_srand(unsigned, unsigned); // seed the generator
static int RandomInt(int low, int high);  // get random value in range [low, high]

/*                                                                  functions
// to run unit test defined in the above test?() functions, run the 
// program like this: ./q.out ? myoutput?.txt
// where ? is a wild card character that is equivalent to one of 
// 1 or 2 or 3 or 4 or 5 or 6 or 7
// compare your output with the correct output like this:
// diff -y --strip-trailing-cr --suppress-common-lines myoutput?.txt output?.txt
// 
// to run all unit tests, do this:
// ./q.out 0 all-output.txt
_____________________________________________________________________________*/
int main(int argc, char *argv[]) {
  // sanity check for correct input ...
  if (argc < 3) {
    fprintf(stderr, "Usage: ./q.out test-case-value output-file-name\n");
    return 0;
  }
  
  // Test is type name for pointer to "function that takes FILE* and returns nothing"
  typedef void (*Test)(FILE*);
  // array of pointers to functions ...
  Test tests[]  = { test1, test2, test3, test4, test5, test6, test7 };
  int const cnt = sizeof(tests) / sizeof(*tests);
  int testno    = atoi(argv[1]);
  // sanity check on value entered by user
  testno = (testno > cnt) ? 0 : testno;
  testno = (testno <   0) ? 0 : testno;
  
  FILE *output_stm = fopen(argv[2], "w"); // open output file
  if (NULL == output_stm) {
    fprintf(stderr, "Unable to create output file %s\n", argv[2]);
    return 0;
  }

  // if testno is 0, run all tests
  ut_srand(3, 4); // seed the random number generator
  if (0 == testno) {
    for (int i = 0; i < cnt; i++) {
      tests[i](output_stm);
    }
  } else {
    tests[testno - 1](output_stm);
  }
  fclose(output_stm);
  return 0;
}

// unit tests for function find ...
void test1(FILE *output_stm) {
  char const *string = "abcdefghijklmnopqrstuvwxyz";
  int length         = strlen(string);

  // print header to output stream ...
  fprintf(output_stm, "============ test1 ============\n");
  // print digits to relate characters in string with subscripts
  fprintf(output_stm, "01234567890123456789012345\n");
  fprintf(output_stm, "%s\n", string);
  
  char const *bytes = "aimzX1", *found; // found is char const*
  while (*bytes) {
    found = find(string, string + length, *bytes);
    if (found) {
      fprintf(output_stm, "Found '%c' at offset %li\n", 
             *bytes, (long int)(found - string));
    } else {
      fprintf(output_stm, "Didn't find byte: %c\n", *bytes);
    }
    bytes++;
  }

  found = find(string + 10, string + 20, 'z');
  if (found) {
    fprintf(output_stm, "Found z at offset %li\n", (long int)(found - string));
  } else {
    fprintf(output_stm, "Didn't find z\n");
  }

  found = find(string + 10, string + 20, 'p');
  if (found) {
    fprintf(output_stm, "Found p at offset %li\n", (long int)(found - string));
  } else {
    fprintf(output_stm, "Didn't find p\n");
  }

  found = find(string, string, 'a');
  if (found) {
    fprintf(output_stm, "Found a at offset %li\n", (long int)(found - string));
  } else {
    fprintf(output_stm, "Didn't find a\n");
  }

  found = find(string, string, 'b');
  if (found) {
    fprintf(output_stm, "Found b at offset %li\n", (long int)(found - string));
  } else {
    fprintf(output_stm, "Didn't find b\n");
  }
}

// unit tests for function find_any ...
void test2(FILE *output_stm) {
  char const *string = "There's a fine line between clever and stupid.";
  int length         = strlen(string);
  
  // print header to output stream ...
  fprintf(output_stm, "============ test2 ============\n");
  // print digits to relate characters in string with subscripts
  fprintf(output_stm, "012345678901234567890123456789012345678901234567890\n");
  fprintf(output_stm, "%s\n", string);

  const char *bytes = "gjkqxyz";
  const char *found = find_any(string, string + length, bytes, strlen(bytes));
  if (found) {
    fprintf(output_stm, "Found '%c' at offset %li\n", 
           *found, (long int)(found - string));
  } else {
    fprintf(output_stm, "Didn't find any bytes: %s\n", bytes);
  }

  bytes = "gjkqxybz";
  found = find_any(string, string + length, bytes, strlen(bytes));
  if (found) {
    fprintf(output_stm, "Found '%c' at offset %li\n", 
        *found, (long int)(found - string));
  } else {
    fprintf(output_stm, "Didn't find any bytes: %s\n", bytes);
  }
}

// unit test for function count ...
void test3(FILE *output_stm) {
  char const *string = "There's a fine line between clever and stupid.";
  int length         = strlen(string);
  
  // print header to output stream ...
  fprintf(output_stm, "============ test3 ============\n");
  fprintf(output_stm, "012345678901234567890123456789012345678901234567890\n");
  fprintf(output_stm, "%s\n", string);

  char const *bytes = "aeiou";
  while (*bytes) {
    int cnt = count(string, string + length, *bytes);
    fprintf(output_stm, "Found %i occurrences of '%c'\n", cnt, *bytes);    
    bytes++;
  }
}

// unit tests for function count_any ...
void test4(FILE *output_stm) {
  char const *string = "There's a fine line between clever and stupid.";
  int length         = strlen(string);

  // print header to output stream ...
  fprintf(output_stm, "============ test4 ============\n");
  fprintf(output_stm, "012345678901234567890123456789012345678901234567890\n");
  fprintf(output_stm, "%s\n", string);

  char const *bytes = "aeiou";
  int cnt = count_any(string, string + length, bytes, strlen(bytes));
  fprintf(output_stm, "Found %i occurrences from the set '%s'\n", cnt, bytes);
}

// helper function for test_compare ...
void scanner(FILE *output_stm, const char *loc1, const char *loc2, int cnt) {
  char const *bytes = loc1;
  for (int i = 0; i < cnt; i++) {
    fprintf(output_stm, "%c", *bytes++);
  }
  fprintf(output_stm, "\n");

  bytes = loc2;
  for (int i = 0; i < cnt; i++) {
    fprintf(output_stm, "%c", *bytes++);
  }
  fprintf(output_stm, "\n");
  
  int result = compare(loc1, loc2, cnt);
  if (result == 0) {
    fprintf(output_stm, "The bytes are the same.\n");
  } else if (result < 0) {
    fprintf(output_stm, "The first bytes are less than the second bytes.\n");
  } else {
    fprintf(output_stm, "The first bytes are greater than the second bytes.\n");
  }
}

// unit tests for function compare ...
void test5(FILE *output_stm) {
  /*                    0123456789012345678901234567890 */
  char const *bytes1 = "abccefghijklmnopqrstuvwxyzxxxxx";
  char const *bytes2 = "abcdefxxxxxghijklpqwxyzabcdefxx";

  fprintf(output_stm, "============ test5 ============\n");

  scanner(output_stm, bytes1, bytes2, 3);
  scanner(output_stm, bytes1, bytes2, 4);
  scanner(output_stm, bytes1 + 12, bytes2 + 11, 6);
  scanner(output_stm, bytes1 + 22, bytes2 + 14, 4);
  scanner(output_stm, bytes1 + 10, bytes2 + 15, 1);
  scanner(output_stm, bytes1 +  6, bytes2 + 11, 6);

  while (*bytes1 && *bytes2) {
    scanner(output_stm, bytes1++, bytes2++, 1);
  }
}

void test6(FILE *output_stm) {
  /*               0123456789.123456789.123456789.  */
  /*                         1         2            */
  // print header to output stream ...
  char string[] = "Four score and seven years ago.";
  fprintf(output_stm, "============ test6a ============\n");

  fprintf(output_stm, "BEFORE: %s\n", string);
  exchange(string + 5, string + 15, 5);
  fprintf(output_stm, " AFTER: %s\n", string);
  exchange(string + 0, string + 27, 4);
  fprintf(output_stm, " AFTER: %s\n", string);
  exchange(string + 7, string + 19, 9);
  fprintf(output_stm, " AFTER: %s\n", string);

  // run more unit tests with a different string
  char string2[] = "Any sufficiently advanced technology is "
                   "indistinguishable from magic.";
  int length     = strlen(string2);
  
  #define MAX_EXCHANGES 1000
  int sizes[MAX_EXCHANGES];
  int loffsets[MAX_EXCHANGES];
  int roffsets[MAX_EXCHANGES];

  // print header to output stream ...
  fprintf(output_stm, "============ test6b ============\n");
  fprintf(output_stm, "%s\n", string2);

  int const cnt = 100;
  for (int i = 0; i < cnt; i++) {
    int maxsize = length / 3; 
    int size    = RandomInt(1, maxsize);
    int loffset = RandomInt(0, length - 2 * maxsize);
    int roffset = RandomInt(loffset + size, length - maxsize);
    exchange(string2 + loffset, string2 + roffset, size);
    fprintf(output_stm, "%s\n", string2);
    sizes[i]    = size;
    loffsets[i] = loffset;
    roffsets[i] = roffset;
  }

  fprintf(output_stm, "****************************************************"
                      "*****************\n");
  for (int i = cnt - 1; i >= 0; i--) {
    exchange(string2 + loffsets[i], string2 + roffsets[i], sizes[i]);
    fprintf(output_stm, "%s\n", string2);
  }
}

// unit tests for function copy ...
void test7(FILE *output_stm) {
  //               01234567890123456789012345
  char string1[] = "abcdefghijklmnopqrstuvwxyz";
  char string2[] = 
  //           1         2         3         4         5         6        
  // 012345678901234567890123456789012345678901234567890123456789012345678
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  
  // print header to output stream ...
  fprintf(output_stm, "============ test7 ============\n");
  fprintf(output_stm, "01234567890123456789012345\n");
  fprintf(output_stm, "%s\n", string1);

  copy(string1 + 11, string1 + 6, 10);
  fprintf(output_stm, "%s\n", string1);

  copy(string1 + 5, string1 + 2, 15);
  fprintf(output_stm, "%s\n", string1);

  fprintf(output_stm, "          1         2         3         4         5"
                      "         6        \n");
  fprintf(output_stm, "01234567890123456789012345678901234567890123456789012"
                      "3456789012345678\n");
  fprintf(output_stm, "%s\n", string2);

  copy(string2 + 11, string2 + 6, 9);
  fprintf(output_stm, "%s\n", string2);

  copy(string2 + 19, string2 + 3, 30);
  fprintf(output_stm, "%s\n", string2);

  copy(string2 + 35, string2 + 30, 22);
  fprintf(output_stm, "%s\n", string2);

  copy(string2 + 2, string2 + 1, 3);
  fprintf(output_stm, "%s\n", string2);
}

/************************************************************************/
/* concatenation of following two 16-bit multiply with carry generators */
/* x(n)=a*x(n-1)+carry mod 2^16 and y(n)=b*y(n-1)+carry mod 2^16,       */
/* number and carry packed within the same 32 bit integer.              */
/************************************************************************/

static unsigned int SEED_X = 521288629;
static unsigned int SEED_Y = 362436069;

unsigned ut_rand(void) {
  /* Use any pair of non-equal numbers from this list for "a" and "b"
      18000 18030 18273 18513 18879 19074 19098 19164 19215 19584
      19599 19950 20088 20508 20544 20664 20814 20970 21153 21243
      21423 21723 21954 22125 22188 22293 22860 22938 22965 22974
      23109 23124 23163 23208 23508 23520 23553 23658 23865 24114
      24219 24660 24699 24864 24948 25023 25308 25443 26004 26088
      26154 26550 26679 26838 27183 27258 27753 27795 27810 27834
      27960 28320 28380 28689 28710 28794 28854 28959 28980 29013
      29379 29889 30135 30345 30459 30714 30903 30963 31059 31083
  */
  static unsigned int a = 18000, b = 30903;

  SEED_X = a * (SEED_X & 65535) + (SEED_X >> 16);
  SEED_Y = b * (SEED_Y & 65535) + (SEED_Y >> 16);

  return ((SEED_X << 16) + (SEED_Y & 65535));
}

void ut_srand(unsigned seed1, unsigned seed2) {
  // use default seeds if parameter is 0
  SEED_X = (seed1) ? seed1 : SEED_X;
  SEED_Y = (seed2) ? seed2 : SEED_Y;
}

int RandomInt(int low, int high) {
  int r1 = (int)(ut_rand() / 2 - 1);
  return r1 % (high - low + 1) + low;
}

void testX(FILE *output_stm) {
  char string1[] = "There's a fine line between clever and stupid.";
  int length = strlen(string1);
  
  // Finds 'b' in the range 'fine line between' and returns a pointer to it
  const char *found = find(string1 + 10, string1 + 26, 'b');
  fprintf(output_stm, "Found %c at offset %li\n", *found, (long int)(found - string1));

  // Doesn't find 'z' in the range 'There's a fi' and returns NULL
  found = find(string1, string1 + 11, 'z');

  const char *bytes = "xyzlabc";
  found = find_any(string1, string1 + length, bytes, 7);
  fprintf(output_stm, "Found %c at offset %li\n", *found, (long int)(found - string1));

  // Returns 3, the number of time 'e' is in range 'There's a fine '
  int cnt = count(string1, string1 + 15, 'e');
  fprintf(output_stm, "count is %i\n", cnt);

  // Returns 15, the number of times a vowel appears in the entire string
  bytes = "aeiou";
  cnt = count_any(string1, string1 + length, bytes, 5);
  fprintf(output_stm, "count is %i\n", cnt);

  const char *string2 = "abcdefghijklm", *string3 = "abcdehijklmno";
  //const char *string3 = "abcdehijklmno";
  // Returns 0 as the ranges 'abcde' and 'abcde' are the same
  cnt = compare(string2, string3, 5);
  fprintf(output_stm, "count is %i\n", cnt);

  // Returns negative number as 'abcdef' is less than 'abcdeh'
  cnt = compare(string2, string3, 6);
  fprintf(output_stm, "count is %i\n", cnt);

  // Returns positive number as 'bcd' is greater than 'abc' */
  cnt = compare(string2 + 1, string3, 3);
  fprintf(output_stm, "count is %i\n", cnt);

  // Returns 0 as the ranges 'jklm' and 'jklm' are the same
  cnt = compare(string2 + 9, string3 + 7, 4);
  fprintf(output_stm, "count is %i\n", cnt);

  // Changes string to "There's a line fine between clever and stupid."
  exchange(string1 + 10, string1 + 15, 4);
  fprintf(output_stm, "%s\n", string1);

  // Changes string to "There's a line fine between stupid and clever."
  exchange(string1 + 28, string1 + 39, 6);
  fprintf(output_stm, "%s\n", string1);

  // Changes string to "There's a line line fine between stand clever."
  copy(string1 + 10, string1 + 15, 20);
  fprintf(output_stm, "%s\n", string1);
}
