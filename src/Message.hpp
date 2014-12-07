#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <regex>
#include <string>

class Message
{
public:
  enum Type
  {
    MSG_NONE
  , MSG_PRIVATE
  , MSG_TEAM
  };

  Message() : TYPE(Type::MSG_NONE) {}
  Message(const std::string &message) : TYPE(Type::MSG_NONE), _rawMessage(message) {}
  
  std::string getSender() const;
  std::string getRawMessage() const;
  std::string getMessage() const;

  static Message parseReceivedMessage(const std::string& message);  
  static Message createPrivateMessage(const std::string& playerFrom, 
                                      const std::string& playerTo, 
                                      const std::string& message);
  static Message createLoginMessage(const std::string& name,
                                    const std::string& password);
  static Message createTeamMessage(const std::string& name,
                                   const std::string& freqNum, 
                                   const std::string& message);
  static Message createGoMessage(const std::string& arena);
  Message::Type TYPE;

private:
  std::string _rawMessage;
  std::string _message;
  std::string _sender;
  static const std::regex _RGX_PRIV;
  static const std::regex _RGX_TEAM;
};

#endif