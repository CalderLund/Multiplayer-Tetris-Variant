#include "specheavy.h"

const int FAIL = 0;
const int SUCCESS = 1;
const int DROP = 2;

SpecHeavy::SpecHeavy(Action *a): SpecAction{a} {}

int SpecHeavy::right(Block *b) {
  int right = currAct->right(b);
  if (right == FAIL) return FAIL;
  if (right == DROP) return DROP;
  if (currAct->down(b) == FAIL) return DROP; // down only returns success or fail
  if (currAct->down(b) == FAIL) return DROP;
  return SUCCESS;
}

int SpecHeavy::left(Block *b) {
  int left = currAct->left(b);
  if (left == FAIL) return FAIL;
  if (left == DROP) return DROP;
  if (currAct->down(b) == FAIL) return DROP; // down only returns success or fail
  if (currAct->down(b) == FAIL) return DROP;
  return SUCCESS;
}

