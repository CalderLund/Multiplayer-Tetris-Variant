#include <string>
#include <iostream>
#include "tblock.h"

using namespace std;

TBlock::TBlock(Grid *g, int lvl) : Block{g, 'T', lvl} {
    createBlock();
}

TBlock::~TBlock() {}

void TBlock::createBlock() {
    cell1 = theGrid->get_cell(1, 3);
    cell2 = theGrid->get_cell(0, 2);
    cell3 = theGrid->get_cell(1, 2);
    cell4 = theGrid->get_cell(2, 2);
    
    if (cell1->get_type() == ' '
        && cell2->get_type() == ' '
        && cell3->get_type() == ' '
        && cell4->get_type() == ' ')
    {
        cell1->set_type('T');
        cell2->set_type('T');
        cell3->set_type('T');
        cell4->set_type('T');
        
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

bool TBlock::clockwise() {
    // uses cell3 as a reference
    int x = cell3->get_x();
    int y = cell3->get_y();
    
    if (orientation == 0 && theGrid->typeAt(x, y-1) == ' ') {
        // sets old cell to ' '
        cell4->set_type(' ');
        
        // disconnects old cell from the block
        cell4->set_block(nullptr);
        
        // connects to new cell
        cell4 = theGrid->get_cell(x, y-1);
        
        // sets new cell to be type 'T'
        cell4->set_type('T');
        
        // connects new cell to the block
        cell4->set_block(this);
        
        // updates orientation
        ++orientation;
    }
    else if (orientation == 1 && x+1 < theGrid->getWidth() &&
             theGrid->typeAt(x-1, y+1) == ' ' && 
             theGrid->typeAt(x+1, y+1) == ' ') {
                 cell2->set_type(' ');
                 cell4->set_type(' ');
                 
                 cell2->set_block(nullptr);
                 cell4->set_block(nullptr);
                 
                 cell2 = theGrid->get_cell(x-1, y+1);
                 cell4 = theGrid->get_cell(x+1, y+1);
                 
                 cell2->set_type('T');
                 cell4->set_type('T');
                 
                 cell2->set_block(this);
                 cell4->set_block(this);
                 
                 ++orientation;
             }
    else if (orientation == 2 && theGrid->typeAt(x-1, y) == ' '
             && theGrid->typeAt(x-1, y-1) == ' ') {
                 cell1->set_type(' ');
                 cell4->set_type(' ');
                 
                 cell1->set_block(nullptr);
                 cell4->set_block(nullptr);
                 
                 cell1 = cell2;
                 
                 cell2 = theGrid->get_cell(x-1, y);
                 cell4 = theGrid->get_cell(x-1, y-1);
                 
                 cell2->set_type('T');
                 cell4->set_type('T');
                 
                 cell2->set_block(this);
                 cell4->set_block(this);
                 
                 ++orientation;
             }
    else if (orientation == 3 && x+1 < theGrid->getWidth() &&
             theGrid->typeAt(x, y+1) == ' ' && 
             theGrid->typeAt(x+1, y) == ' ') {
                 cell1->set_type(' ');
                 cell4->set_type(' ');
                 
                 cell1->set_block(nullptr);
                 cell4->set_block(nullptr);
                 
                 cell1 = theGrid->get_cell(x, y+1);
                 cell4 = theGrid->get_cell(x+1, y);
                 
                 cell1->set_type('T');
                 cell4->set_type('T');
                 
                 cell1->set_block(this);
                 cell4->set_block(this);
                 
                 orientation = 0;
             }
    else return false;
    return true;
}


bool TBlock::cclockwise() {
    // chooses cell3 as a reference
    int x = cell3->get_x();
    int y = cell3->get_y();
    
    if (orientation == 0 && theGrid->typeAt(x-1, y+1) == ' ' &&
        theGrid->typeAt(x-1, y-1) == ' ') {
            // sets old cell to be type ' '
            cell1->set_type(' ');
            cell4->set_type(' ');
            
            // disconnects old cell from the block
            cell1->set_block(nullptr);
            cell4->set_block(nullptr);
            
            // connects block to new cells
            cell1 = theGrid->get_cell(x-1, y+1);
            cell4 = theGrid->get_cell(x-1, y-1);
            
            // sets new cells' type to be 'T'
            cell1->set_type('T');
            cell4->set_type('T');
            
            // connects new cells to the block
            cell1->set_block(this);
            cell4->set_block(this);
            
            // updates orientation
            orientation = 3;
        }
    else if (orientation == 1 && x+1 < theGrid->getWidth() &&
             theGrid->typeAt(x+1, y) == ' ') {
            cell4->set_type(' ');
            
            cell4->set_block(nullptr);
            
            cell4 = theGrid->get_cell(x+1, y);
            
            cell4->set_type('T');
            
            cell4->set_block(this);
            
            --orientation;
        }
    else if (orientation == 2 && theGrid->typeAt(x-1, y) == ' ' &&
             theGrid->typeAt(x, y-1) == ' ') {
            cell2->set_type(' ');
            cell4->set_type(' ');
            
            cell2->set_block(nullptr);
            cell4->set_block(nullptr);
            
            cell2 = theGrid->get_cell(x-1, y);
            cell4 = theGrid->get_cell(x, y-1);
            
            cell2->set_type('T');
            cell4->set_type('T');
            
            cell2->set_block(this);
            cell4->set_block(this);
            
            --orientation;
        }
    else if (orientation == 3 && x+1 < theGrid->getWidth() &&
             theGrid->typeAt(x, y+1) == ' ' && 
             theGrid->typeAt(x+1, y+1) == ' ') {
            cell2->set_type(' ');
            cell4->set_type(' ');
            
            cell2->set_block(nullptr);
            cell4->set_block(nullptr);
            
            cell2 = cell1;
            cell1 = theGrid->get_cell(x, y+1);
            cell4 = theGrid->get_cell(x+1, y+1);
            
            cell1->set_type('T');
            cell4->set_type('T');
            
            cell1->set_block(this);
            cell4->set_block(this);
            
            --orientation;
        }
    else return false;
    return true;
}
     
