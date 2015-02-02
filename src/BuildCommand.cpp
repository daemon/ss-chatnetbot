#include <cstdlib>
#include <ctime>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include "Message.hpp"
#include "Player.hpp"
#include "BuildCommand.hpp"

static const std::regex _BUILD_RGX(R"(^\s*?\!build\s+(\d).+$)"); // TODO: fix later

void BuildCommand::_onMessage(Player* player, const Message& message)
{
  if (message.TYPE != Message::Type::MSG_PRIVATE)
    return;

  // TODO message parser class & factory...refactor
  std::smatch m;
  if (!std::regex_match(message.getMessage(), m, _BUILD_RGX))
    return;

  int shipNo = std::stoi(m[1].str());
}