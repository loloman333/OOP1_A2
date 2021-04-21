//---------------------------------------------------------------------------------------------------------------------
// StartTile.cpp
//
// Class for Start Tile
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "StartTile.hpp"

StartTile::StartTile(char player_color) : Tile{}, player_color_{player_color} 
{
  Rotation rot;
  switch (player_color)
  {
    case 'G':
      rot = Rotation::DEG0;
      break;
    case 'B':
      rot = Rotation::DEG90;
      break;
    case 'Y':
      rot = Rotation::DEG180;
      break;
    case 'R':
      rot = Rotation::DEG270;
      break;
    default:
      //TODO: remove?
      std::cerr << "Invalid player color!" << std::endl;
      exit(-1);
      break;
  }

  setType(TileType::L);
  setRotation(rot);
}

char StartTile::getPlayerColor()
{
  return player_color_;
}

std::vector<std::string> StartTile::getTileString()
{
  std::vector<std::string> tileString = getRawTileString();
  std::string playerBase{"("};
  playerBase += getPlayerColor();
  playerBase += ")";

  //TODO: use wstring instead?
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