#include "oblock.h"
using namespace std;

OBlock::OBlock(Grid *g, int lvl) : Block{g, 'O', lvl} {
    createBlock();
}

OBlock::~OBlock() {}

void OBlock::createBlock() {
    cell1 = theGrid->get_cell(0, 3);
    cell2 = theGrid->get_cell(1, 3);
    cell3 = theGrid->get_cell(0, 2);
    cell4 = theGrid->get_cell(1, 2);
    
    if (cell1->get_type() == ' '
        && cell2->get_type() == ' '
        && cell3->get_type() == ' '
        && cell4->get_type() == ' ')
    {
        cell1->set_type('O');
        cell2->set_type('O');
        cell3->set_type('O');
        cell4->set_type('O');
        
        cell1->set_block(this);
        cell2->set_block(this);
        cell3->set_block(this);
        cell4->set_block(this);
        
        numcell = 4;
        created = true;
    }
}

bool OBlock::clockwise() {return false;} // when this is called, act as if no rotation happened, for the Heavy class

bool OBlock::cclockwise() {return false;}

