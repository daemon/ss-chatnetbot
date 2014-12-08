#include <cstdlib>
#include <ctime>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include "CvDatabase.hpp"
#include "CvDatabaseConnection.hpp"
#include "Message.hpp"
#include "NormalDistribution.hpp"
#include "Player.hpp"
#include "SayCommand.hpp"

static const std::regex _SAY_RGX(R"(^\s*?\!say\s+(.+?)$)");

void SayCommand::_onMessage(Player* player, const Message& message)
{
  if (message.TYPE != Message::Type::MSG_PRIVATE &&
      message.TYPE != Message::Type::MSG_TEAM)
    return;

  // TODO message parser class & factory...refactor
  std::smatch m;
  if (!std::regex_match(message.getMessage(), m, _SAY_RGX))
    return;

  std::string name(m[1].str());
  auto conn = CvDatabase::instance("conversations.db").newConnection();
  std::string realName;
  std::string startingWord = conn.getRandomStartingWord(name, &realName);

  if (startingWord == "")
  {
    player->sendPrivateMessage(message.getSender(), "No matching player.");
    return; 
  }

  int length = 0;
  NormalDistribution normal(3.0, 10.0);
  std::string word(startingWord);
  std::string tmpWord = word;

  srand(time(NULL));
  // int r = rand() % 100;  

  while (++length, 1)
  {    
    std::vector<std::string> words = conn.getPossibleWordsOf(name, tmpWord);

    if (words.size() == 0)
      break;
    std::string randWord(words[rand() % words.size()]);

    if (randWord == "")
      break;
    word += " " + randWord;
    tmpWord = randWord;

    /* double p = normal.computeCdfVal(length) * 100; TODO FIX NORMALDIST
    if (r < p)
      break;*/

    if (length > 15)
      break; // temporary
  }
  // TODO add freq attribute to player...
  player->sendFreqMessage("1337", realName + "> " + word);
}