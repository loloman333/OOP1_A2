//---------------------------------------------------------------------------------------------------------------------
// Item.cpp
//
// Class for Item
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "Item.hpp"

Item::Item(ItemType item_type) : item_type_{item_type} {};

ItemType Item::getItemType()
{
  return item_type_;
}

bool Item::getFound()
{
  return found_;
}

void Item::setFound(bool found)
{
  found_ = found;
}