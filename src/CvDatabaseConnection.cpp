#include "CvDatabaseConnection.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>

CvDatabaseConnection::CvDatabaseConnection(const std::string& filename)
 : _stddev(0), _avgLineLength(0), _handle(nullptr)
{
  this->_filename = "file:" + filename;
  if (filename != "")
  {
    sqlite3_open(filename.c_str(), &this->_handle);
  }
}

CvDatabaseConnection::~CvDatabaseConnection()
{
  this->close();
}

void CvDatabaseConnection::close()
{
  if (this->_filename != "")
    sqlite3_close(this->_handle);
}

std::string CvDatabaseConnection::getRandomStartingWord(const std::string& name, std::string* realName)
{
  std::string statement = "SELECT * FROM conversations WHERE `name` COLLATE NOCASE =? AND `is_starting`=1";
  sqlite3_stmt* stmtObj;

  int rc = sqlite3_prepare_v2(this->_handle,
                              statement.c_str(),
                              statement.length() + 1,
                              &stmtObj,
                              NULL);
  if (rc != SQLITE_OK)
    return "";
  
  sqlite3_bind_text(stmtObj, 1, name.c_str(), -1, 0);
  std::vector<std::string> words;
  bool flag = true;

  while (rc = sqlite3_step(stmtObj), 1)
  {
    if (rc == SQLITE_DONE)
      break;
    else if (rc == SQLITE_ROW)
    {
      if (flag)
      {
        *realName = reinterpret_cast<const char*>(sqlite3_column_text(stmtObj, 1));
        flag = false;
      }
      std::string columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmtObj, 2)));
      words.push_back(columnText);
    } else if (rc == SQLITE_BUSY) {
      std::chrono::milliseconds duration(100);
      std::this_thread::sleep_for(duration);
      continue;
    } else
      break;
  }

  if (words.size() == 0)
    return "";

  sqlite3_finalize(stmtObj);
  srand(time(NULL));
  
  return words[rand() % words.size()];
}

/* int sqlite3_exec(
  sqlite3*,                                  An open database 
  const char *sql,                           SQL to be evaluated 
  int (*callback)(void*,int,char**,char**),  Callback function 
  void *,                                    1st argument to callback 
  char **errmsg                              Error msg written here 
);*/
std::vector<std::string> CvDatabaseConnection::getPossibleWordsOf(const std::string& name, const std::string& word)
{
  std::string statement = "SELECT * FROM conversations WHERE `name` COLLATE NOCASE =? AND `word_a`=?";

  sqlite3_stmt* stmtObj;
  
  int rc = sqlite3_prepare_v2(this->_handle, 
                              statement.c_str(), 
                              statement.length() + 1, 
                              &stmtObj, 
                              NULL);
  if (rc != SQLITE_OK)
    return std::vector<std::string>();

  sqlite3_bind_text(stmtObj, 1, name.c_str(), -1, 0);
  sqlite3_bind_text(stmtObj, 2, word.c_str(), -1, 0);

  std::vector<std::string> words;  
  // TODO handle error codes...
  while ((rc = sqlite3_step(stmtObj)))
  {
    if (rc == SQLITE_DONE)
      break;
    else if (rc == SQLITE_ROW)
    {
      std::string columnText(reinterpret_cast<const char*>(sqlite3_column_text(stmtObj, 3)));
      words.push_back(columnText);
    } else if (rc == SQLITE_BUSY) {
      std::chrono::milliseconds duration(100);
      std::this_thread::sleep_for(duration);
      continue;
    } else
      break;
  }

  sqlite3_finalize(stmtObj);
  return words;
}

double CvDatabaseConnection::getAverageLineLength()
{
  // TODO
  return 7.0;
}

double CvDatabaseConnection::getLineLengthStdDev()
{
  // TODO
  return 4.0;
}