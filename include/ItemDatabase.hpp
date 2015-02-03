#ifndef __ITEM_DATABASE_HPP__
#define __ITEM_DATABASE_HPP__

#include <memory>
#include <vector>

class Item; // Item.hpp

class ItemDatabase
{
public:
  static ItemDatabase& getInstance();
  std::vector<std::shared_ptr<Item>>& getItems();
  bool isLoaded() const { return this->_loaded; }
private:
  ItemDatabase() : _loaded(false) {}
  bool _loaded;
  std::vector<std::shared_ptr<Item>> _items;
};

#endif