#ifndef _IBLOCK_H_
#define _IBLOCK_H_

#include <string>
#include <iostream>
#include "block.h"


class IBlock: public Block {
    bool performRotation(Cell *ref_cell, int direction);  // Rotates the block accordingly to its orientation
    public:
      IBlock(Grid *g, int lvl);
      ~IBlock();
      void createBlock() override;
      bool clockwise() override;
      bool cclockwise() override;
};

#endif
