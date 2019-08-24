#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "game.h"
#include "block.h"
#include <fstream>

struct InterpreterImpl;
class Block;
class Game;

class Interpreter {
  InterpreterImpl *impl;                          // Contains a list of the commands
  Game *currGame;
  std::ifstream file;
  long int seed;
  std::string seq1, seq2;
  int startLvl;
  bool textOnly;
  int numPlayers;
  int maxLevel;
  //Player *currPlayer;

  public:
    Interpreter(long int seed, std::string seq1, std::string seq2, int startLvl, bool textOnly, int, int);
    ~Interpreter();
    bool executeCommand(std::string s);             // Handles the logic behind recognizing
                                                    // commands and deciding
                                                    // what needs to be
                                                    // executed. True if it ends turn.
    void eval();                                    // The main "REPL" loop that handles
                                                    // commands properly,
                                                    // renaming, adding
                                                    // multipliers, etc.
};

#endif
