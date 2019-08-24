#include "levelheavy.h"

const int FAIL = 0;
const int SUCCESS = 1;
const int DROP = 2;

LevelHeavy::LevelHeavy(Action *a): SpecAction{a} {}

int LevelHeavy::left(Block *b) {
  int left = currAct->left(b);
  if (left == FAIL) return FAIL;
  else if (left == DROP) return DROP;
  if (currAct->down(b) == FAIL) return DROP;
  return SUCCESS;
}

int LevelHeavy::right(Block *b) {
  int right = currAct->right(b);
  if (right == FAIL) return FAIL;
  else if (right == DROP) return DROP;
  if (currAct->down(b) == FAIL) return DROP;
  return SUCCESS;
}

int LevelHeavy::clockwise(Block *b) {
  int cl = currAct->clockwise(b);
  if (cl == FAIL) return FAIL;
  else if (cl == DROP) return DROP;
  if (currAct->down(b) == FAIL) return DROP;
  return SUCCESS;
}

int LevelHeavy::cclockwise(Block *b) {
  int cc = currAct->cclockwise(b);
  if (cc == FAIL) return FAIL;
  else if (cc == DROP) return DROP;
  if (currAct->down(b) == FAIL) return DROP;
  return SUCCESS;
}
