#include "interpreter.h"
#include <string>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
  bool textOnly = false;
  int startLvl = 0;
  long int randSeed = static_cast<long int>(time(nullptr));
  string seq1 = "";
  string seq2 = "";
  int maxLevel = 4;

  int numPlayers = 2;
  
  for (int i = 1; i < argc; i++) {
    if (string(argv[i]) == "-text") textOnly = true;
    else if (string(argv[i]) == "-seed") {
      randSeed = stoi(string(argv[i+1]));
    }
    else if (string(argv[i]) == "-scriptfile1") {
      seq1 = string(argv[i+1]);
    }
    else if (string(argv[i]) == "-scriptfile2") {
      seq2 = string(argv[i+1]);
    }
    else if (string(argv[i]) == "-startlevel") {
      startLvl = stoi(string(argv[i+1]));
    }
    else if (string(argv[i]) == "-numplayers") {
      numPlayers = stoi(string(argv[i+1]));
    }
    else if (string(argv[i]) == "-maxlevel") {
      maxLevel = stoi(string(argv[i+1]));
    }
  }
  Interpreter i{randSeed, seq1, seq2, (numPlayers > 2 && startLvl == 0 ? 1 : startLvl), textOnly, numPlayers, maxLevel};
  try {
    i.eval();
  } catch (int n) {
    if (n == 2) return EXIT_FAILURE;
  }
}
