#include <regex>
#include <sstream>

#include "ChatnetBot.hpp"
#include "CommandSet.hpp"
#include "Common.hpp"
#include "HelpCommand.hpp"
#include "Message.hpp"
#include "Player.hpp"

static const std::regex _HELP_RGX(BASIC_CMD_RGX(help));

void HelpCommand::_onMessage(Player* player, const Message& message)
{
  if (message.TYPE != Message::Type::MSG_PRIVATE)
    return;
  else if (!std::regex_match(message.getMessage(), _HELP_RGX))
    return;

  auto ptr = this->_bot.lock();
  if (!ptr)
    return;

  std::stringstream ss;
  ss << "Commands:";

  for (auto& cmdset : ptr->getCommandSets())
    for (auto& cmd : cmdset->getCommands())
      ss << " " << cmd->getName();

  player->sendPrivateMessage(message.getSender(), ss.str());
}