#include <regex>
#include <sstream>
#include "ChatnetBot.hpp"
#include "CommandSet.hpp"
#include "Common.hpp"
#include "HelpCommand.hpp"
#include "Message.hpp"
#include "Player.hpp"

static const std::regex _HELP_RGX(R"(^\s*?\!help\s*(.+?)?$)", std::regex_constants::icase);

void HelpCommand::_onMessage(Player* player, const Message& message)
{
  std::smatch m;
  if (message.TYPE != Message::Type::MSG_PRIVATE)
    return;
  else if (!std::regex_match(message.getMessage(), m, _HELP_RGX))
    return;

  auto ptr = this->_bot.lock();
  if (!ptr)
    return;

  std::stringstream ss;
  if (m[1].str() == "")
  {
    ss << "Commands:";

    for (auto& cmdset : ptr->getCommandSets())
      for (auto& cmd : cmdset->getCommands())
        ss << " " << cmd->getName();

  } else {
    for (auto& cmdset : ptr->getCommandSets())
      for (auto& cmd : cmdset->getCommands())
        if (cmd->getName() == m[1].str())
          ss << cmd->getDocumentation();
  }
  if (ss.str() == "")
    player->sendPrivateMessage(message.getSender(), "No such command");
  else
    player->sendPrivateMessage(message.getSender(), ss.str());
}