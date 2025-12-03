#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "myutils.h"

#define MAXLINE 1000
#define MAXLINES 10

#define MAXINPUT (MAXLINE*MAXLINES)
char input[MAXINPUT] = {0};
char *lines[MAXLINES];
int nlines = 0;

#define SEP ','
#define RSEP '-'

int get_range(unsigned int n, char from[18], char to[18]) {
  int i = 0, j = 0;

  for (i = 0; n > 0; i++)
    if (input[i] == SEP)
      n--;

  for (j = 0; (from[j] = input[i]) != RSEP; i++, j++);
  from[j] = '\0';
  i++;
  for (j = 0; (to[j] = input[i]) != SEP && to[j] != '\0'; i++, j++);
  to[j] = '\0';

  return 0;
}

bool is_silly_p1(char num[18]) {
  int len;
  for (len = 0; num[len] != '\0'; len++);
  if (len % 2 != 0)
    return false;

  for (int i = 0, j = len / 2; j < len; i++, j++)
    if (num[i] != num[j])
      return false;

  return true;
}

bool is_silly_p2(char num[18]) {
  int len, subl, p;

  for (len = 0; num[len] != '\0'; len++);

  for (subl = 1; subl <= len / 2; subl++) {
    if (len % subl != 0)
      continue;
    for (p = 0; p < len / subl - 1; p++) {
      for (int i = p * subl, j = (p+1) * subl; i < (p+1) * subl; i++, j++)
        if (num[i] != num[j])
          goto ls;
    }
    return true;
ls:
    ;
  }

  return false;
}

long long part(int p) {
  int i = 0;
  int rn = 0;
  char a[18] = {0}, b[18] = {0}, cur[18] = {0};
  long long ai = 0, bi = 0;
  long long res = 0;

  for (i = rn = 0; input[i] != '\0'; i++)
    if (input[i] == SEP)
      rn++;

  for (i = 0; i <= rn; i++) {
    get_range(i, a, b);
    ai = atoll(a);
    bi = atoll(b);
    for (long long n = ai; n <= bi; n++){
      sprintf(cur, "%lld", n);
      if (p == 1)
        if (is_silly_p1(cur))
          res += n;
      if (p == 2)
        if (is_silly_p2(cur))
          res += n;
    }
  }

  return res;
}

int main() {
  nlines = readall(input, lines, MAXINPUT, MAXLINE);
  printf("part1: %lld\n", part(1));
  printf("part2: %lld\n", part(2));
  return 0;
}
