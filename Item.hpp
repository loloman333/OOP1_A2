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

#include <string>

const std::string UI_LADDER_PROMPT = "You can go in all directions, with your next move. Choose wisely!";

enum class ItemType {ROPE, DYNAMITE, BRICKS, LADDER};

class Item
{
private:
  ItemType item_type_;
  bool found_ = false;
  void useBricks();
  void useDynamite();
  void useLadder();
  void useRope();

public:
  Item(ItemType item_type);

  ItemType getItemType();
  std::string getItemTypeAsString();
  bool getFound();

  void setFound(bool found);

  void use();

};

#endif //A2_ITEM_HPP