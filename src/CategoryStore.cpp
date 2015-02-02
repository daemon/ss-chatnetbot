#include <utility>
#include "CategoryStore.hpp"
#include "Item.hpp"

CategoryStore::CategoryStore()
{
  this->_categories = std::unordered_map<int, ItemCategory>([](int id) { return id; });
}

CategoryStore& CategoryStore::getInstance()
{
  static CategoryStore s;
  return s;
}

std::shared_ptr<ItemCategory> CategoryStore::register(int id, const std::string& name)
{
  if (this->_categories.find(id) == this->_categories.end())
    this->_categories.insert(std::make_pair<int, std::shared_ptr<ItemCategory>>(id, std::make_shared<ItemCategory>(id, name)));
  return this->_categories[id];
}

std::shared_ptr<ItemCategory> CategoryStore::get(int id)
{
  if (this->_categories.find(id) == this->_categories.end())
    return nullptr;
  return this->_categories[id];
}