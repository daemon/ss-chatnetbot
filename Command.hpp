#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <memory>

class Player; // player.hpp
class Message; // message.hpp

class Command
{
public:
  Command(const std::string& name, const std::string& documentation) : _name(name), _doc(documentation) {}
  std::string getName() const;
  std::string getDocumentation() const;

  onMessage(std::shared_ptr<Player> player, const Message& message);
private:
  virtual void _onMessage(std::shared_ptr<Player> player, const Message& message) = 0;

  std::string _doc;
  std::string _name;
};

#endif