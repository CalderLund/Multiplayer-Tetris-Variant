#ifndef _LEVEL1_H
#define _LEVEL1_H

#include "level.h"

class Level1: public Level {
  public:
    Level1();
    char generatenext(int seed) override;
    Action *generateaction() override;
    void nocleareffect(Grid *) override;
};

#endif
