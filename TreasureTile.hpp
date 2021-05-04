//---------------------------------------------------------------------------------------------------------------------
// TreasureTile.hpp
//
// Class for Treasure-Tile
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_TREASURE_TILE_HPP
#define A2_TREASURE_TILE_HPP

#include "Tile.hpp"
#include <string>
#include <vector>

class TreasureTile : public Tile
{
  private:
    Treasure* treasure_;

    std::string getTreasureId();
    Rotation calculateRotation(size_t treasure_id);

  public:
    TreasureTile(Treasure* treasure);
    TreasureTile(TileType type, Treasure* treasure);

    Treasure* getTreasure();
    bool getFound();

    void setTreasure(Treasure* treasure);
    void setFound(bool collected);

    void foundTreasure();
    std::vector<std::string> getTileString();
};


#endif //A2_TREASURE_TILE_HPP
