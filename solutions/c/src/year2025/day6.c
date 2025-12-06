#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "myutils.h"

#define MAXLINE 5000
#define MAXLINES 50

#define MAXINPUT (MAXLINE*MAXLINES)
char input[MAXINPUT];
char *lines[MAXLINES];
int nlines;

#define MAXCOLS 1500
#define MAXROWS 10

// read numbers from `lines` into `nums`, return the amount of columns and rows
// written to `nums` via `nc` and `nr` respectively
void readnums(int nums[MAXROWS][MAXCOLS], int *nc, int *nr) {
  char c;
  int row, col;
  int num;

  *nr = nlines - 1;

  for (row = 0; row < *nr; row++) {
    *nc = -1;  // crutch? maybe, but who cares
    num = 0;
    for (col = 0; (c = lines[row][col]) != '\0'; col++) {
      if (isspace(c) && num > 0) {
        nums[row][*nc] = num;
        num = 0;
      }
      else if (isdigit(c)) {
        if (num == 0)
          ++*nc;
        num = num * 10 + c - '0';
      }
    }
    if (num > 0)
      nums[row][*nc] = num;
  }

  ++*nc;
}

void readops(char ops[MAXCOLS], int nr) {
  char c;
  int i, col;
  for (i = 0; (c = lines[nr][i]) != '\0'; i++) {
    if (!isblank(c))
      ops[col++] = c;
  }
}

void makeops(
  ll results[MAXCOLS],
  int nums[MAXROWS][MAXCOLS],
  char ops[MAXCOLS],
  int nc,
  int nr
) {
  char op;
  int row, col;

  for (col = 0; col < nc; col++) {
    results[col] = nums[0][col];
    op = ops[col];
    for (row = 1; row < nr; row++) {
      switch (op) {
      case '+':
        results[col] += nums[row][col];
        break;
      case '*':
        results[col] *= nums[row][col];
        break;
      }
    }
  }
}

ll part1() {
  int i;
  int nums[MAXROWS][MAXCOLS], nc, nr;
  ll results[MAXCOLS];
  char ops[MAXCOLS];
  ll sum;

  readnums(nums, &nc, &nr);
  readops(ops, nr);
  makeops(results, nums, ops, nc, nr);

  sum = 0;
  for (i = 0; i < nc; i++)
    sum += results[i];

  return sum;
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
