#ifndef __ABOUT_COMMAND_H__
#define __ABOUT_COMMAND_H__

#include <memory>

#include "Command.hpp"

class ChatnetBot; // chatnetbot.hpp
class Player; // Player.hpp
class Message; // Message.hpp

static const std::string ABOUT_COMMAND_NAME = "about";
static const std::string ABOUT_COMMAND_DOC  = "Gives info about the bot. !about";

class AboutCommand : public Command
{
public:
  AboutCommand(const std::string& aboutText) : Command(ABOUT_COMMAND_NAME, ABOUT_COMMAND_DOC), _aboutText(aboutText) {}
private:
  virtual void _onMessage(std::shared_ptr<Player> player, const Message& message);
  std::string _aboutText;
};

#endif