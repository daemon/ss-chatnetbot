#include "Command.hpp"

void Command::onMessage(Player* player, const Message& message)
{
  this->_onMessage(player, message);
}

std::string Command::getName() const
{
  return this->_name;
}

std::string Command::getDocumentation() const
{
  return this->_doc;
}