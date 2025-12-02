#ifndef MYUTILS_H
#define MYUTILS_H

#include <stdbool.h>

bool is_prime(long a);

void swap(int *a, int *b);
void reverse(char s[]);

// find string `s` in array of strings `in` and return its index or -1 if it's
// not in the array
int find_str(const char s[], char *const in[], const int in_len);

int readline(char s[], int lim);

#endif /* MYUTILS_H */
