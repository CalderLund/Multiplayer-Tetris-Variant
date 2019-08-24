#include "zblock.h"
using namespace std;

ZBlock::ZBlock(Grid *g, int lvl) : Block{g, 'Z', lvl} {
    createBlock();
}

ZBlock::~ZBlock() {}

void ZBlock::createBlock() {
    cell1 = theGrid->get_cell(0, 2);
    cell2 = theGrid->get_cell(1, 2);
    cell3 = theGrid->get_cell(1, 3);
    cell4 = theGrid->get_cell(2, 3);
    
    if (cell1->get_type() == ' '
        && cell2->get_type() == ' '
        && cell3->get_type() == ' '
        && cell4->get_type() == ' ')
    {
        cell1->set_type('Z');
        cell2->set_type('Z');
        cell3->set_type('Z');
        cell4->set_type('Z');
        
        cell1->set_block(this);
        cell2->set_block(this);
        cell3->set_block(this);
        cell4->set_block(this);
        
        numcell = 4;
        created = true;
    }
}

bool ZBlock::clockwise() {
    // chooses cell2 as a reference
    int x = cell2->get_x();
    int y = cell2->get_y();
    
    if ((orientation == 0 || orientation == 2) && 
        theGrid->typeAt(x-1, y+1) == ' ' &&
        theGrid->typeAt(x, y-1) == ' ') {
        // sets old cells to be type ' '
        cell3->set_type(' ');
        cell4->set_type(' ');
        
        // disconnects old cells from the block
        cell3->set_block(nullptr);
        cell4->set_block(nullptr);
        
        // connects block to new cells
        cell3 = theGrid->get_cell(x-1, y+1);
        cell4 = theGrid->get_cell(x, y-1);
        
        // sets new cells to be type 'Z'
        cell3->set_type('Z');
        cell4->set_type('Z');
        
        // connects new cells to block
        cell3->set_block(this);
        cell4->set_block(this);
        
        // updates orientation
        ++orientation;
    }
    else if ((orientation == 1 || orientation == 3) &&
             x+1 < theGrid->getWidth() &&
             theGrid->typeAt(x, y+1) == ' ' &&
             theGrid->typeAt(x+1, y+1) == ' ') {
            cell3->set_type(' ');
            cell4->set_type(' ');
            
            cell3->set_block(nullptr);
            cell3->set_block(nullptr);
            
            cell3 = theGrid->get_cell(x, y+1);
            cell4 = theGrid->get_cell(x+1, y+1);
            
            cell3->set_type('Z');
            cell4->set_type('Z');
            
            cell3->set_block(this);
            cell4->set_block(this);
            
            if (orientation == 1) {
                ++orientation;
            }
            else if (orientation == 3) {
                orientation = 0;
            }
        }
    else return false;
    return true;
}

bool ZBlock::cclockwise() {
    // chooses cell2 as a reference
    int x = cell2->get_x();
    int y = cell2->get_y();
    
    if ((orientation == 0 || orientation == 2) && 
        theGrid->typeAt(x-1, y+1) == ' ' &&
        theGrid->typeAt(x, y-1) == ' ') {
        // sets old cells to be type ' '
        cell3->set_type(' ');
        cell4->set_type(' ');
        
        // disconnects old cells from the block
        cell3->set_block(nullptr);
        cell4->set_block(nullptr);
        
        // connects block to new cells
        cell3 = theGrid->get_cell(x-1, y+1);
        cell4 = theGrid->get_cell(x, y-1);
        
        // sets new cells to be type 'Z'
        cell3->set_type('Z');
        cell4->set_type('Z');
        
        // connects new cells to block
        cell3->set_block(this);
        cell4->set_block(this);
        
        // updates orientation
        if (orientation == 0) {
            orientation = 3;
        }
        else if (orientation == 2) {
            --orientation;
        }
    }
    else if ((orientation == 1 || orientation == 3) &&
             x+1 < theGrid->getWidth() &&
             theGrid->typeAt(x, y+1) == ' ' &&
             theGrid->typeAt(x+1, y+1) == ' ') {
            cell3->set_type(' ');
            cell4->set_type(' ');
            
            cell3->set_block(nullptr);
            cell3->set_block(nullptr);
            
            cell3 = theGrid->get_cell(x, y+1);
            cell4 = theGrid->get_cell(x+1, y+1);
            
            cell3->set_type('Z');
            cell4->set_type('Z');
            
            cell3->set_block(this);
            cell4->set_block(this);
            
            --orientation;
        }
    else return false;
    return true;
}
