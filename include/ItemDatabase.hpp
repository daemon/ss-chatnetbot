#ifndef __ITEM_DATABASE_HPP__
#define __ITEM_DATABASE_HPP__

#include <vector>

class Item; // Item.hpp

class ItemDatabase
{
public:
  static ItemStore& getInstance();
  std::vector<Item> loadItems();
  bool isLoaded() const { return this->_loaded }
private:
  ItemStore() : _loaded(false) {}
  bool _loaded;
};

#endif