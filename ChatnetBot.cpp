#include <algorithm>
#include <functional>
#include <type_traits>
#include <utility>
#include <winsock2.h>

#include "ChatnetBot.hpp"
#include "CommandSet.hpp"
#include "Common.hpp"
#include "Player.hpp"
#include "Zone.hpp"

ChatnetBot::ChatnetBot(std::shared_ptr<Player> player) : _player(player), _running(false)
{
  this->_uMtxMap = std::unique_lock<std::mutex>(this->_mtxMap); // fix
  this->_uMtxMap.unlock();
  this->_player->addObserver(this);
}

void ChatnetBot::addCommandSet(std::unique_ptr<CommandSet> set)
{
  this->_commandsets.push_back(std::move(set));
}
/*
void ChatnetBot::removeCommandSet(int id)
{
  std::remove_if(this->_commandsets.begin(), this->_commandsets.end(),
    [&](std::shared_ptr<CommandSet> set) 
    {
      return set->getId() == id;
    });
}
*/
bool ChatnetBot::connect(const Zone& zone, bool blocking)
{
  return this->_player->connect(zone);
}

bool ChatnetBot::disconnect(bool blocking)
{
  return this->_player->disconnect();
}

bool ChatnetBot::login()
{
  this->_player->login();
  return true; // Implement later with futures..
}

void ChatnetBot::run(bool blocking)
{
  this->_player->runListen();
  this->_thd = std::thread(std::bind(&ChatnetBot::_run, this, blocking));
}

void ChatnetBot::stop()
{
  this->_running = false;
  this->_cv.notify_all();
  if (this->_thd.joinable())
    this->_thd.join();
}

void ChatnetBot::_notify(Player* player, Message message)
{
  this->_uMtxMap.lock();
  this->_recvQueue[player] = message;
  this->_cv.notify_all(); 
}

void ChatnetBot::_run(bool blocking)
{
  this->_uMtxMap.lock();
  // Don't care about @blocking for now...implement later
  while (this->_running)
  {
    this->_cv.wait(this->_uMtxMap);
    if (!this->_running)
      break;
    else
    {
      for (auto p : this->_recvQueue)
        for (auto& c : this->_commandsets)
            c->onMessage(p.first /* shptrPlayer */, p.second /* Message */);        
    }
  }
  this->_uMtxMap.unlock();
}

std::vector<std::unique_ptr<CommandSet>>& ChatnetBot::getCommandSets()
{
  return this->_commandsets;
}