#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "myutils.h"

#define MAXLINE 50
#define MAXLINES 2000

#define MAXINPUT (MAXLINE*MAXLINES)
char input[MAXINPUT];
char *lines[MAXLINES];
int nlines;

#define MAXNR 200 // max number of ranges
#define RSEP '-'
#define DBSEP '\0'

int get_ranges(ll from[], ll to[]) {
  int nl, i;

  for (nl = 0; lines[nl][0] != DBSEP; nl++) {
    for (i = 0; lines[nl][i] != RSEP; i++);
    lines[nl][i] = '\0';
    from[nl] = atoll(lines[nl]);
    to[nl] = atoll(&lines[nl][i+1]);
  }

  return nl;
}

bool is_in_ranges(ll x, int cr, ll from[], ll to[]) {
  int i;
  for (i = 0; i < cr; i++) {
    if (x < from[i])
      continue;
    if (x > to[i])
      continue;
    return true;
  }
  return false;
}

ll part1() {
  ll rf[MAXNR], rt[MAXNR];
  int nl;
  int cr;
  int cfresh = 0;

  cr = get_ranges(rf, rt);

  for (nl = cr+1; nl < nlines; nl++) {
    if (is_in_ranges(atoll(lines[nl]), cr, rf, rt))
      cfresh++;
  }

  return cfresh;
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
