#ifndef __ITEM_DATABASE_HPP__
#define __ITEM_DATABASE_HPP__

#include <vector>

class Item; // Item.hpp

class ItemDatabase
{
public:
  static ItemDatabase& getInstance();
  std::vector<Item>& getItems();
  bool isLoaded() const { return this->_loaded; }
private:
  ItemDatabase() : _loaded(false) {}
  bool _loaded;
  std::vector<Item> _items;
};

#endif