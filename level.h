#ifndef _LEVEL_H
#define _LEVEL_H

#include <iostream>
#include <fstream>
#include <string>
#include "grid.h"

class Action;

class Level {
  public:
    virtual char generatenext(int seed) = 0;
    virtual Action *generateaction() = 0;
    virtual void nocleareffect(Grid *) = 0;
    virtual ~Level() {};
};

#endif
