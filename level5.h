#ifndef _LEVEL5_H
#define _LEVEL5_H

#include "level.h"

class Level5: public Level {
  public:
    char generatenext(int seed);
    Action *generateaction();
    void nocleareffect(Grid *);
};

#endif
