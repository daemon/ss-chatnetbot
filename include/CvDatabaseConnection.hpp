#ifndef __CV_DATABASE_CONNECTION_H__
#define __CV_DATABASE_CONNECTION_H__

#include <sqlite3.h>
#include <string>
#include <vector>

// TODO Make cache? Profile to see if we need one.

class CvDatabaseConnection
{
public:
  CvDatabaseConnection(const std::string& filename);
  ~CvDatabaseConnection();

  std::string getRandomStartingWord(const std::string& name, std::string* realName);
  std::vector<std::string> getPossibleWordsOf(const std::string& name, 
                                              const std::string& word);
  double getAverageLineLength();
  double getLineLengthStdDev();
  void close();
private:
  double _stddev;
  double _avgLineLength;
  std::string _filename;
  sqlite3* _handle;
};

#endif