#ifndef _LEVEL2_H
#define _LEVEL2_H

#include "level.h"

class Level2: public Level {
  public:
    char generatenext(int seed) override;
    Action *generateaction() override;
    void nocleareffect(Grid *) override;
};

#endif
