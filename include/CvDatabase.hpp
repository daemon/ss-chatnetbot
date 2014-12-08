#ifndef __CV_DATABASE_H__
#define __CV_DATABASE_H__

#include <string>
#include <sqlite3.h>

#include "Common.hpp"
#include "CvDatabaseConnection.hpp"

class CvDatabase
{
public:
  CvDatabaseConnection newConnection();
  static CvDatabase& instance(const std::string& filename);
private:
  std::string _filename;
};

#endif