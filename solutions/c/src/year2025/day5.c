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
    lines[nl][i] = RSEP;
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

// all possible combination of two ranges: base and {1..6}
//
//            f0     t0
// base:      |------|
//         f    t
// 1:      |----|               f0=f
// 2:              |----|       t0=t
// 3:          |----|           -
// 4:      |------------|       f0=f, t0=t
// 5: |----|                    new
// 6:                   |----|  new

// read each range, merge it with one other range if possible, otherwise add it
// as a separate range (this may leave the new array of ranges mergeable, so
// might take a few runs to fully merge)
int merge_ranges(int cr, ll from[], ll to[]) {
  int oldi, newi;
  int cmr = 1;
  bool fcmr;

  for (oldi = 1; oldi < cr; oldi++) {
    fcmr = true;
    for (newi = 0; newi < cmr; newi++) {
      if (from[oldi] < from[newi]) {
        if (to[oldi] < from[newi]) {
          // 5
          continue;
        }
        if (to[oldi] < to[newi]) {
          // 1
          from[newi] = from[oldi];
          fcmr = false;
          continue;
        }
        // 4
        from[newi] = from[oldi];
        to[newi] = to[oldi];
        fcmr = false;
        continue;
      }
      if (from[oldi] > to[newi]) {
        // 6
        continue;
      }
      if (to[oldi] < to[newi]) {
        // 3
        fcmr = false;
        continue;
      }
      // 2
      fcmr = false;
      to[newi] = to[oldi];
    }
    if (fcmr) {
      from[cmr] = from[oldi];
      to[cmr] = to[oldi];
      cmr++;
    }
  }

  return cmr;
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
  ll rf[MAXNR], rt[MAXNR];
  int i;
  int cr, pcr;
  ll cfresh = 0;

  cr = get_ranges(rf, rt);

  do {
    pcr = cr;
    cr = merge_ranges(cr, rf, rt);
  } while (pcr != cr);

  for (i = 0; i < cr; i++) {
    cfresh += rt[i] - rf[i] + 1;
  }

  return cfresh;
}

int main() {
  nlines = readall(input, lines, MAXINPUT, MAXLINE);
  printf("part1: %lld\n", part1());
  printf("part2: %lld\n", part2());
  return 0;
}
