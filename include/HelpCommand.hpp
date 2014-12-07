#ifndef __HELP_COMMAND_H__
#define __HELP_COMMAND_H__

#include <memory>

#include "Command.hpp"

class ChatnetBot; // chatnetbot.hpp
class Player; // Player.hpp
class Message; // Message.hpp

static const std::string HELP_COMMAND_NAME = "help";
static const std::string HELP_COMMAND_DOC  = "Displays help about bot or command. !help [command]";

class HelpCommand : public Command
{
public:
  HelpCommand(std::shared_ptr<ChatnetBot> bot) : Command(HELP_COMMAND_NAME, HELP_COMMAND_DOC), _bot(bot) {}
private:
  virtual void _onMessage(Player* player, const Message& message);
  std::weak_ptr<ChatnetBot> _bot;
};

#endif