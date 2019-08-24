#include <string>
#include "block.h"

using namespace std;

Block::Block(Grid *g, char c, int lvl) : orientation{0}, theGrid{g}, type{c}, numcell{0}, 
                                       cell1{nullptr}, cell2{nullptr}, 
                                       cell3{nullptr}, cell4{nullptr}, 
                                       spawnlevel{lvl}, created {false}, blinded{false} {}
                                       
Block::~Block() {}

void Block::removeFromGrid() {
    if (cell1) {
        cell1->set_type(' ');
        cell1->set_block(nullptr);
    }
    if (cell2) { 
        cell2->set_type(' ');
        cell2->set_block(nullptr);
    }
    if (cell3) {
        cell3->set_type(' ');
        cell3->set_block(nullptr);
    }
    if (cell4) {
        cell4->set_type(' ');
        cell4->set_block(nullptr);
    }
}

void Block::set_numcell(int i) {
    numcell = i;
}
                
int Block::get_numcell() {
    return numcell;
}

void Block::set_cell(int i, Cell *cell) {
    if (i == 1) {
        cell1 = cell;
    }
    else if (i == 2) {
        cell2 = cell;
    }
    else if (i == 3) {
        cell3 = cell;
    }
    else if (i == 4) {
        cell4 = cell;
    }
}

bool Block::is_created() { return created; }

bool Block::right() {
    int x1,y1,x2,y2,x3,y3,x4,y4;
    int width = theGrid->getWidth();
    
    x1 = cell1->get_x();
    y1 = cell1->get_y();
    x2 = cell2->get_x();
    y2 = cell2->get_y();
    x3 = cell3->get_x();
    y3 = cell3->get_y();
    x4 = cell4->get_x();
    y4 = cell4->get_y();
    
    // if there is an open cell to the right of each cell in block or
    // the right of a cell is also in same block
    if (((x1+1 == x2 && y1 == y2) || (x1+1 == x3 && y1 == y3) || (x1+1 == x4 && y1 == y4) ||
	 (x1+1 < width && theGrid->typeAt(x1+1, y1) == ' ')) &&
        ((x2+1 == x1 && y1 == y2) || (x2+1 == x3 && y3 == y2) || (x2+1 == x4 && y4 == y2) ||
	 (x2+1 < width && theGrid->typeAt(x2+1, y2) == ' ')) &&
        ((x3+1 == x2 && y3 == y2) || (x3+1 == x1 && y1 == y3) || (x3+1 == x4 && y3 == y4) ||
	 (x3+1 < width && theGrid->typeAt(x3+1, y3) == ' ')) &&
        ((x4+1 == x2 && y4 == y2) || (x4+1 == x3 && y4 == y3) || (x4+1 == x1 && y1 == y4) ||
	 (x4+1 < width && theGrid->typeAt(x4+1, y4) == ' ')))
    {
        // default value all the cells
        cell1->set_type(' ');
        cell2->set_type(' ');
        cell3->set_type(' ');
        cell4->set_type(' ');
        
        cell1->set_block(nullptr);
        cell2->set_block(nullptr);
        cell3->set_block(nullptr);
        cell4->set_block(nullptr);
        
        //point at all cells to the right
        cell1 = theGrid->get_cell(x1+1, y1);
        cell2 = theGrid->get_cell(x2+1, y2);
        cell3 = theGrid->get_cell(x3+1, y3);
        cell4 = theGrid->get_cell(x4+1, y4);
        
        // set type
        cell1->set_type(type);
        cell2->set_type(type);
        cell3->set_type(type);
        cell4->set_type(type);
        
        // set block
        cell1->set_block(this);
        cell2->set_block(this);
        cell3->set_block(this);
        cell4->set_block(this);
        
        return true;
    }
    return false;
}

bool Block::left() {
    int x1,y1,x2,y2,x3,y3,x4,y4;
    
    x1 = cell1->get_x();
    y1 = cell1->get_y();
    x2 = cell2->get_x();
    y2 = cell2->get_y();
    x3 = cell3->get_x();
    y3 = cell3->get_y();
    x4 = cell4->get_x();
    y4 = cell4->get_y();
    
    if (((x1-1 == x2 && y1 == y2) || (x1-1 == x3 && y1 == y3) || (x1-1 == x4 && y1 == y4) ||
	 (x1-1 >= 0 && theGrid->typeAt(x1-1, y1) == ' ')) &&
        ((x2-1 == x1 && y1 == y2) || (x2-1 == x3 && y3 == y2) || (x2-1 == x4 && y4 == y2) ||
	 (x2-1 >= 0 && theGrid->typeAt(x2-1, y2) == ' ')) &&
        ((x3-1 == x2 && y3 == y2) || (x3-1 == x1 && y1 == y3) || (x3-1 == x4 && y3 == y4) ||
	 (x3-1 >= 0 && theGrid->typeAt(x3-1, y3) == ' ')) &&
        ((x4-1 == x2 && y4 == y2) || (x4-1 == x3 && y4 == y3) || (x4-1 == x1 && y1 == y4) ||
	 (x4-1 >= 0 && theGrid->typeAt(x4-1, y4) == ' ')))
    {
        // default value all the cells
        cell1->set_type(' ');
        cell2->set_type(' ');
        cell3->set_type(' ');
        cell4->set_type(' ');
        
        cell1->set_block(nullptr);
        cell2->set_block(nullptr);
        cell3->set_block(nullptr);
        cell4->set_block(nullptr);
        
        //point at all cells to the right
        cell1 = theGrid->get_cell(x1-1, y1);
        cell2 = theGrid->get_cell(x2-1, y2);
        cell3 = theGrid->get_cell(x3-1, y3);
        cell4 = theGrid->get_cell(x4-1, y4);
        
        // set type
        cell1->set_type(type);
        cell2->set_type(type);
        cell3->set_type(type);
        cell4->set_type(type);
        
        // set block
        cell1->set_block(this);
        cell2->set_block(this);
        cell3->set_block(this);
        cell4->set_block(this);
        
        return true;
    }
    return false;
}

bool Block::down() {
    int x1,y1,x2,y2,x3,y3,x4,y4;
    int height = theGrid->getHeight();
    
    x1 = cell1->get_x();
    y1 = cell1->get_y();
    x2 = cell2->get_x();
    y2 = cell2->get_y();
    x3 = cell3->get_x();
    y3 = cell3->get_y();
    x4 = cell4->get_x();
    y4 = cell4->get_y();
    
    if (((y1+1 == y2 && x1 == x2) || (y1+1 == y3 && x1 == x3) || (y1+1 == y4 && x1 == x4) ||
	 (y1+1 < height && theGrid->typeAt(x1, y1+1) == ' ')) &&
        ((y2+1 == y1 && x2 == x1) || (y2+1 == y3 && x2 == x3) || (y2+1 == y4 && x2 == x4) ||
	 (y2+1 < height && theGrid->typeAt(x2, y2+1) == ' ')) &&
        ((y3+1 == y2 && x3 == x2) || (y3+1 == y1 && x3 == x1) || (y3+1 == y4 && x3 == x4) ||
	 (y3+1 < height && theGrid->typeAt(x3, y3+1) == ' ')) &&
        ((y4+1 == y2 && x4 == x2) || (y4+1 == y3 && x4 == x3) || (y4+1 == y1 && x4 == x1) ||
	 (y4+1 < height && theGrid->typeAt(x4, y4+1) == ' ')))
    {
        // default value all the cells
        cell1->set_type(' ');
        cell2->set_type(' ');
        cell3->set_type(' ');
        cell4->set_type(' ');
        
        cell1->set_block(nullptr);
        cell2->set_block(nullptr);
        cell3->set_block(nullptr);
        cell4->set_block(nullptr);
        
        //point at all cells to the right
        cell1 = theGrid->get_cell(x1, y1+1);
        cell2 = theGrid->get_cell(x2, y2+1);
        cell3 = theGrid->get_cell(x3, y3+1);
        cell4 = theGrid->get_cell(x4, y4+1);
        
        // set type
        cell1->set_type(type);
        cell2->set_type(type);
        cell3->set_type(type);
        cell4->set_type(type);
        
        // set block
        cell1->set_block(this);
        cell2->set_block(this);
        cell3->set_block(this);
        cell4->set_block(this);
        
        return true;
    }
    return false;
}

void Block::drop() {
    while (down());
}

int Block::get_spawnlevel() {
    return spawnlevel;
}

void Block::draw_block() {
    if (!(blinded)) {
        cell1->draw();
        cell2->draw();
        cell3->draw();
        cell4->draw();
    }
    else {
        if (cell1->get_x() < 2 || cell1->get_x() > 8 ||
            cell1->get_y() < 4 || cell2->get_y() > 12) {
            cell1->draw();
        }
        if (cell2->get_x() < 2 || cell2->get_x() > 8 || 
            cell2->get_y() < 4 || cell2->get_y() > 12) {
            cell2->draw();
        }
        if (cell3->get_x() < 2 || cell3->get_x() > 8 || 
            cell3->get_y() < 4 || cell3->get_y() > 12) {
            cell3->draw();
        }
        if (cell4->get_x() < 2 || cell4->get_x() > 8 || 
            cell4->get_y() < 4 || cell4->get_y() > 12) {
            cell4->draw();
        }
    }
}

void Block::undraw_block() {
    if (!(blinded)) {
        cell1->undraw();
        cell2->undraw();
        cell3->undraw();
        cell4->undraw();
    }
    else {
        if (cell1->get_x() < 2 || cell1->get_x() > 8 ||
            cell1->get_y() < 4 || cell2->get_y() > 12) {
            cell1->undraw();
        }
        if (cell2->get_x() < 2 || cell2->get_x() > 8 ||
            cell2->get_y() < 4 || cell2->get_y() > 12) {
            cell2->undraw();
        }
        if (cell3->get_x() < 2 || cell3->get_x() > 8 ||
            cell3->get_y() < 4 || cell3->get_y() > 12) {
            cell3->undraw();
        }
        if (cell4->get_x() < 2 || cell4->get_x() > 8 ||
            cell4->get_y() < 4 || cell4->get_y() > 12) {
            cell4->undraw();
        }
    }
}

void Block::set_blind(bool b) {
    blinded = b;
}
