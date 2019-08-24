#ifndef _LEVEL0_H
#define _LEVEL0_H

#include "level.h"

class Level0: public Level {
    std::ifstream blocks;
  public:
    Level0(std::string file);
    char generatenext(int seed) override;
    Action *generateaction() override;
    void nocleareffect(Grid *) override;
    ~Level0();
};

#endif
