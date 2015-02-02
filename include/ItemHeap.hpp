#ifndef __ITEM_HEAP__
#define __ITEM_HEAP__

#include <functional>
#include <memory>
#include <vector>

class Item; // Item.hpp
class ItemCategory; // Item.hpp

typedef std::function<int(Item)> CostFunctionT;

struct ItemNode
{
  std::unique_ptr<ItemNode> root;
  std::unique_ptr<ItemNode> left;
  std::unique_ptr<ItemNode> right;
};

struct ItemCategoryNode
{
  std::shared_ptr<ItemCategory> category;
  std::unique_ptr<ItemNode> root;
  size_t height;
};

class ItemHeap
{
  friend class ItemHeap::Builder;
public:
  ItemHeap(const ItemHeap&) = delete;
  ItemHeap& operator=(const ItemHeap&) = delete;
  ItemHeap(ItemHeap&& other);
  ItemHeap& operator=(ItemHeap&&);

  std::vector<ItemCategoryNode>& getCategoryNodes();
  
  class Builder
  {
  public:
    Builder(std::vector<std::shared_ptr<ItemCategory>> categories, CostFunctionT costFn);
    ItemHeap build(unsigned int ship);
  private:
    std::vector<std::shared_ptr<ItemCategory>> _categories;
    CostFunctionT _costFn;
  };
private:
  std::vector<ItemCategoryNode> _categoryNodes;
};

#endif