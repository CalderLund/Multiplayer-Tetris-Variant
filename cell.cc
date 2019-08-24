#include "cell.h"
#include "block.h"

using namespace std;


Cell::Cell(int x, int y, Xwindow *xwin) : x{x}, y{y}, type{' '}, block{nullptr}, cell_window{xwin} {}

Cell::~Cell() {}

char Cell::get_type() {
    return type;
}

void Cell::set_type(char c) {
    type = c;
}

int Cell::get_x() {
    return x;
}

void Cell::set_x(int i) {
    x = i;
}

int Cell::get_y() {
    return y;
}

void Cell::set_y(int i) {
    y = i;
}

Block *Cell::get_block() {
    return block;
}

void Cell::set_block(Block *bp) {
    block = bp;
}

 void Cell::draw() {
   if (cell_window) {
    if (type == 'I') {
        cell_window->fillRectangle(10 + x * 30, 90 + y * 30, 30, 30, Xwindow::Red);
/*        cell_window->drawLine(10 + x * 30, 90 + y * 30, 40 + x * 30, 90 + y * 30);
        cell_window->drawLine(10 + x * 30, 90 + y * 30, 10 + x * 30, 120 + y * 30);
        cell_window->drawLine(40 + x * 30, 120 + y * 30, 10 + x * 30, 120 + y * 30);
        cell_window->drawLine(40 + x * 30, 120 + y * 30, 40 + x * 30, 90 + y * 30); */
    } 
    else if (type == 'L') {
        cell_window->fillRectangle(10 + x * 30, 90 + y * 30, 30, 30, Xwindow::Green);
	/*   cell_window->drawLine(10 + x * 30, 90 + y * 30, 40 + x * 30, 90 + y * 30);
        cell_window->drawLine(10 + x * 30, 90 + y * 30, 10 + x * 30, 120 + y * 30);
        cell_window->drawLine(40 + x * 30, 120 + y * 30, 10 + x * 30, 120 + y * 30);
        cell_window->drawLine(40 + x * 30, 120 + y * 30, 40 + x * 30, 90 + y * 30); */
    }
    else if (type == 'Z') {
        cell_window->fillRectangle(10 + x * 30, 90 + y * 30, 30, 30, Xwindow::Blue);
	/*    cell_window->drawLine(10 + x * 30, 90 + y * 30, 40 + x * 30, 90 + y * 30);
        cell_window->drawLine(10 + x * 30, 90 + y * 30, 10 + x * 30, 120 + y * 30);
        cell_window->drawLine(40 + x * 30, 120 + y * 30, 10 + x * 30, 120 + y * 30);
        cell_window->drawLine(40 + x * 30, 120 + y * 30, 40 + x * 30, 90 + y * 30); */
    }
    else if (type == 'S') {
        cell_window->fillRectangle(10 + x * 30, 90 + y * 30, 30, 30, Xwindow::Yellow);
	/*   cell_window->drawLine(10 + x * 30, 90 + y * 30, 40 + x * 30, 90 + y * 30);
        cell_window->drawLine(10 + x * 30, 90 + y * 30, 10 + x * 30, 120 + y * 30);
        cell_window->drawLine(40 + x * 30, 120 + y * 30, 10 + x * 30, 120 + y * 30);
        cell_window->drawLine(40 + x * 30, 120 + y * 30, 40 + x * 30, 90 + y * 30); */
    }
    else if (type == 'O') {
        cell_window->fillRectangle(10 + x * 30, 90 + y * 30, 30, 30, Xwindow::Magenta);
	/*  cell_window->drawLine(10 + x * 30, 90 + y * 30, 40 + x * 30, 90 + y * 30);
        cell_window->drawLine(10 + x * 30, 90 + y * 30, 10 + x * 30, 120 + y * 30);
        cell_window->drawLine(40 + x * 30, 120 + y * 30, 10 + x * 30, 120 + y * 30);
        cell_window->drawLine(40 + x * 30, 120 + y * 30, 40 + x * 30, 90 + y * 30); */
    }
    else if (type == 'T') {
        cell_window->fillRectangle(10 + x * 30, 90 + y * 30, 30, 30, Xwindow::Cyan);
	/*      cell_window->drawLine(10 + x * 30, 90 + y * 30, 40 + x * 30, 90 + y * 30);
        cell_window->drawLine(10 + x * 30, 90 + y * 30, 10 + x * 30, 120 + y * 30);
        cell_window->drawLine(40 + x * 30, 120 + y * 30, 10 + x * 30, 120 + y * 30);
        cell_window->drawLine(40 + x * 30, 120 + y * 30, 40 + x * 30, 90 + y * 30); */
    }
    else if (type == 'J') {
        cell_window->fillRectangle(10 + x * 30, 90 + y * 30, 30, 30, Xwindow::Orange);
	/*    cell_window->drawLine(10 + x * 30, 90 + y * 30, 40 + x * 30, 90 + y * 30);
        cell_window->drawLine(10 + x * 30, 90 + y * 30, 10 + x * 30, 120 + y * 30);
        cell_window->drawLine(40 + x * 30, 120 + y * 30, 10 + x * 30, 120 + y * 30);
        cell_window->drawLine(40 + x * 30, 120 + y * 30, 40 + x * 30, 90 + y * 30); */
    }
    else if (type == '*') {
        cell_window->fillRectangle(10 + x * 30, 90 + y * 30, 30, 30, Xwindow::Brown);
	/*     cell_window->drawLine(10 + x * 30, 90 + y * 30, 40 + x * 30, 90 + y * 30);
        cell_window->drawLine(10 + x * 30, 90 + y * 30, 10 + x * 30, 120 + y * 30);
        cell_window->drawLine(40 + x * 30, 120 + y * 30, 10 + x * 30, 120 + y * 30);
        cell_window->drawLine(40 + x * 30, 120 + y * 30, 40 + x * 30, 90 + y * 30); */
    }
   }
}

void Cell::undraw() {
  if (cell_window) {
    cell_window->fillRectangle(10 + x * 30, 90 + y * 30, 30, 30, Xwindow::White);
 /*   cell_window->drawLine(10 + x * 30, 90 + y * 30, 40 + x * 30, 90 + y * 30);
    cell_window->drawLine(10 + x * 30, 90 + y * 30, 10 + x * 30, 120 + y * 30); 
    cell_window->drawLine(40 + x * 30, 120 + y * 30, 10 + x * 30, 120 + y * 30);
    cell_window->drawLine(40 + x * 30, 120 + y * 30, 40 + x * 30, 90 + y * 30); */
  }
}
