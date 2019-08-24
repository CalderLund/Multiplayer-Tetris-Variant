#include "player.h"
#include "grid.h"
#include "game.h"
#include "action.h"
#include "block.h"
#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "level5.h"
#include "blind.h"
#include "specheavy.h"
#include "specaction.h"
#include "normal.h"
#include "tblock.h"
#include "sblock.h"
#include "iblock.h"
#include "oblock.h"
#include "jblock.h"
#include "lblock.h"
#include "zblock.h"

using namespace std;

Player::Player(int id, Game *game, string file, int seed, bool textOnly): 
  theGrid {new Grid(textOnly)}, playerId {id}, theGame {game}, 
  current_action {new Normal}, current_block {nullptr}, next_block{'\0'},
  level {new Level0{file}}, currentlevel {0}, sequencefile {file}, seed {seed}
{theGrid->init(currentlevel);}  // defaults to level 0, height 18, width 11

Player::~Player() {
  delete level;
  delete current_action;
  delete theGrid; // current_block should be destroyed through the Grid dtor
}

string Player::printRow(int i) {
  string output = "";
  int height = theGrid->getHeight();
  string row = theGrid->printRow(i);
  if (current_action->printchar() == '?' &&
      (i > 3 && i <= height - 6)) 
  { 
    current_block->set_blind(true);
    theGrid->blind();
    int len = row.length();
    for (int j = 0; j < len; j++) {
      if (j > 1 && j < 9) 
        output += "?";
      else
        output += row[j];
    }
  }
  else output = row;
  return output;
}

void Player::setGrid(Grid *g) {
  theGrid = g;
}

Grid *Player::getGrid() {
  return theGrid;
}

void Player::levelup() {
  currentlevel++;
  if (currentlevel > 5) currentlevel = 5;
  else {
    delete level;
    if (currentlevel == 1) level = new Level1();
    else if (currentlevel == 2) level = new Level2();
    else if (currentlevel == 3) level = new Level3();
    else if (currentlevel == 4) level = new Level4();
    else if (currentlevel == 5) level = new Level5();
  }
  theGrid->display_level(currentlevel);
  theGrid->setlevel(currentlevel);
}

void Player::leveldown() {
  currentlevel--;
  if (currentlevel < 0) currentlevel = 0;
  else {
    delete level;
    if (currentlevel == 0) level = new Level0(sequencefile);
    else if (currentlevel == 1) level = new Level1();
    else if (currentlevel == 2) level = new Level2();
    else if (currentlevel == 3) level = new Level3();
    else if (currentlevel == 4) level = new Level4();
  }
  theGrid->display_level(currentlevel);
  theGrid->setlevel(currentlevel);
}

void Player::generatenext() {
  next_block = level->generatenext(seed);
}

void Player::setAction(string s, char b) {
  if (s == "force") {
    force(b);
    //current_action = new Force(current_action, b);
  }
  else if (s == "blind") {
    current_action = new Blind(current_action);
  }
  else if (s == "heavy") {
    current_action = new SpecHeavy(current_action);
  }
}

void Player::effectOther(int playerId, string action, char b) {
  theGame->changeAction(playerId, action, b);
}

Block *Player::getCurrBlock() {
  return current_block;
}

void generateBlock(Grid *theGrid, int currentlevel, Block **current_block, char *next_block, char block, Game* theGame, Player* p) {
  if (block == 'T')
    *current_block = new TBlock(theGrid, currentlevel);
  else if (block == 'O')
    *current_block = new OBlock(theGrid, currentlevel);
  else if (block == 'I')
    *current_block = new IBlock(theGrid, currentlevel);
  else if (block == 'S')
    *current_block = new SBlock(theGrid, currentlevel);
  else if (block == 'J')
    *current_block = new JBlock(theGrid, currentlevel);
  else if (block == 'L')
    *current_block = new LBlock(theGrid, currentlevel);
  else if (block == 'Z')
    *current_block = new ZBlock(theGrid, currentlevel);
  
  (*current_block)->draw_block();
  theGrid->addBlock(**current_block);

  if (!((*current_block)->is_created())) {
    // block couldn't be created so game over!
    theGame->somePlayerLost(p);
  }
}

void Player::setNextBlockType(char b) {
  next_block = b;
}

void Player::endTurn() {
  theGrid->erase_next(next_block);
  // place the current block on the board
  // get the next block based on whichever level we are
  char block;
  if (sequencefile != "" && (currentlevel == 0 || currentlevel == 3 || currentlevel == 4)) {
    if (!f.is_open()) {
      f.open(sequencefile);
    }

    if (next_block == '\0')
      f >> next_block;

    block = next_block;
    f >> next_block;
    
    if (f.eof()) {
      f.clear();
      f.seekg(0, ios::beg);
      f >> next_block;
    }

    generateBlock(theGrid, currentlevel, &current_block, &next_block, block, theGame, this);
  }
  else {
    // check if blocks have to be randomly generated...if not level generates
    // the blocks.
    if (next_block == '\0') block = level->generatenext(seed);
    else {
      block = next_block;
    }

    generateBlock(theGrid, currentlevel, &current_block, &next_block, block, theGame, this);
    next_block = level->generatenext(seed);
  }
  if (current_action->printchar() == '?') {
    theGrid->unblind();
  }
  delete current_action;
  current_action = level->generateaction();
  theGrid->display_next(next_block);
}

int Player::getID() {
  return playerId; 
}

int Player::getLevel() {
  return currentlevel;
}

int Player::getScore() {
  return theGrid->getscore();
}

char Player::getNextBlockType() {
  return next_block;
}

void Player::setSequence(std::string s) {
  sequencefile = s;
}

int Player::right() {
    return current_action->right(current_block);
}

int Player::left() {
    return current_action->left(current_block);
}

int Player::down() {
    return current_action->down(current_block);
}

void Player::drop() {
    current_action->drop(current_block);
    level->nocleareffect(theGrid);
}

int Player::clockwise() {
  return current_action->clockwise(current_block);
}

int Player::cclockwise() {
  return current_action->cclockwise(current_block);
}

void Player::force(char new_cell) {
  current_block->undraw_block();
  if (new_cell == 'I') {
    current_block->removeFromGrid();
    delete current_block;
    current_block = new IBlock(theGrid, currentlevel);
  }
  else if (new_cell == 'J') {
    current_block->removeFromGrid();
    delete current_block;
    current_block = new JBlock(theGrid, currentlevel);
  }
  else if (new_cell == 'L') {
    current_block->removeFromGrid();
    delete current_block;
    current_block = new LBlock(theGrid, currentlevel);
  }
  else if (new_cell == 'O') {
    current_block->removeFromGrid();
    delete current_block;
    current_block = new OBlock(theGrid, currentlevel);
  }
  else if (new_cell == 'S') {
    current_block->removeFromGrid();
    delete current_block;
    current_block = new SBlock(theGrid, currentlevel);
  }
  else if (new_cell == 'T') {
    current_block->removeFromGrid();
    delete current_block;
    current_block = new TBlock(theGrid, currentlevel);
  }
  else if (new_cell == 'Z') {
    current_block->removeFromGrid();
    delete current_block;
    current_block = new ZBlock(theGrid, currentlevel);
  }
  else return;
  
  current_block->draw_block();

  if (!(current_block->is_created())) {
    // block couldn't be created so game over!
    theGame->somePlayerLost(this);
  }
}
