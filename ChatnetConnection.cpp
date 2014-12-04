#include <cassert>
#include <cstring>
#include <windows.h>

#include "ChatnetConnection.hpp"
#include "Common.hpp"
#include "Message.hpp"

ChatnetConnection::ReturnType ChatnetConnection::connect(const Zone& zone)
{
  this->_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  assert(this->_sockfd != INVALID_SOCKET);

  addrinfo hints, *result;
  ZeroMemory(hints, sizeof(hints)); 
  hints.ai_family     = AF_INET;
  hints.ai_socktype   = SOCK_STREAM;
  hints.ai_protocol   = IPPROTO_TCP;

  int rv = getaddrinfo(zone.ip.c_str(), zone.port.c_str(), &hints, &result);
  assert(rv == 0);

  int rv2 = connect(this->_sockfd, hints->ai_addr, sizeof(hints->ai_addr));
  
  ReturnType retCode;
  if (rv2 == 0)
    retCode = ReturnTypes::CONN_OK;
  else if (WSAGetLastError() == WSAECONNREFUSED)
  {
    retCode = ReturnTypes::CONN_FAIL | ReturnTypes::CONN_FAILNOCONN;
    this->_sockfd = -1;
  } else {
    retCode = ReturnTypes::CONN_FAIL;
    this->_sockfd = -1;
  }
    
  freeaddrinfo(result);
  return retCode;
}

ChatnetConnection::operator bool() const
{
  return this->_sockfd != -1;
}

void ChatnetConnection::disconnect()
{
  if (this->_sockfd >= 0)
  {
    shutdown(this->_sockfd);
    closesocket(this->_sockfd);
  }
  this->_sockfd = -1;
}

bool ChatnetConnection::send(const Message& message)
{
  if (this->_sockfd < 0)
    return false;

  int ret = send(this->_sockfd, message.getRawMessage().c_str(), message.length(), 0);

  return ret != SOCKET_ERROR;
}

ReturnType ChatnetConnection::listen(std::list<Message>& msgs, unsigned int blockTimeSec = 8)
{
  if (this->_sockfd < 0)
    return ReturnTypes::RECV_FAIL;

  long secs = static_cast<long>(blockTimeSec);

  timeval tv;
  tv.tv_sec   = secs;
  tv.tv_usec  = 0;

  fd_set readFds;
  FD_ZERO(&readFds);
  FD_SET(this->_sockfd, &readFds);
  
  int nReadyFds = select(0 /* Berkeley legacy (Windows) */, &readFds, NULL, NULL, &tv);
  
  if (nReadyFds > 0)
  {
    char buf[200];
    int ret = recv(this->_sockfd, &buf, 200, 0);

    if (ret == WSACONNRESET)
    {
      this->disconnect();
      return ReturnTypes::RECV_CONNRST | RECV_FAIL;
    } else if (ret <= 0) {
      this->disconnect();
      return ReturnTypes::RECV_FAIL | ReturnTypes::RECV_CONNSHUTDOWN;
    } else {
      size_t len = 200;
      char *token;

      while (common::next_tokenize(&buf, &len, '\n', &token))
        msgs.push_back(Message::parseReceivedMessage(buf));
      
      return ReturnTypes::RECV_OK;
    }
  }
}