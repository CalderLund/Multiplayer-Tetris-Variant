#include "normal.h"
#include "block.h"

const int FAIL = 0;
const int SUCCESS = 1;

char Normal::printchar() {return '\0';}

int Normal::left(Block *b) {
  if (b->left()) return SUCCESS;
  return FAIL;
}

int Normal::right(Block *b) {
  if (b->right()) return SUCCESS;
  return FAIL;
}

int Normal::down(Block *b) {
  if (b->down()) return SUCCESS;
  return FAIL;
}

void Normal::drop(Block *b) {b->drop();}

int Normal::clockwise(Block *b) {
  if (b->clockwise()) return SUCCESS;
  return FAIL;
}

int Normal::cclockwise(Block *b) {
  if (b->cclockwise()) return SUCCESS;
  return FAIL;
}
