#ifndef _GRID_H_
#define _GRID_H_

#include <string>
#include <vector>
#include <iostream>
#include "cell.h"
#include "window.h"

class Grid {
    std::vector<std::vector<Cell>> theGrid;  // The actual grid
    int width;                               // The width of the grid
    int height;                              // The height of the grid
    int score;                               // The player's score
    int noclearcount;                        // Number of turns player does not
                                             // clear a row since last clear
    int level;                               // The level player has choosen
    int highest_score;                       // Records the highest score
    Xwindow *grid_window;                    // Graphic display window

    std::vector<Block *> blocks;            // List of blocks currently active
                                             // on the Grid

    public:
      Grid(bool textOnly);
      ~Grid();
      void init(int l, int w = 11, int h = 18);   // Creates a (w * h) grid filled with 
                                                  // type ' ' cells
                                     
      int checkfilled();                          // Checks and clears the filled rows, moves
                                                  // the remaining cells to the bottom and
                                                  // returns the number of filled rows
      
      std::string printRow(int i);                // Returns a string that contains all the
                                                  // cells in the i-th row
                                     
      int getHeight();                            // Returns the height of the grid
      int getWidth();                             // Returns the width of the grid  
      void refresh();                             // Adjusts every cell's coordinate
      
      char typeAt(int x, int y);                  // Returns the type of the cell at (x, y)
      void setAt(int x, int y, char type);        // Changes the type of the cell at (x, y)
      void updatescore(int s);                    // Updates score to s
      int getscore();                             // Returns the current score
      int getnoclearcount();                      // Returns noclearcount
      void setlevel(int l);                       // Sets level to l
      int getlevel();                             // Returns the current level
      Cell *get_cell(int x, int y);               // Returns a pointer to a cell at (x, y)
      int get_highest_score();                    // Returns the highest score
      void set_highest_score(int s);
      void display_score(int s);                  // Displays the current score on window
      void display_level(int lvl);                // Displays the current level on window
      void display_highest_score(int hs);         // Displays the current highest_score on window

      void display_next(char c);                  // Displays the next block at the bottom
      void erase_next(char c);                    // Erases the next block from the window
      void blind();                               // Covers column 3-9, row 3-12 with black Cells 
      void unblind();                             // Recovers the Grid

      void addBlock(Block &);                     // Adds the given block to the blocks array
};

#endif
