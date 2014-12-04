#include <algorithm>
#include <regex>
#include <sstream>
#include <cstdlib>

#include "Common.hpp"
#include "Message.hpp"
#include "Player.hpp"
#include "AboutCommand.hpp"

static const std::regex _ABOUT_RGX(BASIC_CMD_RGX(about));

void AboutCommand::_onMessage(std::shared_ptr<Player> player, const Message& message)
{
	if (message.TYPE != Message::Type::MSG_PRIVATE)
		return;
	else if (!std::regex_match(message.getMessage(), _ABOUT_RGX))
		return;

	auto sender = message.getSender();
	player->sendPrivateMessage(sender, this->_aboutText);
}