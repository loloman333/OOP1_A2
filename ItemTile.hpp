//---------------------------------------------------------------------------------------------------------------------
// ItemTile.hpp
//
// Class for Item-Tile
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_ITEM_TILE_HPP
#define A2_ITEM_TILE_HPP

#include "Tile.hpp"
#include <string>
#include <vector>

const size_t ITEM_TILE_ROW = 2;

class Item;

class ItemTile : public Tile
{
  private:
    Item* item_;

  public:
    ItemTile(TileType type, Item* item);
    
    Item* getItem();
    void setFound(bool collected);
    bool getFound();
    bool hasItem();

    std::vector<std::string> getTileString();
};


#endif //A2_ITEM_TILE_HPP
