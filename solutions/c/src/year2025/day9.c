#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "myutils.h"

#define MAXLINE 12
#define MAXLINES 500

#define MAXINPUT (MAXLINE*MAXLINES)
static char input[MAXINPUT];
static char *lines[MAXLINES];
static int nlines;

typedef struct {
  int x, y;
} Tile;

typedef struct {
  Tile *a, *b;
  ll area;
} Rect;

static Tile tiles[MAXLINES];
static int ntiles;
static Rect rects[MAXLINES*MAXLINES];
static int nrects;

static void get_tiles() {
  Tile *t;
  ntiles = 0;
  for (int i = 0; i < nlines; i++) {
    t = &tiles[i];
    sscanf(lines[i], "%d,%d", &t->x, &t->y);
    ntiles++;
  }
}

static void get_rects() {
  Rect *r;
  nrects = 0;
  for (int i = 0; i < ntiles; i++) {
    for (int j = i+1; j < ntiles; j++) {
      r = &rects[nrects++];
      r->a = &tiles[i];
      r->b = &tiles[j];
      r->area = (ll)(abs(r->a->x - r->b->x)+1) * (ll)(abs(r->a->y - r->b->y)+1);
    }
  }
}

static ll part1() {
  get_tiles();
  get_rects();
  ll max = 0;
  for (int i = 0; i < nrects; i++)
    if (max < rects[i].area)
      max = rects[i].area;
  return max;
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
