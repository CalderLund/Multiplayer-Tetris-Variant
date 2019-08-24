#ifndef _CELL_H_
#define _CELL_H_

#include <iostream>
#include "window.h"

class Block;

class Cell {
    int x, y;      // Represents x and y coordinate respectively.
    char type;     // Indicates the type of block it belongs to, if the cell
                   // does not belong to any blocks, the type will be ' '
                 
    Block *block;  // A pointer pointing to the block it belongs to or a nullptr
                   // if its type is '0'
    Xwindow *cell_window;  // The window used to display cells  
    
    public:
      Cell(int x, int y, Xwindow *xwin);
      ~Cell();
      char get_type();        // Returns the type of the cell
      void set_type(char c);  // Sets the type of the cell to c
      int get_x();           // Returns the x-coordinate of the cell
      void set_x(int i);      // Sets the cell's x value to i
      int get_y();           // Returns the y-coordinate of the cell
      void set_y(int i);      // Sets the cell's y value to i
      Block *get_block();     // Returns a pointer to the Block it belongs to
      void set_block(Block *bp);  // Sets block to be bp
      void draw();            // Display the cell on window
      void undraw();          // Erase the cell from window
};

#endif
