#ifndef __OWNER_COMMAND_H__
#define __OWNER_COMMAND_H__

#include <memory>

#include "Command.hpp"

class ChatnetBot; // chatnetbot.hpp
class Player; // Player.hpp
class Message; // Message.hpp

static const std::string OWNER_COMMAND_NAME = "owner";
static const std::string OWNER_COMMAND_DOC  = "Shows the owner. !owner";

class OwnerCommand : public Command
{
public:
  OwnerCommand(const std::string& ownerName) : Command(OWNER_COMMAND_NAME, OWNER_COMMAND_DOC), _owner(ownerName) {}
private:
  virtual void _onMessage(std::shared_ptr<Player> player, const Message& message);
  std::string _owner;
};

#endif