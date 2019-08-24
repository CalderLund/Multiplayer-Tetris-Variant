#include "jblock.h"
using namespace std;

JBlock::JBlock(Grid *g, int lvl) : Block{g, 'J', lvl} {
    createBlock();
}

JBlock::~JBlock() {}

void JBlock::createBlock() {
    cell1 = theGrid->get_cell(0, 3);
    cell2 = theGrid->get_cell(0, 2);
    cell3 = theGrid->get_cell(1, 3);
    cell4 = theGrid->get_cell(2, 3);
    
    if (cell1->get_type() == ' '
        && cell2->get_type() == ' '
        && cell3->get_type() == ' '
        && cell4->get_type() == ' ')
    {
        cell1->set_type(type);
        cell2->set_type(type);
        cell3->set_type(type);
        cell4->set_type(type);
        
        cell1->set_block(this);
        cell2->set_block(this);
        cell3->set_block(this);
        cell4->set_block(this);
        
        numcell = 4;
        created = true;
    }
}

bool JBlock::clockwise() {
    int x = cell1->get_x();
    int y = cell1->get_y();
    
    if (orientation == 0 &&
        theGrid->typeAt(x, y-2) == ' ' &&
        theGrid->typeAt(x+1, y-2) == ' ') 
    {
        // sets old to  ' '
        cell3->set_type(' ');
        cell4->set_type(' ');
        
        // makes old cells have no block ptrs
        cell3->set_block(nullptr);
        cell4->set_block(nullptr);
        
        // points to new cells on grid
        cell3 = theGrid->get_cell(x, y-2);
        cell4 = theGrid->get_cell(x+1, y-2);
        
        // sets new cell type
        cell3->set_type(type);
        cell4->set_type(type);
        
        // sets cells blocks to this block
        cell3->set_block(this);
        cell4->set_block(this);
        
        orientation++;
    }
    else if (orientation == 1 && x+2 < theGrid->getWidth() &&
             theGrid->typeAt(x+1, y-1) == ' ' &&
             theGrid->typeAt(x+2, y-1) == ' ' &&
             theGrid->typeAt(x+2, y) == ' ')
    {
        cell1->set_type(' ');
        cell3->set_type(' ');
        cell4->set_type(' ');
        
        cell1->set_block(nullptr);
        cell3->set_block(nullptr);
        cell4->set_block(nullptr);
        
        cell1 = cell2;
        cell2 = theGrid->get_cell(x+1, y-1);
        cell3 = theGrid->get_cell(x+2, y-1);
        cell4 = theGrid->get_cell(x+2, y);
        
        cell2->set_type(type);
        cell3->set_type(type);
        cell4->set_type(type);
        
        cell2->set_block(this);
        cell3->set_block(this);
        cell4->set_block(this);
        
        orientation++;
    }
    else if (orientation == 2 &&
             theGrid->typeAt(x, y+1) == ' ' &&
             theGrid->typeAt(x+1, y+1) == ' ' &&
             theGrid->typeAt(x+1, y-1) == ' ')
    {
        cell1->set_type(' ');
        cell3->set_type(' ');
        cell4->set_type(' ');
        
        cell1->set_block(nullptr);
        cell3->set_block(nullptr);
        cell4->set_block(nullptr);
        
        cell1 = theGrid->get_cell(x, y+1);
        cell3 = theGrid->get_cell(x+1, y+1);
        cell4 = theGrid->get_cell(x+1, y-1);
        
        cell1->set_type(type);
        cell3->set_type(type);
        cell4->set_type(type);
        
        cell1->set_block(this);
        cell3->set_block(this);
        cell4->set_block(this);
        
        orientation++;
    }
    else if (orientation == 3 && x+2 < theGrid->getWidth() &&
             theGrid->typeAt(x, y-1) == ' ' &&
             theGrid->typeAt(x+2, y) == ' ')
    {
        cell2->set_type(' ');
        cell4->set_type(' ');
         
        cell2->set_block(nullptr);
        cell4->set_block(nullptr);
        
        cell2 = theGrid->get_cell(x, y-1);
        cell4 = theGrid->get_cell(x+2, y);
        
        cell2->set_type(type);
        cell4->set_type(type);
        
        cell2->set_block(this);
        cell4->set_block(this);
        
        orientation = 0;
    }
    else return false;
    return true;
}

bool JBlock::cclockwise() {
    int x = cell1->get_x();
    int y = cell1->get_y();
    
    if (orientation == 1 && x+2 < theGrid->getWidth() &&
        theGrid->typeAt(x+1, y) == ' ' &&
        theGrid->typeAt(x+2, y) == ' ') 
    {
        // sets old to  ' '
        cell3->set_type(' ');
        cell4->set_type(' ');
        
        // makes old cells have no block ptrs
        cell3->set_block(nullptr);
        cell4->set_block(nullptr);
        
        // points to new cells on grid
        cell3 = theGrid->get_cell(x+1, y);
        cell4 = theGrid->get_cell(x+2, y);
        
        // sets new cell type
        cell3->set_type(type);
        cell4->set_type(type);
        
        // sets cells blocks to this block
        cell3->set_block(this);
        cell4->set_block(this);
        
        orientation--;
    }
    else if (orientation == 2 &&
             theGrid->typeAt(x, y+1) == ' ' &&
             theGrid->typeAt(x, y-1) == ' ' &&
             theGrid->typeAt(x+1, y-1) == ' ')
    {
        cell2->set_type(' ');
        cell3->set_type(' ');
        cell4->set_type(' ');
        
        cell2->set_block(nullptr);
        cell3->set_block(nullptr);
        cell4->set_block(nullptr);
        
        cell2 = cell1;
        cell1 = theGrid->get_cell(x, y+1);
        cell3 = theGrid->get_cell(x, y-1);
        cell4 = theGrid->get_cell(x+1, y-1);
        
        cell1->set_type(type);
        cell3->set_type(type);
        cell4->set_type(type);
        
        cell1->set_block(this);
        cell3->set_block(this);
        cell4->set_block(this);
        
        orientation--;
    }
    else if (orientation == 3 && x+2 < theGrid->getWidth() &&
             theGrid->typeAt(x, y-1) == ' ' &&
             theGrid->typeAt(x+2, y-1) == ' ' &&
             theGrid->typeAt(x+2, y) == ' ')
    {
        cell1->set_type(' ');
        cell3->set_type(' ');
        cell4->set_type(' ');
        
        cell1->set_block(nullptr);
        cell3->set_block(nullptr);
        cell4->set_block(nullptr);
        
        cell1 = theGrid->get_cell(x, y-1);
        cell3 = theGrid->get_cell(x+2, y-1);
        cell4 = theGrid->get_cell(x+2, y);
        
        cell1->set_type(type);
        cell3->set_type(type);
        cell4->set_type(type);
        
        cell1->set_block(this);
        cell3->set_block(this);
        cell4->set_block(this);
        
        orientation--;
    }
    else if (orientation == 0 &&
             theGrid->typeAt(x+1, y-1) == ' ' &&
             theGrid->typeAt(x+1, y-2) == ' ')
    {
        cell2->set_type(' ');
        cell4->set_type(' ');
         
        cell2->set_block(nullptr);
        cell4->set_block(nullptr);
        
        cell2 = theGrid->get_cell(x+1, y-1);
        cell4 = theGrid->get_cell(x+1, y-2);
        
        cell2->set_type(type);
        cell4->set_type(type);
        
        cell2->set_block(this);
        cell4->set_block(this);
        
        orientation = 3;
    }
    else return false;
    return true;
}
