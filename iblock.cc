#include <string>
#include <iostream>
#include "iblock.h"

using namespace std;

IBlock::IBlock(Grid *g, int lvl) : Block{g, 'I', lvl} {
    createBlock();
}

IBlock::~IBlock() {}

void IBlock::createBlock() {
    cell1 = theGrid->get_cell(0, 3);
    cell2 = theGrid->get_cell(1, 3);
    cell3 = theGrid->get_cell(2, 3);
    cell4 = theGrid->get_cell(3, 3);
    
    if (cell1->get_type() == ' '
        && cell2->get_type() == ' '
        && cell3->get_type() == ' '
        && cell4->get_type() == ' ')
    {
        cell1->set_type('I');
        cell2->set_type('I');
        cell3->set_type('I');
        cell4->set_type('I');
        
        cell1->set_block(this);
        cell2->set_block(this);
        cell3->set_block(this);
        cell4->set_block(this);
        
        numcell = 4;
        created = true;
    }
    else {
        created = false;
    }
}

bool IBlock::performRotation(Cell *ref_cell, int direction) {
// leave the bottom cell the same, and go horizontal 3 cells across
//
// direction refers to the new orientation we are trying to achieve AFTER the
// rotation

    int x = ref_cell->get_x();
    int y = ref_cell->get_y();

    int x2, x3, x4, y2, y3, y4 = 0;

    if (direction == 0 || direction == 2) {
      x2 = x + 1;
      x3 = x + 2;
      x4 = x + 3;

      y2 = y;
      y3 = y;
      y4 = y; 
    }
    else if (direction == 1 || direction == 3) {
      y2 = y - 1;
      y3 = y - 2;
      y4 = y - 3;

      x2 = x;
      x3 = x;
      x4 = x; 
    }

    if (x4 < theGrid->getWidth() && theGrid->typeAt(x2, y2) == ' ' 
        && theGrid->typeAt(x3, y3) == ' ' && theGrid->typeAt(x4, y4) == ' ') {
            
      cell2->set_block(nullptr);
      cell3->set_block(nullptr);
      cell4->set_block(nullptr);
      
      cell2->set_type(' ');
      cell3->set_type(' ');
      cell4->set_type(' ');

      cell2 = theGrid->get_cell(x2, y2);
      cell3 = theGrid->get_cell(x3, y3);
      cell4 = theGrid->get_cell(x4, y4);
      
      cell2->set_type('I');
      cell3->set_type('I');
      cell4->set_type('I');
      
      cell2->set_block(this);
      cell3->set_block(this);
      cell4->set_block(this);

      return true;
    }
    return false;
}

bool IBlock::clockwise() {
  // determine current orientation, and rotate according to that
  if (orientation == 0) {
    ++orientation;
  }
  else if (orientation == 1) {
    ++orientation;
  }
  else if (orientation == 2) {
    ++orientation;
  }
  else if (orientation == 3) {
    orientation = 0;
  }

  return performRotation(cell1, orientation);
}

bool IBlock::cclockwise() {
  if (orientation == 0) {
    orientation = 3;
  }
  else if (orientation == 1) {
    orientation = 0;
  }
  else if (orientation == 2) {
    orientation = 1;
  }
  else if (orientation == 3) {
    orientation = 2;
  }

  return performRotation(cell1, orientation);
}
