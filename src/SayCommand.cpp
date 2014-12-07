#include "MarkovDatabaseConnection.hpp"
#include "MarkovDatabase.hpp"
#include "SayCommand.hpp"

void SayCommand::_onMessage(Player* player, const Message& message)
{
  auto db = this->_database.lock();
  if (!db)
    return;

  auto dbConn = db->newConnection();
}