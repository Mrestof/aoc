#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "myutils.h"

#define MAXLINE 200
#define MAXLINES 300

#define MAXINPUT (MAXLINE*MAXLINES)
char input[MAXINPUT] = {0};
char *lines[MAXLINES];
int nlines = 0;

int largest_joltage_p1(char r[]) {
  int i = 0;
  int maxi = 0;
  char jolts[2] = {0};

  for (i = 0; r[i+1] != '\0'; i++)
    if (r[maxi] < r[i])
      maxi = i;
  jolts[0] = r[maxi];

  maxi++;

  for (i = maxi; r[i] != '\0'; i++)
    if (r[maxi] < r[i])
      maxi = i;
  jolts[1] = r[maxi];

  return atoi(jolts);
}

int largest_joltage_p2(char r[]) {
  int i = 0;
  int maxi = 0;
  char jolts[2] = {0};

  for (i = 0; r[i+1] != '\0'; i++)
    if (r[maxi] < r[i])
      maxi = i;
  jolts[0] = r[maxi];

  maxi++;

  for (i = maxi; r[i] != '\0'; i++)
    if (r[maxi] < r[i])
      maxi = i;
  jolts[1] = r[maxi];

  return atoi(jolts);
}

int shared(int lj(char [])) {
  int nl = 0;
  int sum = 0;
  for (nl = 0; nl < nlines; nl++)
    sum += lj(lines[nl]);
  return sum;
}

int main() {
  nlines = readall(input, lines, MAXINPUT, MAXLINE);
  printf("part1: %d\n", shared(largest_joltage_p1));
  printf("part2: %d\n", shared(largest_joltage_p2));
  return 0;
}
