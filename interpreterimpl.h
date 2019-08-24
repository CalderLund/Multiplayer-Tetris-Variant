#ifndef _INTERPRETER_IMPL_H
#define _INTERPRETER_IMPL_H

#include <map>
#include <string>
#include <vector>

struct InterpreterImpl {
  std::map<std::string, std::vector<std::string> *> commands;

  public:
  InterpreterImpl() {
    std::string arr[20] = {"left", "right", "down", "clockwise", "counterclockwise", "drop", "levelup", "leveldown",
      "norandom", "random", "sequence", "I", "J", "L", "O", "S", "Z", "T", "restart", "rename"};
    for (int i = 0; i < 20; i++) {
      commands[arr[i]] = new std::vector<std::string>{};
    }
  }
  std::map<std::string, std::vector<std::string> *> getCommands() {
    return commands;
  }
  ~InterpreterImpl() {}
};

#endif
