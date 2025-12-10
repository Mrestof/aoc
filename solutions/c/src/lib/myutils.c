#include <math.h>
#include <string.h>
#include <stdio.h>

#include "myutils.h"

bool is_prime(long num) {
  if (num < 2) return false;
  double max_factor = sqrt(num);
  for (long a = 2; a <= max_factor; a++)
    if (num % a == 0) return false;
  return true;
}

double distance(Point *p1, Point *p2) {
  return sqrt(
    pow((p1->x - p2->x), 2)
    + pow((p1->y - p2->y), 2)
    + pow((p1->z - p2->z), 2)
  );
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void swapb(bool *a, bool *b) {
  bool tmp = *a;
  *a = *b;
  *b = tmp;
}

void reverse(char s[]) {
  int i, j;
  char c;

  for (j = 0; s[j] != '\0'; ++j);
  --j;

  for (i = 0; i < j; ++i, --j) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

int find_str(const char s[], char * const in[], const int in_len) {
  int i;

  for (i = 0; i < in_len; i++)
    if (strcmp(s, in[i]) == 0)
      return i;

  return -1;
}

int readline_from_stdin(char s[], int lim) {
  int c, i;

  for (i=0; (c=getchar())!=EOF && c!='\n'; ++i)
    if (i < lim-1)
      s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';

  return i;
}

// read stdin until EOF, write it to `input`, replace every \n with \0, set
// pointers in `lines` to point to strings in `input`, return the amount of
// pointers to lines
int readall(char *input, char *lines[], int lim, int line_lim) {
  char line[line_lim];
  int i = 0, nline = 0;
  char *line_p;
  int len = 0;
  int total_len = 0;

  while ((len = readline_from_stdin(line, line_lim)) > 0) {
    total_len += len;
    if (total_len > lim) {
      puts("error: input lim exceeded");
      return -1;
    }
    strcat(input, line);
  }

  for (i = nline = 0, line_p = &input[0]; input[i] != '\0'; i++) {
    if (input[i] == '\n') {
      input[i] = '\0';
      lines[nline++] = line_p;
      line_p = &input[i+1];
    }
  }
  if (input[i-1] != '\0')
    lines[nline++] = line_p;

  return nline;
}
