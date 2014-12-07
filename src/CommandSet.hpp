#ifndef __COMMAND_SET_H__
#define __COMMAND_SET_H__

#include <atomic>
#include <memory>
#include <vector>

#include "Command.hpp"

class Player; // player.hpp
class Message; // message.hpp

class CommandSet : public Command
{
public:
  CommandSet() : Command("", "") {}

  std::vector<std::unique_ptr<Command>>& getCommands();
  void addCommand(std::unique_ptr<Command> command);
private:
  virtual void _onMessage(Player* player, const Message& message);
  void _dispatchMessage(Player* player, const Message& message);

  // @unsigned int: call count for optimization, will be recalibrated to prevent overflow...
  // TODO: make tree, priority queue...
  std::vector<std::unique_ptr<Command>> _commands;
};

#endif