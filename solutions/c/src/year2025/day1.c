#include <stdio.h>
#include <stdlib.h>

#include "myutils.h"

#define MAXLINE 8
#define MAXLINES 50000
#define MAXINPUT (MAXLINE*MAXLINES)
char input[MAXINPUT] = {0};
char *lines[MAXLINES];
int nlines = 0;

int get_rot(char line[]) {
  int num = atoi(&line[1]);
  if (line[0] == 'R')
    return num;
  else
    return -num;
}

int part1() {
  int cur_rot = 50;
  int zero_counter = 0;

  for (int i = 0; i < nlines; i++) {
    cur_rot = (cur_rot + get_rot(lines[i])) % 100;
    if (cur_rot == 0)
      zero_counter++;
  }

  return zero_counter;
}

int part2() {
  int cur_rot = 50, new_rot = 0, direction = 1;
  int zero_counter = 0;

  for (int i = 0; i < nlines; i++) {
    new_rot = get_rot(lines[i]);
    direction = new_rot / abs(new_rot);
    for (int j = 0; j < abs(new_rot); j++) {
      cur_rot += direction;
      if (cur_rot == 100)
        cur_rot = 0;
      if (cur_rot == -1)
        cur_rot = 99;
      if (cur_rot == 0)
        zero_counter++;
    }
  }

  return zero_counter;
}

int main() {
  nlines = readall(input, lines, MAXINPUT, MAXLINE);
  printf("part1: %d\n", part1());
  printf("part2: %d\n", part2());
  return 0;
}
