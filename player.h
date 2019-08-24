#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>
#include <iostream>
#include <fstream>

class Grid;
class Game;
class Action;
class Block;
class Level;

class Player {
  int score;
  Grid *theGrid;
  int playerId;
  Game *theGame;
  Action *current_action;
  Block *current_block;
  char next_block;
  std::string next_action;
  Level *level;
  int currentlevel;
  std::string sequencefile;
  std::ifstream f;
  int seed;

  public:
    Player(int id, Game *game, 
           std::string file, int seed, bool textOnly);             // Creates a new Player with
                                                    // with their appropriate
                                                    // sequence file name
    ~Player();
    void setGrid(Grid *g);                          // Assigns a Grid to the current
                                                    // player
    Grid *getGrid();                                // Retrieves the Grid assigned
                                                    // to a player.
    void levelup();                                 // Triggers a level up for the
                                                    // current player.
    void leveldown();                               // Triggers a level down for the
                                                    // current player.
    void generatenext();                            // Generates the next Block for
                                                    // the current player.
    void setAction(std::string, char);              // Sets the current action for a
                                                    // player. If it's force, the 
                                                    // second param denotes the block
                                                    // to force.
    void effectOther(int, std::string, char);       // Informs the Game of applying an
                                                    // action onto another player (such
                                                    // as force). In the case of force,
                                                    // also provides a second param to
                                                    // note which block to force.
    void endTurn();                                 // Marks the culmination of the
                                                    // current turn.
    int getID();                                    // Gets the current player's id
    int getLevel();                                 // Gets the current player's level
    int getScore();                                 // Gets the current player's score
    char getNextBlockType();                        // Gets the block type of the next
                                                    // block in line.
    void setNextBlockType(char);                    // Sets the next block type.
    void setSequence(std::string);                  // Sets the sequence file for the
                                                    // current player's blocks.
    Block *getCurrBlock();                          // Gets the current block
    std::string printRow(int);                      // Prints the screen for each player.
    
    int right();
    int left();
    int down();
    void drop();

    int clockwise();
    int cclockwise();

    void force(char);
};

#endif
