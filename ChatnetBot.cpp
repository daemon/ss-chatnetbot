#include <algorithm>
#include <functional>
#include <type_traits>
#include <utility>
#include <iostream>
#include <winsock2.h>

#include "ChatnetBot.hpp"
#include "CommandSet.hpp"
#include "Common.hpp"
#include "Player.hpp"
#include "Zone.hpp"

ChatnetBot::ChatnetBot(std::shared_ptr<Player> player) : _player(player), _running(false)
{
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
  this->_running = true;
  this->_thd = std::thread(std::bind(&ChatnetBot::_run, this, blocking));
  this->_thd.join();
}

void ChatnetBot::stop()
{
  this->_player->stopListen();
  this->_running = false;
  this->_cv.notify_all();
}

void ChatnetBot::_notify(Player* player, Message message)
{
  this->_recvQueue[player] = message;
  this->_cv.notify_all(); 
}

void ChatnetBot::_run(bool blocking)
{
  std::unique_lock<std::mutex> lock(this->_mtxMap);
  // Don't care about @blocking for now...implement later TODO
  while (this->_running)
  {
    this->_cv.wait(lock);
    if (!this->_running)
      break;
    else
    {
      for (auto p : this->_recvQueue)
        for (auto& c : this->_commandsets)
            c->onMessage(p.first /* shptrPlayer */, p.second /* Message */);        
    }
  }
}

std::vector<std::unique_ptr<CommandSet>>& ChatnetBot::getCommandSets()
{
  return this->_commandsets;
}