#include "lock.h"
#include <iostream>

using namespace std;

const int FAIL = 0;
const int SUCCESS = 1;
const int DROP = 2;

Lock::Lock(Action *a): SpecAction{a} {}

int Lock::clockwise(Block *b) {return FAIL;}
int Lock::cclockwise(Block *b) {return FAIL;}
