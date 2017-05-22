#pragma once

#include <iostream>
#include <string>
#include <list>

namespace Debug {

  class Shell {

    std::string			_cmd;
    std::list<std::string>	_args;

    void	CheckCommand(std::string cmd);
    int		GetArgCount(std::string cmd);
    
  public:

    Shell();
    ~Shell();
    
    void	Execute();
    void	ParseCommand(std::string cmd);
  };
};
