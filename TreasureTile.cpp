//---------------------------------------------------------------------------------------------------------------------
// TreasureTile.cpp
//
// Class for Treasure-Tile
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "TreasureTile.hpp"

TreasureTile::TreasureTile(Treasure& treasure, TileType type, Rotation rotation) : treasure_{treasure}, collected_{false}
{
  setType(type);
  setRotation(rotation);
}

Treasure& TreasureTile::getTreasure()
{
  return treasure_;
}

bool TreasureTile::getCollected()
{
  return collected_;
}

void TreasureTile::setTreasure(Treasure& treasure)
{
  treasure_ = treasure;
}

void TreasureTile::setCollected(bool collected)
{
  collected_ = collected;
}

void TreasureTile::collectTreasure()
{
  collected_ = true;
}

std::string TreasureTile::getTreasureId()
{
  int treasure_id = treasure_.getTreasureId();
  std::string treasure = "T";

  if (treasure_id < 10)
  {
    treasure.append("0");
  }

  treasure.append(std::to_string(treasure_id));
  return treasure;
}

std::vector<std::string> TreasureTile::getTileString()
{
  std::vector<std::string> tileString = getRawTileString(getType(), getRotation());
  /*if (collected_)
  {
    return tileString;
  }

  std::string treasure_id = getTreasureId();
  std::cout << tileString[2] << std::endl;
  for (char c : tileString[2])
  {
    std::cout << c << std::endl;
  }
  std::cout << tileString[2].length() << std::endl;
  tileString[2].replace(4, 3, treasure_id);*/
  return tileString;
}
