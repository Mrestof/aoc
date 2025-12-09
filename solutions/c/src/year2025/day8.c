#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "myutils.h"

#define MAXLINE 20
#define MAXLINES 1500

#define MAXINPUT (MAXLINE*MAXLINES)
static char input[MAXINPUT];
static char *lines[MAXLINES];
static int nlines;

typedef struct JunctionBox {
  Point pos;
  struct JunctionBox *adj[MAXLINES];
} JunctionBox;

typedef struct {
  JunctionBox *b1, *b2;
  double distance;
} Pair;

static Pair pairs[MAXLINES*MAXLINES];
static int npairs = 0;
static JunctionBox jboxes[MAXLINES] = {0};
static int njboxes = 0;

static int int_cmp(const void *a, const void *b) {
  int n1 = *(const int *)a;
  int n2 = *(const int *)b;
  if (n1 < n2) return -1;
  if (n1 > n2) return 1;
  return 0;
}

static int pair_cmp(const void *a, const void *b) {
  Pair p1 = *(const Pair *)a;
  Pair p2 = *(const Pair *)b;
  if (p1.distance < p2.distance) return -1;
  if (p1.distance > p2.distance) return 1;
  return 0;
}

static void get_boxes() {
  int i;
  JunctionBox *b;
  for (i = 0; i < nlines; i++) {
    b = &jboxes[i];
    sscanf(lines[i], "%lf,%lf,%lf", &b->pos.x, &b->pos.y, &b->pos.z);
    njboxes++;
  }
}

static void get_pairs() {
  int i, j;
  Pair *pair;
  for (i = 0; i < njboxes; i++) {
    for (j = i+1; j < njboxes; j++) {
      pair = &pairs[npairs++];
      pair->b1 = &jboxes[i];
      pair->b2 = &jboxes[j];
      pair->distance = distance(&pair->b1->pos, &pair->b2->pos);
    }
  }
}

static bool in_circuit(JunctionBox *prev, JunctionBox *b1, JunctionBox *b2) {
  for (int i = 0; b1->adj[i] != NULL; i++) {
    if (prev != NULL && b1->adj[i] == prev)
      continue;
    if (b1->adj[i] == b2)
      return true;
    if (in_circuit(b1, b1->adj[i], b2))
      return true;
  }
  return false;
}

static void add_adj(JunctionBox *target, JunctionBox *new) {
  int i;
  for (i = 0; target->adj[i] != NULL; i++);
  target->adj[i] = new;
}

static void connect_pair(Pair p) {
  if (!in_circuit(NULL, p.b1, p.b2)) {
    add_adj(p.b1, p.b2);
    add_adj(p.b2, p.b1);
  }
}

static size_t get_jbox_idx(JunctionBox *addr) {
  JunctionBox *base = jboxes;
  return addr - base;
}

static int count_boxes_in_circuit(
  JunctionBox *prev,
  JunctionBox *b,
  bool seen[MAXLINES]
) {
  int sum = 1;
  seen[get_jbox_idx(b)] = true;
  for (int i = 0; b->adj[i] != NULL; i++) {
    if (prev != NULL && b->adj[i] == prev)
      continue;
    sum += count_boxes_in_circuit(b, b->adj[i], seen);
  }
  return sum;
}

static int eval_circuits() {
  int i, ncl;
  int res;
  bool seen[MAXLINES] = {0};
  int ciruit_length[MAXLINES];
  for (i = 0; i < njboxes; i++) {
    if (seen[i]) continue;
    ciruit_length[ncl++] = count_boxes_in_circuit(NULL, &jboxes[i], seen);
  }
  qsort(ciruit_length, ncl, sizeof(int), int_cmp);
  res = 1;
  for (i = 0; i < 3; i++)
    res *= ciruit_length[ncl-i-1];
  return res;
}

static ll part1() {
  int i;
  int pairs_to_connect = 0;

  get_boxes();
  get_pairs();

  qsort(pairs, npairs, sizeof(Pair), pair_cmp);

  // separate limit for test and actual data as per the puzzle description
  pairs_to_connect = npairs < 1000 ? 10 : 1000;
  for (i = 0; i < pairs_to_connect; i++)
    connect_pair(pairs[i]);

  return eval_circuits();
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
