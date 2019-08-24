#ifndef _GAME_H
#define _GAME_H

#include <string>
#include <vector>
//#include "player.h"

class Player;

class Game {
    std::vector<Player*> players;
    int numPlayers;
    Player *currPlayer;
    int currWinner;
    int hiscore;
    bool textOnly;
    int seed;
    int init_num;

    std::string printLevels() const;
    std::string printScores() const;
    std::string printGrids() const;
    std::string printNexts() const;
    
  public:
    Game(int num, int seed, bool textOnly);
    ~Game();
    
    void addPlayer(int seed, bool textOnly);                   // creates a new player
    
    bool removePlayer(int id);                  // removes a player
    
    void changeAction(int, std::string, char);  // changes the current action of
                                                //  a player (second param is to
                                                //  note the block if the action
                                                //  is a force)

    void changeCurrPlayer();			// Changes the current player to
						// the next player in line.
                                                
    void tick();                                // runs through one iteration of
                                                //  the game
                                                
    std::string prettyprint() const;            // returns a pretty string
                                                //  representing the game board
                                                
    int getWinner();                        // returns a Player* to the
                                                //  winner of the Game
                                                
    int getNumPlayers();                        // returns the number of Players
                                                
    Player *getCurrPlayer();                    // returns a Player* to the
                                                //  player who's turn it is
                                                
    void setFile(int id, std::string file);     // modifies the sequence file
                                                //  for a given Player

    void somePlayerLost(Player *);              // indicates that some player
                                                // needs to be taken out of the
                                                // game since they have lost

    void restart();                             // Deletes all the players and
                                                // creates new ones.

    bool playerIsIncluded(Player *);            // Checks if the supplied player
                                                // is still in the game.

    void updateHighScore();
};

std::ostream &operator<<(std::ostream& out, const Game &game);

#endif
