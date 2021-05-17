//---------------------------------------------------------------------------------------------------------------------
// StartTile.cpp
//
// Class for Start Tile
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "StartTile.hpp"
#include "Player.hpp"

StartTile::StartTile(PlayerColor player_color) : Tile{}, player_color_{player_color} 
{
  Rotation rot;
  switch (player_color)
  {
    case PlayerColor::GREEN:
      rot = Rotation::DEG0;
      break;
    case PlayerColor::BLUE:
      rot = Rotation::DEG90;
      break;
    case PlayerColor::YELLOW:
      rot = Rotation::DEG180;
      break;
    case PlayerColor::RED:
      rot = Rotation::DEG270;
      break;
  }

  setType(TileType::L);
  setRotation(rot);
}

PlayerColor StartTile::getPlayerColor()
{
  return player_color_;
}

std::vector<std::string> StartTile::getTileString()
{
  std::vector<std::string> tileString = getRawTileString();
  std::string playerBase{"("};
  playerBase += static_cast<char>(getPlayerColor());
  playerBase += ")";

  if (tileString[2][0] == ' ')
  {
    tileString[2].replace(3, 3, playerBase);
  }
  else
  {
    tileString[2].replace(7, 3, playerBase);
  }
  return tileString;
}