#include "Common.hpp"

#if !defined(WIN32_LEAN_AND_MEAN) && !(_WIN32_WINNT == 0x0501)
#undef _WIN32_WINNT
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0501
#endif

#include <cassert>
#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

void common::program_initialize()
{
  WSADATA tmp;
  assert(WSAStartup(MAKEWORD(2, 2), &tmp) == 0);
}

void common::program_cleanup()
{
  WSACleanup();
}
