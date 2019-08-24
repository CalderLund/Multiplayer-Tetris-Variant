#ifndef _LBLOCK_H_
#define _LBLOCK_H_

#include <string>
#include <iostream>
#include "block.h"


class LBlock: public Block {
    public:
      LBlock(Grid *g, int lvl);
      ~LBlock();
      void createBlock() override;
      bool clockwise() override;
      bool cclockwise() override;
};

#endif
