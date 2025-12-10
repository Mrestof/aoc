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

typedef struct {
  int x1, y1, x2, y2;
} Line;

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

static Tile *find_tile(int x, int y) {
  for (int i = 0; i < ntiles; i++)
    if (tiles[i].x == x && tiles[i].y == y)
      return &tiles[i];
  return NULL;
}

static void get_tiles_on_line(Tile *tiles_on_line[], Line l) {
  int ntol = 0;
  if (l.x1 == l.x2) {
    for (int i = 0; i < ntiles; i++)
      if (tiles[i].x == l.x1) {
        if (l.y1 > l.y2) {
          if (tiles[i].y < l.y1 && tiles[i].y > l.y2)
            tiles_on_line[ntol++] = &tiles[i];
        }
        else
          if (tiles[i].y < l.y2 && tiles[i].y > l.y1)
            tiles_on_line[ntol++] = &tiles[i];
      }
  }
  else if (l.y1 == l.y2)
    for (int i = 0; i < ntiles; i++)
      if (tiles[i].y == l.y1) {
        if (l.x1 > l.x2) {
          if (tiles[i].x < l.x1 && tiles[i].x > l.x2)
            tiles_on_line[ntol++] = &tiles[i];
        }
        else
          if (tiles[i].x < l.x2 && tiles[i].x > l.x1)
            tiles_on_line[ntol++] = &tiles[i];
      }
}

static bool is_valid_direction(Tile *from, int x, int y) {
  Tile *prev, *next;

  if (from == &tiles[0])
    prev = &tiles[ntiles-1];
  else
    prev = from - 1;
  if (from == &tiles[ntiles-1])
    next = &tiles[0];
  else
    next = from + 1;

  // TODO: allow direction anchor points to be on the same line as prev-from or
  // from-next but only if they are in front of those vectors

  // magic happening because my drawings from yesterday told me to
  bool q2 = true, q1 = false, // allowed quadrants for
       q3 = true, q4 = false; // a direction anchor to be
  ll cross = (from->x - prev->x) * (next->y - prev->y) -
             (from->y - prev->y) * (next->x - prev->x);
  if (cross > 0)
    q1 = true;
  else
    q2 = false;

  if (prev->x == from->x)
    if (prev->y > from->y)
      // up
      ;
    else {
      // down
      swapb(&q1, &q3);
      swapb(&q2, &q4);
    }
  else // p.y == f.y
    if (prev->x > from->x) {
      // left
      swapb(&q1, &q4);
      swapb(&q2, &q3);
      swapb(&q1, &q3);
    }
    else {
      // right
      swapb(&q1, &q4);
      swapb(&q2, &q3);
      swapb(&q2, &q4);
    }

  int px = x - from->x;
  int py = y - from->y;
  if (px > 0 && py > 0) return q1;
  if (px < 0 && py > 0) return q2;
  if (px < 0 && py < 0) return q3;
  if (px > 0 && py < 0) return q4;

  return false;
}

static bool is_crossing_lines(Line l) {
  Line tl;
  if (l.x1 == l.x2) {
    for (int i = 0, j = 1; j < ntiles; i++, j++) {
      tl = (Line){tiles[i].x, tiles[i].y, tiles[j].x, tiles[j].y};
      if (tl.x1 == tl.x2)
        continue;
      if (l.y1 > l.y2) {
        if (tiles[i].y > l.y1 && tiles[i].y < l.y2)
          continue;
      }
      else
        if (tiles[i].y > l.y2 && tiles[i].y < l.y1)
          continue;
      if (tl.x1 > tl.x2) {
        if (tl.x1 > l.x1 && tl.x2 < l.x1)
          return true;
      }
      else
        if (tl.x2 > l.x1 && tl.x1 < l.x1)
          return true;
    }
  }
  else
    for (int i = 0, j = 1; j < ntiles; i++, j++) {
      tl = (Line){tiles[i].x, tiles[i].y, tiles[j].x, tiles[j].y};
      if (tl.y1 == tl.y2)
        continue;
      if (l.x1 > l.x2) {
        if (tiles[i].x > l.x1 && tiles[i].x < l.x2)
          continue;
      }
      else
        if (tiles[i].x > l.x2 && tiles[i].x < l.x1)
          continue;
      if (tl.y1 > tl.y2) {
        if (tl.y1 > l.y1 && tl.y2 < l.y1)
          return true;
      }
      else
        if (tl.y2 > l.y1 && tl.y1 < l.y1)
          return true;
    }
  return true;
}

static bool is_valid_line(Line l) {
  int i;
  Tile *t;
  Tile *tiles_on_line[MAXLINES] = {0};

  if (
    (t = find_tile(l.x1, l.y1)) != NULL
    && !is_valid_direction(t, l.x2, l.y2)
  )
    return false;
  if (
    (t = find_tile(l.x2, l.y2)) != NULL
    && !is_valid_direction(t, l.x1, l.y1)
  )
    return false;

  if (is_crossing_lines(l))
    return false;

  get_tiles_on_line(tiles_on_line, l);
  for (i = 0; (t = tiles_on_line[i]) != NULL; i++)
    if (
      !is_valid_direction(t, l.x1, l.y1)
      || !is_valid_direction(t, l.x2, l.y2)
    )
      return false;

  return true;
}

static bool is_valid_rect(Rect r) {
  Line rect_lines[] = {
    {r.a->x, r.a->y, r.b->x, r.a->y},
    {r.a->x, r.a->y, r.a->x, r.b->y},
    {r.b->x, r.b->y, r.b->x, r.a->y},
    {r.b->x, r.b->y, r.a->x, r.b->y},
  };
  for (int i = 0; i < 4; i++) {
    if (!is_valid_line(rect_lines[i]))
      return false;
  }
  return true;
}

static void filter_rects() {
  int new_nrects = 0;
  for (int i = 0; i < nrects; i++) {
    if (is_valid_rect(rects[i]))
      rects[new_nrects++] = rects[i];
  }
  nrects = new_nrects;
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
  get_tiles();
  get_rects();
  filter_rects();
  ll max = 0;
  for (int i = 0; i < nrects; i++)
    if (max < rects[i].area)
      max = rects[i].area;
  return max;
}

int main() {
  nlines = readall(input, lines, MAXINPUT, MAXLINE);
  printf("part1: %lld\n", part1());
  printf("part2: %lld\n", part2());
  return 0;
}
