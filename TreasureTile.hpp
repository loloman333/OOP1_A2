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
    bool collected_;

    std::string getTreasureId();
    Rotation calculateRotation(size_t treasure_id);

  public:
    TreasureTile(Treasure* treasure);

    Treasure* getTreasure();
    bool getCollected();

    void setTreasure(Treasure* treasure);
    void setCollected(bool collected);

    void collectTreasure();
    std::vector<std::string> getTileString();
};


#endif //A2_TREASURE_TILE_HPP
