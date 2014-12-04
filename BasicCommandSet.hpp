#ifndef __BASIC_COMMAND_SET_H__
#define __BASIC_COMMAND_SET_H__

#include "CommandSet.hpp"

class ChatnetBot; // ChatnetBot.hpp

class BasicCommandSet : public CommandSet
{
public:
	BasicCommandSet(const std::string& aboutText, 
									const std::string& ownerName,
									std::shared_ptr<ChatnetBot> bot);
};

#endif