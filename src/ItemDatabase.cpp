#include <algorithm>
#include <map>
#include <sqlite3.h>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include "CategoryStore.hpp"
#include "Item.hpp"
#include "ItemDatabase.hpp"

static const std::vector<std::string> _shouldMinimize {"bombenergy",
  "mineenergypct",
  "cloakenergy",
  "bulletdelaypct",
  "jittertime",
  "stealthenergy",
  "bombdelaypct",
  "minedelay",
  "explodepixels",
  "multienergypct",
  "extrabombdelay",
  "minedelaypct",
  "xradarenergy",
  "multidelaypct",
  "bulletenergypct",
  "shrapdamage",
  "bulletdamage",
  "multidelay",
  "mineenergy",
  "bombdamage",
  "bombdelay",
  "bombenergypct" };

ItemDatabase& ItemDatabase::getInstance()
{
  static ItemDatabase s;
  return s;
}

std::vector<Item>& ItemDatabase::getItems()
{
  sqlite3* handle;
  sqlite3_open("hs_items.db", &handle);
  if (this->_loaded)
    return this->_items;

  std::string statement = "SELECT * FROM items WHERE 1=1";
  sqlite3_stmt* stmtObj;

  int rc = sqlite3_prepare_v2(handle,
                              statement.c_str(),
                              statement.length() + 1,
                              &stmtObj,
                              NULL);    
  
  std::vector<std::pair<int, std::string>> idToItemNames;  

  while (rc = sqlite3_step(stmtObj), 1)
  {
    if (rc == SQLITE_DONE)
      break;
    else if (rc == SQLITE_ROW)
    {      
      std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmtObj, 1)));
      int id = sqlite3_column_int(stmtObj, 0);

      idToItemNames.push_back(std::make_pair(id, name));
    } else if (rc == SQLITE_BUSY) {
      std::chrono::milliseconds duration(100);
      std::this_thread::sleep_for(duration);
      continue;
    } else
      break;
  }

  sqlite3_finalize(stmtObj);

  statement = "SELECT * FROM categories WHERE 1=1";
  rc = sqlite3_prepare_v2(handle,
                              statement.c_str(),
                              statement.length() + 1,
                              &stmtObj,
                              NULL);
  
  std::vector<std::pair<int, std::string>> idToCategoryNames;

  while (rc = sqlite3_step(stmtObj), 1)
  {
    if (rc == SQLITE_DONE)
      break;
    else if (rc == SQLITE_ROW)
    {      
      std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmtObj, 1)));
      int id = sqlite3_column_int(stmtObj, 0);

      idToCategoryNames.push_back(std::make_pair(id, name));
    } else if (rc == SQLITE_BUSY) {
      std::chrono::milliseconds duration(100);
      std::this_thread::sleep_for(duration);
      continue;
    } else
      break;
  }

  sqlite3_finalize(stmtObj);

  statement = "SELECT * FROM category_constraints WHERE 1=1";
  rc = sqlite3_prepare_v2(handle,
                              statement.c_str(),
                              statement.length() + 1,
                              &stmtObj,
                              NULL);
  
  std::vector<std::pair<int, int>> idToCategoryMax;

  while (rc = sqlite3_step(stmtObj), 1)
  {
    if (rc == SQLITE_DONE)
      break;
    else if (rc == SQLITE_ROW)
    {      
      int max = sqlite3_column_int(stmtObj, 1);
      int id = sqlite3_column_int(stmtObj, 0);

      idToCategoryMax.push_back(std::make_pair(id, max));
    } else if (rc == SQLITE_BUSY) {
      std::chrono::milliseconds duration(100);
      std::this_thread::sleep_for(duration);
      continue;
    } else
      break;
  }

  sqlite3_finalize(stmtObj);

  statement = "SELECT * FROM item_categories WHERE 1=1";
  rc = sqlite3_prepare_v2(handle,
                              statement.c_str(),
                              statement.length() + 1,
                              &stmtObj,
                              NULL);
  
  std::vector<std::pair<int, int>> idToCategoryIds;

  while (rc = sqlite3_step(stmtObj), 1)
  {
    if (rc == SQLITE_DONE)
      break;
    else if (rc == SQLITE_ROW)
    {      
      int catId = sqlite3_column_int(stmtObj, 1);
      int id = sqlite3_column_int(stmtObj, 0);

      idToCategoryIds.push_back(std::make_pair(id, catId));
    } else if (rc == SQLITE_BUSY) {
      std::chrono::milliseconds duration(100);
      std::this_thread::sleep_for(duration);
      continue;
    } else
      break;
  }

  sqlite3_finalize(stmtObj);

  statement = "SELECT * FROM item_costs WHERE 1=1";
  rc = sqlite3_prepare_v2(handle,
                              statement.c_str(),
                              statement.length() + 1,
                              &stmtObj,
                              NULL);
  std::vector<ItemInfo> itemInfos; 

  while (rc = sqlite3_step(stmtObj), 1)
  {
    if (rc == SQLITE_DONE)
      break;
    else if (rc == SQLITE_ROW)
    {      
      ItemInfo info;
      info.id       = sqlite3_column_int(stmtObj, 0);
      info.money    = sqlite3_column_int(stmtObj, 1);
      info.exp      = sqlite3_column_int(stmtObj, 2);
      info.shipMask = sqlite3_column_int(stmtObj, 3);
      info.max      = sqlite3_column_int(stmtObj, 4);

      itemInfos.push_back(info);
    } else if (rc == SQLITE_BUSY) {
      std::chrono::milliseconds duration(100);
      std::this_thread::sleep_for(duration);
      continue;
    } else
      break;
  }

  sqlite3_finalize(stmtObj);

  statement = "SELECT * FROM stats WHERE 1=1";
  rc = sqlite3_prepare_v2(handle,
                              statement.c_str(),
                              statement.length() + 1,
                              &stmtObj,
                              NULL);
  std::vector<ItemStat> stats; 

  while (rc = sqlite3_step(stmtObj), 1)
  {
    if (rc == SQLITE_DONE)
      break;
    else if (rc == SQLITE_ROW)
    {      
      ItemStat stat;
      stat.id             = sqlite3_column_int(stmtObj, 0);
      stat.name           = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmtObj, 1)));
      stat.maxmin         = sqlite3_column_int(stmtObj, 2);
      auto it = std::find(_shouldMinimize.begin(), _shouldMinimize.end(), stat.name);
      stat.shouldMaximize = it == _shouldMinimize.end();
      stats.push_back(stat);
    } else if (rc == SQLITE_BUSY) {
      std::chrono::milliseconds duration(100);
      std::this_thread::sleep_for(duration);
      continue;
    } else
      break;
  }

  sqlite3_finalize(stmtObj);

  statement = "SELECT * FROM item_stats WHERE 1=1";
  rc = sqlite3_prepare_v2(handle,
                              statement.c_str(),
                              statement.length() + 1,
                              &stmtObj,
                              NULL);  

  std::map<int, std::vector<ItemStat>> itemIdToStats;

  while (rc = sqlite3_step(stmtObj), 1)
  {
    if (rc == SQLITE_DONE)
      break;
    else if (rc == SQLITE_ROW)
    {  
      int itemId = sqlite3_column_int(stmtObj, 0);
      int statId = sqlite3_column_int(stmtObj, 1);
      int change = sqlite3_column_int(stmtObj, 2);      
      
      auto it = std::find_if(stats.begin(), stats.end(), [&statId](const ItemStat& stat) {
        return stat.id == statId;
      });

      ItemStat tmp(*it);
      tmp.change = change;
      itemIdToStats[itemId].push_back(std::move(tmp));
    } else if (rc == SQLITE_BUSY) {
      std::chrono::milliseconds duration(100);
      std::this_thread::sleep_for(duration);
      continue;
    } else
      break;
  }

  sqlite3_finalize(stmtObj);
  
  for (auto& i : idToCategoryNames)
  {
    auto cat = CategoryStore::getInstance().create(i.first, i.second); 
    cat->max = (*std::find_if(idToCategoryMax.begin(), idToCategoryMax.end(), [&i, cat](const std::pair<int, int>& j) {
      return i.first == cat->id;
    })).second;
  }
  
  for (auto& i : itemInfos)
    i.name = (*std::find_if(idToItemNames.begin(), idToItemNames.end(), [&i](const std::pair<int, std::string>& j) {
      return j.first == i.id;
    })).second;

  for (auto& i : itemInfos)
    this->_items.push_back(Item(i, itemIdToStats[i.id]));
  
  for (auto& i : idToCategoryIds)
  {
    auto cat = CategoryStore::getInstance().get(i.second);
    auto it = std::find_if(this->_items.begin(), this->_items.end(), [&i](const Item& item) {
      return item.getId() == i.first;
    });
    it->getInfo().category = cat;
  }

  this->_loaded = true;
  return this->_items;
}