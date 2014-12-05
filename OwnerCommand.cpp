#include <regex>
#include <sstream>

#include "Common.hpp"
#include "Message.hpp"
#include "OwnerCommand.hpp"
#include "Player.hpp"

static const std::regex _OWNER_RGX(BASIC_CMD_RGX(owner));

void OwnerCommand::_onMessage(std::shared_ptr<Player> player, const Message& message)
{
	if (message.TYPE != Message::Type::MSG_PRIVATE)
		return;
	else if (!std::regex_match(message.getMessage(), _OWNER_RGX))
		return;  

  player->sendPrivateMessage(message.getSender(), this->_owner);
}