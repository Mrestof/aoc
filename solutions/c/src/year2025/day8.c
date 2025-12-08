#include <stdbool.h>
#include <stdio.h>

#include "myutils.h"

#define MAXLINE 20
#define MAXLINES 1500

#define MAXINPUT (MAXLINE*MAXLINES)
static char input[MAXINPUT];
static char *lines[MAXLINES];
static int nlines;

static ll part1() {
  return 0;
}

static ll part2() {
  return 0;
}

int main() {
  nlines = readall(input, lines, MAXINPUT, MAXLINE);
  printf("part1: %lld\n", part1());
  printf("part2: %lld\n", part2());
  return 0;
}
