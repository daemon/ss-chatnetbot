#ifndef __CHATNET_BOT_H__
#define __CHATNET_BOT_H__

#include <atomic>
#include <condition_variable>
#include <map>
#include <memory>
#include <thread>

#include "Message.hpp"
#include "Observer.hpp"
#include "Zone.hpp"

class Player; // Player.hpp
class Zone; // Zone.hpp
class CommandSet; // CommandSet.hpp

class ChatnetBot : public common::Observer<std::shared_ptr<Player>, Message>
{
public:
  ChatnetBot(std::shared_ptr<Player> player);
  // TODO Destructor
  template <typename T>
  void addCommandSet(T&& set);
  std::vector<CommandSet>& getCommandSets();
  void removeCommandSet(int id);

  bool connect(const Zone& zone, bool blocking = true);
  bool disconnect(bool blocking = true);
  bool login();

  void run(bool blocking = false);
  void stop();

  std::vector<Zone>& getActiveZones();
protected:
  std::shared_ptr<Player> getOwner();

private:
  virtual void _run(bool blocking);
  virtual void _notify(std::shared_ptr<Player> player, Message message);
  
  std::vector<Zone> _zones;
  std::vector<std::unique_ptr<CommandSet>> _commandsets;
  std::map<std::shared_ptr<Player>, Message> _recvQueue;
  std::thread _thd;
  std::shared_ptr<Player> _player;
  std::condition_variable _cv;
  std::unique_lock<std::mutex> _uMtxMap;
  std::mutex _mtxMap;
  std::atomic<bool> _running;
};


#endif