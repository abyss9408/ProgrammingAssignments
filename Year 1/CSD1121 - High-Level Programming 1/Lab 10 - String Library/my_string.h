#ifndef MY_STRING_H
#define MY_STRING_H

#include <stddef.h>

// https://en.cppreference.com/w/c/string/byte/strlen
size_t my_strlen(const char* str);

// https://en.cppreference.com/w/c/string/byte/strcpy
char* my_strcpy(char* dest, const char* src);

// https://en.cppreference.com/w/c/string/byte/strcat
char* my_strcat(char* dest, const char* src);

// https://en.cppreference.com/w/c/string/byte/strcmp
int my_strcmp(const char* lhs, const char* rhs);

// https://en.cppreference.com/w/c/string/byte/strstr
char* my_strstr(const char* str, const char* substr);

#endif
