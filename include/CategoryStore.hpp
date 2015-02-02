#ifndef __CATEGORY_STORE_HPP__
#define __CATEGORY_STORE_HPP__

#include <memory>
#include <unordered_map>

class ItemCategory; // Item.hpp

class CategoryStore
{
public:
  static CategoryStore& getInstance();
  std::shared_ptr<ItemCategory> create(int id, const std::string& name);
  std::shared_ptr<ItemCategory> get(int id);
private:
  CategoryStore() {}
  std::unordered_map<int, std::shared_ptr<ItemCategory>> _categories;
};

#endif