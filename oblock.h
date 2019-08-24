#ifndef _OBLOCK_H_
#define _OBLOCK_H_

#include <string>
#include <iostream>
#include "block.h"


class OBlock: public Block {
    public:
      OBlock(Grid *g, int lvl);
      ~OBlock();
      void createBlock() override;
      bool clockwise() override;
      bool cclockwise() override;
};

#endif
