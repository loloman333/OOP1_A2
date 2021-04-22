//---------------------------------------------------------------------------------------------------------------------
// NormalTile.cpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "NormalTile.hpp"

NormalTile::NormalTile(TileType type, Rotation rotation) : Tile(type, rotation){};
NormalTile::NormalTile(TileType type) : Tile(type){};

std::vector<std::string> NormalTile::getTileString()
{
  return getRawTileString();
}