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

  void onMessage(Player* player, const Message& message);
private:
  virtual void _onMessage(Player* player, const Message& message) = 0;
  
  std::string _name;
  std::string _doc;
};

#endif