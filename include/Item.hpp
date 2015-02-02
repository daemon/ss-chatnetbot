#ifndef __ITEM_HPP__
#define __ITEM_HPP__

#include <string>
#include <utility>
#include <vector>

struct ItemCategory
{
  ItemCategory(int id1, const std::string name1) : id(id1), name(name1) {}
  std::vector<Item> items;
  std::string name;
  int id;
};

struct ItemInfo
{
  std::string name;
  std::shared_ptr<ItemCategory> category;
  unsigned int money;
  unsigned int exp;
  unsigned int shipMask;
  int id;
};

struct ItemStat
{
  std::string name;
  int change;
  int maxmin;
  bool shouldMaximize;
  int id;
};

class Item
{
public:
  Item(const ItemInfo& info, const std::vector<ItemStat>& stats) : _info(info), _stats(stats) {}
  
  std::string getName() const;
  unsigned int getMoney() const;
  unsigned int getExp() const;
  std::shared_ptr<ItemCategory> getCategory() const;
  int getId() const;

  unsigned int getShipMask() const;
  bool canSatisfy(unsigned int shipNo) const;

  std::vector<ItemStat>& getStats();
private:
  ItemInfo _info;
  std::vector<ItemStat> _stats;
};

#endif