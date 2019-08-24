#include "specaction.h"
#include "block.h"
#include "normal.h"

SpecAction::SpecAction(Action *action): currAct {action} {}

char SpecAction::printchar() {return currAct->printchar();}
int SpecAction::left(Block *b) {return currAct->left(b);}
int SpecAction::right(Block *b) {return currAct->right(b);}
int SpecAction::down(Block *b) {return currAct->down(b);}
void SpecAction::drop(Block *b) {currAct->drop(b);}
int SpecAction::clockwise(Block *b) {return currAct->clockwise(b);}
int SpecAction::cclockwise(Block *b) {return currAct->cclockwise(b);}

SpecAction::~SpecAction() {delete currAct;}
