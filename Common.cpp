#include "Common.hpp"

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0501

#include <cassert>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

inline void common::program_initialize()
{
	WSADATA tmp;
	assert(WSAStartup(MAKEWORD(2, 2), &tmp) == 0);
}

inline void common::program_cleanup()
{
	WSACleanup();
}