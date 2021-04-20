//---------------------------------------------------------------------------------------------------------------------
// NormalTile.hpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_NORMALTILE_HPP
#define A2_NORMALTILE_HPP


#include "Tile.hpp"

class NormalTile : public Tile
{
  private:

  public:
    NormalTile(TileType type, Rotation rotation);

    std::vector<std::string> getTileString();

};

#endif //A2_NORMALTILE_HPP