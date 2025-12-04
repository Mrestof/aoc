#include <stdbool.h>
#include <stdio.h>

#include "myutils.h"

#define MAXLINE 141 // content + 1 newline
#define MAXLINES 140

#define MAXINPUT (MAXLINE*MAXLINES)
char input[MAXINPUT];
char *lines[MAXLINES];
int nlines;

#define NRP '.' // empty place
#define RP '@' // roll of paper
#define MAX_ADJ_RPS 3

bool is_rp_accessible(int nl, int nc) {
  int lb, rb, tb, bb;
  int n_adj_rp = 0;

  lb = nc == 0 ? nc : nc - 1;
  tb = nl == 0 ? nl : nl - 1;
  rb = lines[nl][nc+1] == '\0' ? nc : nc + 1;
  bb = nl + 1 == nlines ? nl : nl + 1;

  for (nl = tb; nl <= bb; nl++)
    for (nc = lb; nc <= rb; nc++) {
      if (lines[nl][nc] == RP)
        n_adj_rp++;
      if (n_adj_rp > MAX_ADJ_RPS + 1)  // +1 rp at [nt][nc]
        return false;
    }

  return true;
}

long long remove_rps(bool dry) {
  int nl, nc;
  int nrp = 0;
  for (nl = 0; nl < nlines; nl++)
    for (nc = 0; lines[nl][nc] != '\0'; nc++)
      if (lines[nl][nc] == RP && is_rp_accessible(nl, nc)) {
        if (!dry) lines[nl][nc] = NRP;
        nrp++;
      }
  return nrp;
}

long long part1() {
  return remove_rps(true);
}

long long part2() {
  int tnrp = 0, nrp;
  while ((nrp = remove_rps(false)) > 0)
    tnrp += nrp;
  return tnrp;
}

int main() {
  nlines = readall(input, lines, MAXINPUT, MAXLINE);
  printf("part1: %lld\n", part1());
  printf("part2: %lld\n", part2());
  return 0;
}
