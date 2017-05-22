#include "DebugShell.hpp"

Debug::Shell::Shell() {

}

Debug::Shell::~Shell() {

}

int Debug::Shell::GetArgCount(std::string cmd) {
  unsigned int i;
  int count;
  
  i = 0;
  count = 0;
  while (i < cmd.length()) {
    i = cmd.find_first_of(' ', i) + 1;
    count++;
  }
  return (count);
}

void Debug::Shell::ParseCommand(std::string cmd) {
  unsigned int i;

  i = 0;
  this->_cmd = cmd.substr(0, cmd.find_first_of(' ', 0));
  std::cout << "CMD : " << cmd << std::endl;
  std::cout << "Arg count : " << this->GetArgCount(cmd) << std::endl;
  while (i < cmd.length()) {
    i++;
  }
}
