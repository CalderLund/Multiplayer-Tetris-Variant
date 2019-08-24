#ifndef _TBLOCK_H_
#define _TBLOCK_H_

#include <string>
#include <iostream>
#include "block.h"


class TBlock: public Block {
    public:
      TBlock(Grid *g, int lvl);
      ~TBlock();
      void createBlock() override;
      bool clockwise() override;
      bool cclockwise() override;
};

#endif
