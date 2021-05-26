//---------------------------------------------------------------------------------------------------------------------
// Item.hpp
//
// Class for Item
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_ITEM_HPP
#define A2_ITEM_HPP

enum class ItemType {ROPE, DYNAMITE, BRICKS, LADDER};

class Item
{
private:
  ItemType item_type_;
  bool found_ = false;

public:
  Item(ItemType item_type);

  ItemType getItemType();
  bool getFound();

  void setFound(bool found);

  void use();
};


#endif //A2_ITEM_HPP
