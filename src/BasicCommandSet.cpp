#include "AboutCommand.hpp"
#include "BasicCommandSet.hpp"
#include "ChatnetBot.hpp"
#include "HelpCommand.hpp"
#include "OwnerCommand.hpp"
#include "ShutdownCommand.hpp"

BasicCommandSet::BasicCommandSet(const std::string& aboutText, const std::string& ownerName, std::shared_ptr<ChatnetBot> bot)
  : CommandSet()
{
  this->addCommand(std::unique_ptr<Command>(new AboutCommand(aboutText)));
  this->addCommand(std::unique_ptr<Command>(new OwnerCommand(ownerName)));
  this->addCommand(std::unique_ptr<Command>(new HelpCommand(bot)));
  this->addCommand(std::unique_ptr<Command>(new ShutdownCommand()));
}