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

bool is_silly(char num[18]) {
  int len;
  for (len = 0; num[len] != '\0'; len++);
  if (len % 2 != 0)
    return false;

  for (int i = 0, j = len / 2; j < len; i++, j++)
    if (num[i] != num[j])
      return false;

  return true;
}

long long part1() {
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
      if (is_silly(cur)) {
        res += n;
      }
    }
  }

  return res;
}

long long part2() {
  return 0;
}

int main() {
  nlines = readall(input, lines, MAXINPUT, MAXLINE);
  printf("part1: %lld\n", part1());
  printf("part2: %lld\n", part2());
  return 0;
}
