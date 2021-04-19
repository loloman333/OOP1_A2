//---------------------------------------------------------------------------------------------------------------------
// Tile.hpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "Tile.hpp"

Tile::Tile(TileType type, Rotation rotation) : type_{type}, rotation_{rotation} {}

TileType Tile::getType()
{
  return type_;
}

Rotation Tile::getRotation()
{
  return rotation_;
}

std::vector<Player*> Tile::getPlayers()
{
  return players_;
}

void Tile::setRotation(Rotation r)
{
  rotation_ = r;
}

size_t Tile::getRotationValue()
{
  switch (rotation_)
  {
  case Rotation::DEG0:
    return 0;
  case Rotation::DEG90:
    return 90;
  case Rotation::DEG180:
    return 180;
  case Rotation::DEG270:
    return 270;
  }
}

std::string Tile::getTileTypeString()
{
  switch (type_)
  {
  case TileType::T:
    return "T";
  case TileType::L:
    return "L";
  case TileType::I:
    return "I";
  case TileType::O:
    return "O";
  case TileType::U:
    return "U";
  case TileType::X:
    return "X";
  default:
    return nullptr;
  }
}