#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <string>
#include "grid.h"

class Block {
    protected:
      int orientation;                  // Represents 4 different kinds of 
                                        // orientation of the block (0, 1, 2, 3)
                                        
      Grid *theGrid;                    // Gives the access to the grid
      char type;                        // Indicates the block's type;
      int numcell;                      // Indicates the number of cells in the
                                        // block
                                        
      Cell *cell1, *cell2, *cell3, *cell4; // Pointers to cell
      int spawnlevel;                   // The level when block has been 
                                        // generated
      
      bool created;                     // Determines if the block has been created successfully
      bool blinded;                     // Determines if the special effect has been triggered
          
    public:
      Block(Grid *g, char c, int lvl);
      virtual ~Block();
      virtual void createBlock() = 0;   // Creates a block in the initial 
                                        // position, returns null if a block
                                        // can not be created
                                         
      virtual bool clockwise() = 0;     // Clockwise rotates the block 
      virtual bool cclockwise() = 0;    // Counterclockwise rotates the block
      bool right();                     // Moves the block to right by 1 column
      bool left();                      // Moves the block to left by 1 column
      bool down();                      // Moves the block downwards by 1 row, returns if successful
      void drop();                      // Drops the block to the lowest 
                                        // possible position
      void set_numcell(int i);          // Sets numcell to i
      int get_numcell();                // Returns the number of cells in the 
                                        // block   
                                         
      void set_cell(int i, Cell *cell); // Sets celli to cell
      int get_spawnlevel();             // Returns the level when block has 
                                        // been created
      void draw_block();                // Display the block on the window
      void undraw_block();              // Remove the block from the window
  
      bool is_created();                // Determines if the block can be
                                        // successfully placed on grid

      void removeFromGrid();            // Removes cells from the block

      void set_blind(bool b);           // Sets blinded to b                             
};

#endif
