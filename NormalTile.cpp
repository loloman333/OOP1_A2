//---------------------------------------------------------------------------------------------------------------------
// NormalTile.cpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "NormalTile.hpp"

NormalTile::NormalTile(TileType type, Rotation rotation) : Tile(type, rotation){};

std::vector<std::string> NormalTile::getTileString()
{
  return getRawTileString(getType(),getRotation());
}