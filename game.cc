#include "game.h"
#include "player.h"
#include "grid.h"
using namespace std;

// Game class implementation

Game::Game(int num, int seed, bool textOnly): numPlayers {0}, hiscore{0},
textOnly{textOnly}, seed{seed}, init_num{num} { // numPlayers is incremented by addPlayer()
    for (int i=0; i<num; i++) addPlayer(seed, textOnly);
}

Game::~Game() {
    currPlayer = nullptr;
    while (numPlayers) {
        delete players.back();
        players.erase(players.end()-1);
        numPlayers--;
    }
}

Player *Game::getCurrPlayer() {
  return currPlayer;
}

void Game::changeCurrPlayer() {
  bool found = false;

  for (int i = 0; i < numPlayers; i++) {
	if (players[i] == currPlayer && i + 1 < numPlayers) {
	    currPlayer = players[i+1];
      found = true;
	    break;
	}
	else if (players[i] == currPlayer && i + 1 == numPlayers) {
	    currPlayer = players[0];
      found = true;
	    break;
	}
  }

  if (!found) {
    // means curr player has been deleted, so manually assign a curr player
    // based on next id in line
    //
    Player *p = currPlayer;

    for (int i = 0; i < numPlayers; i++) {
      if (players[i]->getID() > currPlayer->getID()) {
        currPlayer = players[i];
        break;
      }
    }

    if (currPlayer == p) {
      // means no larger player was found
      currPlayer = players[0];
    }
  }
}

int Game::getNumPlayers() {
  return numPlayers;
}

void Game::addPlayer(int seed, bool textOnly) {
    Player *p = new Player(++numPlayers, this, "", seed, textOnly); // Increments numPlayers,
                                                          // Player contains a pointer
                                                          // to this Game
    p->getGrid()->set_highest_score(hiscore);
    players.push_back(p);
    if (players.size() == 1) {
      // if this is the first player to enter, make them the current_player
      currPlayer = p;
    }
}

bool Game::removePlayer(int id) {
    // cycle through until the id is found, then remove
    for (int i=0; i < numPlayers; i++) {
        if (id == players[i]->getID()) {
	    delete players[i];
            players.erase(players.begin() + i);
            numPlayers--;
            return true;
        }
    }
    return false;
}

void Game::changeAction(int id, string action, char block) {
    // Search for id
    for (int i=0; i<numPlayers; i++) {
        // if the id exists, change that players action
        if (id == players[i]->getID()) {
            players[i]->setAction(action, block);
            break;
        }
    }
}

void Game::tick() {
    for (int i=0; i<numPlayers; i++) {
        players[i]->endTurn();
    }
}

int Game::getWinner() {
    int highestScore = 0;
    Player *winner = nullptr;
    for (int i = 0; i < numPlayers; i++) {
        int score = players[i]->getScore();
        
        // if new highscore, modify winner
        if (numPlayers == 1 || score > highestScore) {
            winner = players[i];
            highestScore = score;
        }
    }
    return ((winner && (winner->getScore() >= hiscore || hiscore == 0)) ? winner->getID() : currWinner);
}

void Game::somePlayerLost(Player *p) {
  for (int i = 0; i < numPlayers; i++) {
    if (players[i] == p) {
      cout << "Player " << p->getID() << " is out!" << endl;
      if (p->getScore() >= hiscore || hiscore == 0) {
        hiscore = p->getScore();
        currWinner = p->getID();
      }

      players.erase(players.begin() + i);
      numPlayers--;
    }
  }
}

bool Game::playerIsIncluded(Player *p) {
  for (int i = 0; i < numPlayers; i++) {
    if (players[i] == p) return true;
  }
  return false;
}

void Game::setFile(int id, std::string file) {
    for (int i=0; i<numPlayers; i++) {
        if (id == players[i]->getID()) {
            players[i]->setSequence(file);
            break;
        }
    }
}

string Game::printLevels() const {
    // prints one line of a string containing all the levels of the players
    // this is a helper function to prettyprint()
    string output = "";
    int width;
    for (int i=0; i<numPlayers; i++) {
        width = players[i]->getGrid()->getWidth();
        
        output += "Level:";
        string level = to_string(players[i]->getLevel());
        int numSpaces = width - 6 - level.length();
        
        for (int j=0; j<numSpaces; j++)
            output += " ";
        output += level;
        
        if (i+1 != numPlayers)
            output += "      ";   // seperates the boards by 6 spaces  
        
        else output += "\n";
    }
    return output;
}

string Game::printScores() const {
    // prints one line containing each player's score seperated by 6 spaces
    // this is a helper function to prettyprint()
    string output = "";
    int width;
    for (int i=0; i<numPlayers; i++) {
        width = players[i]->getGrid()->getWidth();
        
        output += "Score:";
        string score = to_string(players[i]->getScore());
        int numSpaces = width - 6 - score.length();
        
        for (int j=0; j<numSpaces; j++)
            output += " ";
        output += score;

        if (i+1 != numPlayers) {
            output += "      ";   // seperates the boards by 6 spaces  
        }
        else output += "\n";
    }
    return output;
}

string Game::printGrids() const {
    string output = "";
    int height = players[0]->getGrid()->getHeight();
    for (int i=-1; i<=height; i++) {  // ranges from -1 to height for dashes
        for (int j=-1; j<numPlayers-1; j++) {
	    string row = players[j+1]->printRow(i);
            output += row; // takes care of printing dashes
	    if (j+1 != numPlayers-1) {
                output += "      ";   // seperates the boards by 6 spaces   
            }
            else {
	      output += "\n";
	    }
        }
    }
    return output;
}

static string printI(int row) {
    string output = "";
    if (row == 0) 
        output += "Next:";
    else if (row == 2)
        output += "IIII";
    return output;
}

static string printJ(int row) {
    string output = "";
    if (row == 0) 
        output += "Next:";
    else if (row == 1)
        output += "J";
    else if (row == 2)
        output += "JJJ";
    return output;
}

static string printL(int row) {
    string output = "";
    if (row == 0) 
        output += "Next:";
    else if (row == 1)
        output += "  L";
    else if (row == 2)
        output += "LLL";
    return output;
}

static string printO(int row) {
    string output = "";
    if (row == 0) 
        output += "Next:";
    else if (row == 1)
        output += "OO";
    else if (row == 2)
        output += "OO";
    return output;
}

static string printS(int row) {
    string output = "";
    if (row == 0) 
        output += "Next:";
    else if (row == 1)
        output += " SS";
    else if (row == 2)
        output += "SS";
    return output;
}

static string printZ(int row) {
    string output = "";
    if (row == 0) 
        output += "Next:";
    else if (row == 1)
        output += "ZZ";
    else if (row == 2)
        output += " ZZ";
    return output;
}

static string printT(int row) {
    string output = "";
    if (row == 0) 
        output += "Next:";
    else if (row == 1)
        output += "TTT";
    else if (row == 2)
        output += " T";
    return output;
}

string Game::printNexts() const {
    string output = "";
    int width;
    for (int row = 0; row < 3; row++) {  // a block will only be two spaces tall, need 3rd for Next:
        for (int i=0; i<numPlayers; i++) {
            string block;
            width = players[i]->getGrid()->getWidth();
            char blockType = players[i]->getNextBlockType();
	    
            if (blockType == 'I')
                block = printI(row);
            else if (blockType == 'J')
                block = printJ(row);
            else if (blockType == 'L')
                block = printL(row);
            else if (blockType == 'O')
                block = printO(row);
            else if (blockType == 'S')
                block = printS(row);
            else if (blockType == 'Z')
                block = printZ(row);
            else if (blockType == 'T')
                block = printT(row);
            
            output += block;
            int numSpaces = width - block.length();
            
            for (int j=0; j<numSpaces; j++)
                output += " ";
            
            if (i+1 != numPlayers) {
                output += "      ";   // seperates the boards by 6 spaces  
            }
            else output += "\n";
        }
    }
    return output;
}

string Game::prettyprint() const {
    string output = "";
    output += printLevels();
    output += printScores();
    output += printGrids();
    output += printNexts();
    return output;
}

void Game::restart() {
  for (int i = numPlayers - 1; i >= 0; i--) {
    int score = players[i]->getScore();
    if (score > hiscore)
        hiscore = players[i]->getScore();
    delete players[i];
    players.pop_back();
  }

  numPlayers = 0;

  for (int i = 0; i < init_num; i++) {
    addPlayer(seed, textOnly);
  }
}

void Game::updateHighScore() {
  int score = currPlayer->getScore();
  if (score > hiscore) {
    hiscore = score;
    for (int j=0; j<numPlayers; j++)
      players[j]->getGrid()->set_highest_score(hiscore);
  }
}

ostream &operator<<(ostream& out, const Game &game) {
    out << game.prettyprint();
    return out;
}

