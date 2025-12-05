#include <stdbool.h>
#include <stdio.h>

#include "myutils.h"

#define MAXLINE 50
#define MAXLINES 2000

#define MAXINPUT (MAXLINE*MAXLINES)
char input[MAXINPUT];
char *lines[MAXLINES];
int nlines;

#define MAXNR 200 // max number of ranges

ll part1() {
  return 0;
}

ll part2() {
  return 0;
}

int main() {
  nlines = readall(input, lines, MAXINPUT, MAXLINE);
  printf("part1: %lld\n", part1());
  printf("part2: %lld\n", part2());
  return 0;
}
