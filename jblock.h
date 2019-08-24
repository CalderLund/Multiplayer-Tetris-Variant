#ifndef _JBLOCK_H_
#define _JBLOCK_H_

#include <string>
#include <iostream>
#include "block.h"


class JBlock: public Block {
    public:
      JBlock(Grid *g, int lvl);
      ~JBlock();
      void createBlock() override;
      bool clockwise() override;
      bool cclockwise() override;
};

#endif
