#include <chrono>
#include <memory>
#include <thread>
#include <utility>
#include <iostream>
#include "BasicCommandSet.hpp"
#include "ChatnetBot.hpp"
#include "CommandSet.hpp"
#include "Common.hpp"
#include "Item.hpp"
#include "ItemDatabase.hpp"
#include "ItemHeap.hpp"
#include "Player.hpp"
#include "Zone.hpp"

int main(int argc, char **argv)
{
  common::program_initialize();
  for (auto i : ItemDatabase::getInstance().getItems())
    std::cout << *i << std::endl;
  std::cout << std::endl;
  ItemHeap::Builder builder(ItemHeap::getDefaultCostFunction());
  builder.build(7);

  auto player = std::make_shared<Player>("tetris-", "password");
  auto bot = std::make_shared<ChatnetBot>(player);

  std::unique_ptr<CommandSet> basicCommandSet(new BasicCommandSet("Work-in-progress: I compute good ship builds using simple rules. !help build", "nn", bot));
  bot->addCommandSet(std::move(basicCommandSet));

  if (!bot->connect(Zone("Hyperspace", "142.4.200.80", "5005")))
  {
    std::cout << "Cannot connect!" << std::endl;
    bot->stop();
    return 0;
  }
  std::cout << "Connected." << std::endl;
  bot->login();
  // TODO change sleep...
  std::this_thread::sleep_for(std::chrono::milliseconds(4000));
  player->goToArena("");
  std::cout << "In arena." << std::endl;
  bot->run();

  // TODO clean destruction
  common::program_cleanup();
  return 0;
}