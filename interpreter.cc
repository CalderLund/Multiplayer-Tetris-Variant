#include "interpreter.h"
#include "interpreterimpl.h"
#include "player.h"

using namespace std;

const int DROP = 2;

void assignSeqFiles(Game *currGame, string seq1, string seq2);
void levelUpEveryone(Game *currGame, int startLvl);

Interpreter::Interpreter(long int seed, string seq1, string seq2, int startLvl, bool textOnly, int numPlayers, int maxLevel): impl{new InterpreterImpl{}}, 
  currGame{nullptr}, seed{seed}, seq1{seq1}, seq2{seq2}, startLvl{startLvl}, textOnly{textOnly}, numPlayers{numPlayers}, maxLevel{maxLevel <= 0 ? 1 : maxLevel} {

    if (startLvl == 0 && numPlayers <= 2) {
      currGame = new Game{numPlayers, seed, textOnly};
      assignSeqFiles(currGame, seq1, seq2);
    }
    else {
      currGame = new Game{numPlayers, seed, textOnly};

      levelUpEveryone(currGame, startLvl);
    }

    currGame->tick();
    cout << *currGame << endl;
  }

void assignSeqFiles(Game *currGame, string seq1, string seq2) {
  if (seq1 != "") currGame->setFile(1, seq1);
  else currGame->setFile(1, "sequence1.txt");
  if (seq2 != "") currGame->setFile(2, seq2);
  else currGame->setFile(2, "sequence2.txt");
}

void levelUpEveryone(Game *currGame, int startLvl) {
      for (int i = 0; i < currGame->getNumPlayers(); i++) {
        for (int j = 0; j < startLvl; j++) {
          currGame->getCurrPlayer()->levelup();
        }

        currGame->changeCurrPlayer();
      }
}

void handleSpecAction(Game *currGame, int filledRows) {
  //check if a row has been cleared
  if (filledRows >= 2) {
    // trigger special action
    string s;
    cout << "You have cleared " << filledRows << " rows. Please choose a special action (heavy/force/blind):" << endl;

    cin >> s;
    while (s != "heavy" && s != "blind" && s != "force") {
      cout << "Not a valid special action. Please choose one from heavy, blind, or force." << endl;
      cin >> s;
    }

    char block = '\0';
    if (s == "force") {
      while (block != 'T' && block != 'O' && block != 'S' && block != 'Z' && block != 'I' && block != 'J' && block != 'L') {
        cout << "Please enter a valid block to force on your opponent:" << endl;
        cin >> block;
      }
    }

    int id = -1;

    cout << "Please enter the player's id on whom you would like to apply " << s << ": "<<  endl;
    cin >> id;
    while (id < 1 || id > currGame->getNumPlayers() || id == currGame->getCurrPlayer()->getID()) {
      cout << "Please enter a valid id that isn't your own:" << endl;
      cin >> id;
    }

    currGame->getCurrPlayer()->effectOther(id, s, block);
  }
}

bool Interpreter::executeCommand(string s) {
  string arg;
  string commandName;

  int filledRows = 0;

  if (s == "rename") {

    string args;
    string arg;
    vector<string> commands;
    getline(cin, args);
    istringstream argStream{args};

    while (argStream >> arg) {
      commands.emplace_back(arg);
    }

    commandName = commands.back();
    commands.pop_back(); 

    // Look through all the command names that have been provided and insert
    // the renamed name in their vector array "value" as an alias.
    map<string, vector<string> *> prevCommands = impl->commands; 
    for (auto elem : prevCommands) {
      for (int i = 0; i < commands.size(); i++) {
        if (elem.first == commands[i]) {
          if (commands.size() == 1 && elem.second->size() == 1) elem.second->pop_back();
          elem.second->emplace_back(commandName);
        }
      }
    }
  }
  if (s == "left" || s == "right" || s == "down") {
    if ((s == "left" && currGame->getCurrPlayer()->left() == DROP) ||
        (s == "right" && currGame->getCurrPlayer()->right() == DROP) ||
        (s == "down" && currGame->getCurrPlayer()->down() == DROP))
    {
      s = "drop";	
    }
    else cout << *currGame << endl;
  }
  if (s == "clockwise" || s == "counterclockwise") {
    Player *p = currGame->getCurrPlayer();

    if ((s == "clockwise" && p->clockwise() == DROP) ||
        (s == "counterclockwise" && p->cclockwise() == DROP))
      s = "drop";
    cout << *currGame << endl;
  }
  if (s == "drop") {
    currGame->getCurrPlayer()->drop();
    currGame->getCurrPlayer()->getCurrBlock()->draw_block();
    filledRows = currGame->getCurrPlayer()->getGrid()->checkfilled();
    currGame->updateHighScore();
    currGame->getCurrPlayer()->endTurn();
    cout << *currGame << endl;

    handleSpecAction(currGame, filledRows); 

    if (currGame->getNumPlayers() == 0) {
      cout << "Player " << currGame->getWinner() << " has won the game!" << endl;
      delete currGame->getCurrPlayer();
      throw 1;
    }
    else {
      Player *p = currGame->getCurrPlayer();
     
      currGame->changeCurrPlayer();
      if (!currGame->playerIsIncluded(p)) delete p;
    }
    return true;
  }
  if (s == "leveldown" || s == "levelup") {
    Player *p = currGame->getCurrPlayer();

    if (s == "leveldown" && (currGame->getNumPlayers() <= 2 || p->getLevel() > 1)) 
      p->leveldown();
    else if (currGame->getNumPlayers() > 2 && s == "leveldown") 
      cout << "Can't access level 0 with more than 2 players in the game!" << endl;
    else {
      if (p->getLevel() < maxLevel)
        p->levelup();
    }

    cout << "New level: " << currGame->getCurrPlayer()->getLevel() << endl;
    cout << *currGame << endl;
  }

  Player *p = currGame->getCurrPlayer();
  if (s == "norandom" && (p->getLevel() == 3 || p->getLevel() == 4)) {
    string fileName;
    cin >> fileName;

    p->setSequence(fileName);
  }

  if (s == "random" && (p->getLevel() == 3 || p->getLevel() == 4)) {
    p->setSequence("");
  }

  if (s == "sequence") {
    string fileName;
    cin >> fileName;

    cout << fileName << endl;
    try {
      if (file.is_open()) file.close();
      file.open(fileName);
    } catch (...) {
      cout << "unknown error opening file" << endl;
    } 
  }
  if (s == "restart") {
    currGame->restart();
    if (startLvl == 0 && numPlayers <= 2) assignSeqFiles(currGame, seq1, seq2);
    else levelUpEveryone(currGame, startLvl);
  
    currGame->tick();
    cout << *currGame << endl;
  }
  if (s == "I" || s == "J" || s == "L" || s == "O" ||
      s == "S" || s == "T" || s == "Z") {
    // the block commands: L, O, etc
    currGame->getCurrPlayer()->getGrid()->erase_next(currGame->getCurrPlayer()->getNextBlockType());
    currGame->getCurrPlayer()->setNextBlockType(s[0]);
    currGame->getCurrPlayer()->getGrid()->display_next(s[0]);
    cout << *currGame << endl;
  }
  return false;
}

void Interpreter::eval() {
  string s;
  int commandsMatched = 0;
  string recentCommand;
  int multiplier = 0;

  map<string, vector<string> *> commands = impl->commands;

  while ((file.is_open() && file >> s) || cin >> s) {
    istringstream checkForInt{s};

    checkForInt >> multiplier >> s;

    for (auto elem : commands) {
      if (s == elem.first || s == elem.first.substr(0, s.length())) {
        commandsMatched++;
        recentCommand = elem.first;
      }
    }
    if (commandsMatched == 1 && recentCommand != "") {
      if (s != "restart" && s != "hint" && s != "norandom" && s != "random") {
        if (multiplier == 0) {
          currGame->getCurrPlayer()->getCurrBlock()->undraw_block();
          executeCommand(recentCommand);
          currGame->getCurrPlayer()->getCurrBlock()->draw_block();	
        }
        else {
          if (recentCommand == "drop") {
            for (int i = 0; i < multiplier; i++) {
              currGame->getCurrPlayer()->getCurrBlock()->undraw_block();
              try {
                executeCommand(recentCommand);
              } catch (int n) {
                if (n == 1) throw 2;
              }
              currGame->getCurrPlayer()->getCurrBlock()->draw_block();
            }
          }
          else {
            currGame->getCurrPlayer()->getCurrBlock()->undraw_block();
            for (int i = 0; i < multiplier; i++) {
              try {
                if (executeCommand(recentCommand)) break;
              } catch (int n) {
                if (n == 1) throw 2;
              }
            }	
            currGame->getCurrPlayer()->getCurrBlock()->draw_block();
          }
        }
      }
      else {
        try {
          executeCommand(recentCommand);
        } catch (int n) {
          if (n == 1) throw 2;
        }
      }
    }
    else {
      // if it's not the first (generic) command, it might be a renamed command
      vector<string> loc;
      for (auto elem : commands) {
        for (auto alias : *elem.second) {
          if (s == alias) {
            loc.emplace_back(elem.first);
          }
        }
      }

      if (loc.size() == 0) {
        cout << "Please enter a valid command." << endl;
      }
      else {
        if (multiplier == 0) multiplier = 1;
        for (int i = 0; i < multiplier; i++) {
          for (auto str : loc) {
            try {
              if (executeCommand(str)) break;
            } catch (int n) {
              if (n == 1) throw 2;
            }
          }
        }
      }
    }
    commandsMatched = 0; // reset matched counter
  }
}

Interpreter::~Interpreter() {
  auto commands = impl->getCommands();

  for (auto it = commands.begin(); it != commands.end(); it++) {
    delete it->second;
  }
  delete impl;
  delete currGame;
}
