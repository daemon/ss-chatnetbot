#ifndef __CHAT_CONNECTION_H__
#define __CHAT_CONNECTION_H__

#include <list>
#include <memory>
#include <vector>
#include <winsock2.h>

#include "Message.hpp"
#include "Zone.hpp"

typedef int ReturnType;

class ChatnetConnection
{
public:
  struct ReturnTypes
  {
    static const ReturnType CONN_OK          = 1;
    static const ReturnType CONN_FAIL        = 1 << 1;
    static const ReturnType CONN_FAILLOGIN   = 1 << 2;
    static const ReturnType CONN_FAILDC      = 1 << 3;
    static const ReturnType CONN_FAILNOCONN  = 1 << 4;

    static const ReturnType RECV_OK           = 1;
    static const ReturnType RECV_CONNRST      = 1 << 1;
    static const ReturnType RECV_FAIL         = 1 << 2;
    static const ReturnType RECV_CONNSHUTDOWN = 1 << 3;
  };

  ChatnetConnection() : _sockfd(-1) {}
  // TODO: Destructor

  operator bool() const;
  ReturnType connect(const Zone& zone);
  void disconnect();

  bool send(const Message& message);
  ReturnType listen(std::list<Message>& msgs, unsigned long blockTimeSec = 8);

private:
  int _sockfd;
};

#endif