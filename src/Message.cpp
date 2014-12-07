#include "Common.hpp"
#include "Message.hpp"

const std::regex Message::_RGX_PRIV(R"(^MSG:PRIV:(.+?):(.+?)$)");
const std::regex Message::_RGX_TEAM(R"(^MSG:FREQ:(.+?):(.+?)$)");

Message Message::parseReceivedMessage(const std::string &message)
{  
  std::smatch match;
  Message m(message);

  // Should convert to CoR...
  if (std::regex_match(message, match, Message::_RGX_PRIV))
  {
    m._sender   = match[1].str();
    m.TYPE      = Type::MSG_PRIVATE;
    m._message  = match[2].str();
  } else if (std::regex_match(message, match, Message::_RGX_TEAM)) {
    m._sender  = match[1].str();
    m.TYPE     = Type::MSG_TEAM;
    m._message = match[2].str();
  }
  
  return m;
}

std::string Message::getSender() const
{
  return this->_sender;
}

std::string Message::getRawMessage() const
{
  return this->_rawMessage;
}

std::string Message::getMessage() const
{
  return this->_message;
}

Message Message::createPrivateMessage(const std::string& playerFrom, 
  const std::string& playerTo, const std::string& message)
{
  Message m("SEND:PRIV:" + playerTo + ":" + message + "\n");
  m._sender   = playerFrom;
  m._message  = message;
  m.TYPE      = Type::MSG_TEAM;

  return m;
}

Message Message::createLoginMessage(const std::string& name, const std::string& password)
{
  Message m("LOGIN:1:" + name + ":" + password + "\n");
  m._sender = name;

  return m;
}

Message Message::createTeamMessage(const std::string& name,
  const std::string& freqNum, const std::string& message)
{
  Message m("SEND:FREQ:" + freqNum + ":" + message + "\n");
  m._sender = name;

  return m;
}

Message Message::createGoMessage(const std::string& arena)
{
  Message m("GO:" + arena + "\n");
  return m;
}