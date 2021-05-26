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

std::string Item::getItemTypeAsString()
{
  switch (item_type_)
  {
  case ItemType::BRICKS:
    return "BRI";

  case ItemType::DYNAMITE:
    return "DYN";

  case ItemType::ROPE:
    return "ROP";

  case ItemType::LADDER:
    return "LAD";
  }
}

bool Item::getFound()
{
  return found_;
}

void Item::setFound(bool found)
{
  found_ = found;
}

void Item::use()
{
  switch (item_type_)
  {
  case ItemType::BRICKS:
    useBricks();
    break;
  case ItemType::DYNAMITE:
    useDynamite();
    break;
  case ItemType::LADDER:
    useLadder();
    break;
  case ItemType::ROPE:
    useRope();
    break;
  }
}

void Item::useBricks()
{

}
void Item::useDynamite()
{

}
void Item::useLadder()
{
  game_.getPrintMaster()->ladderUsed();
  game_.getCurrentPlayer().setUsingLadder(true);
}
void Item::useRope()
{

}