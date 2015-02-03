#include <algorithm>
#include <cmath>
#include "CategoryStore.hpp"
#include "Item.hpp"
#include "ItemDatabase.hpp"
#include "ItemHeap.hpp"

ItemHeap::Builder::Builder(CostFunctionT costFn) : _costFn(costFn) {}

ItemHeap ItemHeap::Builder::build(unsigned int ship)
{
  ItemHeap heap;
  std::vector<std::shared_ptr<Item>>& items = ItemDatabase::getInstance().getItems();
  auto& catMap = CategoryStore::getInstance().getMap();
  for (auto& category : catMap)
  {
    ItemCategoryNode node;
    node.category = category.second;
    heap._categoryNodes.push_back(std::move(node));

    for (auto& i : category.second->items)
    {
      if (!i.lock()->canSatisfy(ship))
        continue;

      std::shared_ptr<ItemNode> node2(new ItemNode);
      node2->item = i.lock();
      node2->cost = this->_costFn(*i.lock());

      heap.insert(heap._categoryNodes.end() - 1, node2);
    }
  } 

  for (int j = 0; j < heap._categoryNodes.size(); ++j) {
    for (auto i : heap._categoryNodes[j].heap)
    {
      std::cout << *i->item << i->cost << std::endl;
      if (i->left)
        std::cout << "LEFT: " << *i->left->item << std::endl;
      if (i->right)
        std::cout << "RIGHT: " << *i->right->item << std::endl;
    }
    std::cout << std::endl;
  }
  return heap;
}

void ItemHeap::insert(std::vector<ItemCategoryNode>::iterator it, std::shared_ptr<ItemNode> node)
{
  it->heap.push_back(node);  
  if (it->heap.size() == 1) 
    return;

  size_t rootPos = (it->heap.size()) / 2 - 1;
  size_t currentPos = it->heap.size() - 1;
  node->root = it->heap[rootPos];
  
  if (node->root.lock()->left)
    node->root.lock()->right = node;
  else
    node->root.lock()->left = node;

  while (node->root.lock() && node->cost > node->root.lock()->cost)
  {
    auto tmp = node->root;
    std::swap(tmp.lock()->item, node->item);    
    std::swap(tmp.lock()->cost, node->cost);

    if (rootPos == 0)
      break;

    currentPos = rootPos;
    rootPos = (rootPos + 1) / 2 - 1;
    node = it->heap[currentPos];
  }
}

CostFunctionT ItemHeap::getDefaultCostFunction()
{
  return [](Item& item) {
    // weighting goes from 1 to 100
    double defaultMult = 100.0;
    int sum = 0;
    for (auto& stat : item.getStats())
      sum += std::max(defaultMult * static_cast<double>(stat.change) / stat.maxmin, -defaultMult / 4);
    
    return sum;
  };
}

std::ostream& operator<<(std::ostream& out, const ItemHeap& heap)
{
  for (auto i : heap._categoryNodes)
    if (i.heap.size() > 0)
      out << i.heap[0].get() << std::endl;

  return out;
}