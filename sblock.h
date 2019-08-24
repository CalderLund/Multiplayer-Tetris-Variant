#ifndef _SBLOCK_H_
#define _SBLOCK_H_

#include <string>
#include <iostream>
#include "block.h"


class SBlock: public Block {
    public:
      SBlock(Grid *g, int lvl);
      ~SBlock();
      void createBlock() override;
      bool clockwise() override;
      bool cclockwise() override;
};

#endif
