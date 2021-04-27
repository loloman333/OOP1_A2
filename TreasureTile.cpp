//---------------------------------------------------------------------------------------------------------------------
// TreasureTile.cpp
//
// Class for Treasure-Tile
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "TreasureTile.hpp"

#include <algorithm>

TreasureTile::TreasureTile(Treasure* treasure) : treasure_{treasure}
{
  setType(TileType::T);
  setRotation(calculateRotation(treasure->getTreasureId()));
}

Treasure* TreasureTile::getTreasure()
{
  return treasure_;
}

bool TreasureTile::getFound()
{
  return treasure_->getFound();
}

void TreasureTile::setTreasure(Treasure* treasure)
{
  treasure_ = treasure;
}

void TreasureTile::setFound(bool found)
{
  treasure_->setFound(found);
}

void TreasureTile::foundTreasure()
{
  treasure_->setFound(true);
}

std::string TreasureTile::getTreasureId()
{
  int treasure_id = treasure_->getTreasureId();
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
  std::vector<std::string> tileString = getRawTileString();
  if (getFound())
  {
    return tileString;
  }

  std::string treasure_id = getTreasureId();
  if (tileString[2][0] == ' ')
  {
    tileString[2].replace(3, 3, treasure_id);
  }
  else
  {
    tileString[2].replace(7, 3, treasure_id);
  }

  return tileString;
}

Rotation TreasureTile::calculateRotation(size_t treasure_id)
{
  std::vector<size_t> deg_0 = {1, 2, 5};
  std::vector<size_t> deg_90 = {3, 4, 7};
  std::vector<size_t> deg_180 = {8, 11, 12};

  if (std::count(deg_0.begin(), deg_0.end(), treasure_id))
  {
    return Rotation::DEG0;
  }
  else if (std::count(deg_90.begin(), deg_90.end(), treasure_id))
  {
    return Rotation::DEG90;
  }
  else if (std::count(deg_180.begin(), deg_180.end(), treasure_id))
  {
    return Rotation::DEG180;
  }
  else
  {
    return Rotation::DEG270;
  }
}
