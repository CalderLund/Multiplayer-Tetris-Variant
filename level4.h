#ifndef _LEVEL4_H
#define _LEVEL4_H

#include "level.h"

class Level4: public Level {
  public:
    char generatenext(int seed);
    Action *generateaction();
    void nocleareffect(Grid *);
};

#endif
