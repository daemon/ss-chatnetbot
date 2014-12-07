#ifndef __ZONE_H__
#define __ZONE_H__

#include <string>

struct Zone
{
  Zone(const std::string& name_, const std::string& ip_, const std::string& port_)
   : name(name_), ip(ip_), port(port_) {}
  std::string name;
  std::string ip;
  std::string port;
};

#endif