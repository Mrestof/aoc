#include <stdio.h>
#include <stdlib.h>

#include "myutils.h"

#define MAXLINE 8

int get_rot(char line[]) {
  int num = atoi(&line[1]);
  if (line[0] == 'R')
    return num;
  else
    return -num;
}

int main() {
  char line[MAXLINE];
  int cur_rot = 50;
  int zero_counter = 0;
  while (readline(line, MAXLINE) > 0) {
    cur_rot = (cur_rot + get_rot(line)) % 100;
    if (cur_rot == 0)
      zero_counter++;
  }
  printf("answer: %d", zero_counter);
  return 0;
}
