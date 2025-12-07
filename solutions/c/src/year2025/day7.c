#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "myutils.h"

#define MAXLINE 200
#define MAXLINES 200

#define MAXINPUT (MAXLINE*MAXLINES)
static char input[MAXINPUT];
static char *lines[MAXLINES];
static int nlines;

static ll part1() {
  char c;
  int nl, nc;
  int bn = 0;
  bool beams[MAXLINE] = {0};

  for (nc = 0; lines[0][nc] != 'S'; nc++);
  beams[nc] = true;

  for (nl = 2; nl < nlines; nl++) {
    for (nc = 0; (c = lines[nl][nc]) != '\0'; nc++) {
      if (c == '^' && beams[nc]) {
        bn++;
        beams[nc] = false;
        beams[nc-1] = beams[nc+1] = true;
      }
    }
  }

  return bn;
}

typedef struct splitter {
  ll timelines;
  struct splitter *left, *right;
} splitter;

static splitter *new_splitter(int timelines) {
  splitter *s = malloc(sizeof *s);
  if (!s) exit(1);
  s->timelines = timelines;
  s->left = s->right = NULL;
  return s;
}

static splitter *find_below(int nl, int nc, splitter *splitters[MAXLINES][MAXLINE]) {
  while (nl < nlines)
    if (lines[nl++][nc] == '^') {
      if (splitters[nl][nc] == NULL)
        return splitters[nl][nc] = new_splitter(0);
      else
        return splitters[nl][nc];
    }
  return NULL;
}

static ll count_timelines(splitter *s) {
  if (s->timelines != 0)
    return s->timelines;

  if (s->left != NULL)
    s->timelines += count_timelines(s->left);
  else
    s->timelines++;

  if (s->right != NULL)
    s->timelines += count_timelines(s->right);
  else
    s->timelines++;

  return s->timelines;
}

static ll part2() {
  int nl, nc;
  splitter *s;
  splitter *root = NULL;
  splitter *splitters[MAXLINES][MAXLINE] = {NULL};

  for (nc = 0; lines[2][nc] != '^'; nc++);
  root = new_splitter(0);
  splitters[2][nc] = root;

  for (nl = 2; nl < nlines; nl++) {
    for (nc = 0; nc < MAXLINE; nc++) {
      if ((s = splitters[nl][nc]) != NULL) {
        s->left = find_below(nl, nc-1, splitters);
        s->right = find_below(nl, nc+1, splitters);
      }
    }
  }

  return count_timelines(root);
}

int main() {
  nlines = readall(input, lines, MAXINPUT, MAXLINE);
  printf("part1: %lld\n", part1());
  printf("part2: %lld\n", part2());
  return 0;
}
