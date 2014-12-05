#ifndef __SHUTDOWN_COMMAND_H__
#define __SHUTDOWN_COMMAND_H__

#include <memory>

#include "Command.hpp"

class ChatnetBot; // chatnetbot.hpp
class Player; // Player.hpp
class Message; // Message.hpp

static const std::string SHUTDOWN_COMMAND_NAME = "owner";
static const std::string SHUTDOWN_COMMAND_DOC  = "Shows the owner. !owner";

class ShutdownCommand : public Command
{
public:
  ShutdownCommand() : Command(SHUTDOWN_COMMAND_NAME, SHUTDOWN_COMMAND_DOC) {}
private:
  virtual void _onMessage(Player* player, const Message& message);
};

#endif