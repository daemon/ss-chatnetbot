#ifndef __ITEM_HEAP__
#define __ITEM_HEAP__

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

class Item; // Item.hpp
class ItemCategory; // Item.hpp

typedef std::function<int(Item&)> CostFunctionT;

struct ItemNode
{
  std::weak_ptr<ItemNode> root;
  std::shared_ptr<ItemNode> left;
  std::shared_ptr<ItemNode> right;
  std::shared_ptr<Item> item;
  int cost;
};

struct ItemCategoryNode
{
  std::shared_ptr<ItemCategory> category;
  std::vector<std::shared_ptr<ItemNode>> heap;
};

class ItemHeap
{
  friend class Builder;
  friend std::ostream& operator<<(std::ostream& out, const ItemHeap& heap);
public:
  std::vector<ItemCategoryNode>& getCategoryNodes() { return this->_categoryNodes; }
  void insert(std::vector<ItemCategoryNode>::iterator it, std::shared_ptr<ItemNode> item);

  static CostFunctionT getDefaultCostFunction();

  class Builder
  {
  public:
    Builder(/*std::vector<std::shared_ptr<ItemCategory>> categories,*/ CostFunctionT costFn);
    ItemHeap build(unsigned int ship); // TODO: user-defined constraints function
  private:
    CostFunctionT _costFn;
  };
private:
  std::vector<ItemCategoryNode> _categoryNodes;
};/*
static inline std::ostream& operator<<(std::ostream& out, ItemNode* node)
{
  if (node == nullptr)
    return out;
  
  if (node->left)
    out << node->left.get();
  
  out << *node->item;

  if (node->right)
    out << node->right.get();
  
  return out;
}*/

#endif