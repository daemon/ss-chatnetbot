#ifndef __ITEM_HPP__
#define __ITEM_HPP__

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Item;

struct ItemCategory
{
  ItemCategory(int id1, const std::string name1) : name(name1), id(id1), max(1) {}
  std::vector<std::weak_ptr<Item>> items;
  std::string name;
  int id;
  unsigned int max; // *todo initialize
};

struct ItemInfo
{
  std::string name;
  std::vector<std::shared_ptr<ItemCategory>> categories;
  unsigned int money;
  unsigned int exp;
  unsigned int max;
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
  friend std::ostream& operator<<(std::ostream& out, const Item& item);
public:
  Item(const ItemInfo& info, const std::vector<ItemStat>& stats) : _info(info), _stats(stats) {}
  
  std::string getName() const;
  unsigned int getMoney() const;
  unsigned int getExp() const;
  std::vector<std::shared_ptr<ItemCategory>> getCategories() const;
  int getId() const;

  unsigned int getShipMask() const;
  bool canSatisfy(unsigned int shipNo) const;

  std::vector<ItemStat>& getStats();
  ItemInfo& getInfo();
private:
  ItemInfo _info;
  std::vector<ItemStat> _stats;
};

#endif