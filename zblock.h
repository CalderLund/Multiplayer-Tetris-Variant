#ifndef _LBLOCK_Z_
#define _LBLOCK_Z_

#include <string>
#include <iostream>
#include "block.h"


class ZBlock: public Block {
    public:
      ZBlock(Grid *g, int lvl);
      ~ZBlock();
      void createBlock() override;
      bool clockwise() override;
      bool cclockwise() override;
};

#endif
