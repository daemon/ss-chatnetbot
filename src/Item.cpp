#include <iostream>
#include "Item.hpp"

std::string Item::getName() const
{
  return this->_info.name;
}

unsigned int Item::getMoney() const
{
  return this->_info.money;
}

unsigned int Item::getExp() const
{
  return this->_info.exp;
}

std::vector<std::shared_ptr<ItemCategory>> Item::getCategories() const
{
  return this->_info.categories;
}

int Item::getId() const
{
  return this->_info.id;
}

unsigned int Item::getShipMask() const
{
  return this->_info.shipMask;
}

bool Item::canSatisfy(unsigned int shipNo) const
{
  return this->getShipMask() & shipNo;
}

std::vector<ItemStat>& Item::getStats()
{
  return this->_stats;
}

ItemInfo& Item::getInfo()
{
  return this->_info;
}

std::ostream& operator<<(std::ostream& out, const Item& item)
{  
  out << "<<" << item.getName() << " : " << item.getMoney() << " " << item.getExp() << " : " << ">>";  
  return out;
}