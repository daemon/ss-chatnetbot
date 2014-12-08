#include <cstdlib>
#include <ctime>
#include <regex>
#include <string>
#include <vector>
#include "CvDatabase.hpp"
#include "CvDatabaseConnection.hpp"
#include "Message.hpp"
#include "SayCommand.hpp"

static const std::regex _SAY_RGX(R"(^\s*?\!say\s+(.+?)$)");

void SayCommand::_onMessage(Player* player, const Message& message)
{
  if (message.TYPE != Message::Type::MSG_PRIVATE)
    return;

  // TODO message parser class & factory...refactor
  std::smatch m;
  if (!std::regex_match(message.getMessage(), m, _SAY_RGX))
    return;
  std::string name(m[1].str());
  auto conn = CvDatabase::instance().newConnection();
  std::string startingWord = conn.getRandomStartingWord(name);

  if (startingWord == "")
  {
    player->sendPrivateMessage(message.getSender(), "No matching player.");
    return;
  }

  bool flag = true;
  std::string word(startingWord);
  while (flag)
  {    
   std::vector<std::string> words = conn.getPossibleWordsOf(name, word);
  }
}