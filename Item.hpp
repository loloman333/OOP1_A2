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
#include <vector>

const std::vector<std::string> WALL_VALID_RESPONSES{"top", "left", "bottom", "right"};

class Game;
class Tile;
enum class Direction;

enum class ItemType {ROPE, DYNAMITE, BRICKS, LADDER};

class Item
{
private:
  ItemType item_type_;
  bool found_ = false;
  void useBricks(Game& game);
  void useDynamite(Game& game);
  void useLadder(Game& game);
  void useRope(Game& game);

  bool isValidResponse(std::string response);
  Direction getDirectionFromString(std::string string);
  void setBricksInDirection(Direction direction, Tile* tile);

public:
  Item(ItemType item_type);

  ItemType getItemType();
  std::string getItemTypeAsString();
  bool getFound();

  void setFound(bool found);

  void use();

};

#endif //A2_ITEM_HPP