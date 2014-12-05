#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <memory>
#include <atomic>
#include <thread>

#include "ChatnetBot.hpp"
#include "Observable.hpp"
#include "Zone.hpp"

class ChatnetBot; // ChatnetBot.hpp
class ChatnetConnection; // ChatnetConnection.hpp
class Message; // Message.hpp

class Player : public common::Observable<ChatnetBot, Message>
{
public:
  Player(const std::string &name, const std::string &password);
  std::weak_ptr<ChatnetConnection> getConnection();

  bool connect(const Zone& zone);
  bool disconnect();
  void runListen();
  void stopListen();

  void login();
  void sendFreqMessage(const std::string& freq, const std::string& message);
  void sendPrivateMessage(const std::string& playerTo, const std::string& message);
  void goToArena(const std::string& name);

private:
  void _runListen();
  std::shared_ptr<ChatnetConnection> _connection;
  std::string _name;
  std::string _password;
  std::atomic<bool> _running;
  std::thread _thd;
};

#endif