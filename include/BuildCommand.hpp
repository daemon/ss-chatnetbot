#ifndef __BUILD_COMMAND_HPP__
#define __BUILD_COMMAND_HPP__

#include <memory>

#include "Command.hpp"

static const std::string BUILD_COMMAND_NAME = "build";
static const std::string BUILD_COMMAND_DOC  = "!build <ship #> to find optimal items for ship #. PM !build 3";

class BuildCommand : public Command
{
public:
  BuildCommand() : Command(BUILD_COMMAND_NAME, BUILD_COMMAND_DOC) {}
private:
  virtual void _onMessage(Player* player, const Message& message);
};

#endif