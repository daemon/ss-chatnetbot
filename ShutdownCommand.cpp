#include <algorithm>
#include <regex>
#include <sstream>
#include <cstdlib>

#include "Common.hpp"
#include "Message.hpp"
#include "Player.hpp"
#include "ShutdownCommand.hpp"

static const std::regex _SHUTDOWN_RGX(BASIC_CMD_RGX(shutdown));

void ShutdownCommand::_onMessage(std::shared_ptr<Player> player, const Message& message)
{
	if (message.TYPE != Message::Type::MSG_PRIVATE)
		return;
	else if (!std::regex_match(message.getMessage(), _SHUTDOWN_RGX))
		return;

	auto sender = message.getSender();
	static const std::vector<std::string> mods{"ceiu", "noldec", "nn", "cdb-man"};
	common::sto_lower(sender);

	if (std::find(mods.begin(), mods.end(), sender))
	{
		player->sendPrivateMessage(message.getSender(), "Shuting down, you're High-ness..."); // Yes, this is a joke.
		// Change later.
  	abort();
	}
}