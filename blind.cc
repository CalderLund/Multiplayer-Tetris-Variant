#include "blind.h"

Blind::Blind(Action *a): SpecAction{a} {}

char Blind::printchar() {return '?';}
