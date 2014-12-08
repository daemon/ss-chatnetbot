#include <sqlite3.h>
#include "CvDatabase.hpp"

CvDatabase& CvDatabase::instance(const std::string& filename)
{
  static CvDatabase db;
  if (db._filename == "")
    db._filename = filename;

  return db;
}

CvDatabaseConnection CvDatabase::newConnection()
{
  return CvDatabaseConnection(this->_filename);
}