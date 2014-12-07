#ifndef __SAY_COMMAND_H__
#define __SAY_COMMAND_H__

#include <memory>

#include "Command.hpp"

static const std::string SAY_COMMAND_NAME = "say";
static const std::string SAY_COMMAND_DOC  = "Constructs a sentence that <player> might say. !say player";

class SayCommand : public Command
{
public:
  SayCommand(std::weak_ptr<MarkovDatabase> database) : _database(database) {}
private:
  virtual void _onMessage(Player* player, const Message& message);
  std::weak_ptr<MarkovDatabase> _database;
};

#endif