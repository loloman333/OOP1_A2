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
  Rotation rot; // [FB] avoid using abbreviations, they may not have the same meaning for everyone and can create missunderstandings
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
  std::string playerBase{"("}; // [FB] you can use "(" + std::string{getPlayerColor()} + td::string{")"} to make it one line -> at leat every second operand needs to be a string
  playerBase += getPlayerColor();
  playerBase += ")";

  if (tileString[2][0] == ' ')
  {
    tileString[2].replace(3, 3, playerBase); // [FB] is it possible to make the meaning of these number clearer?
  }
  else
  {
    tileString[2].replace(7, 3, playerBase);
  }
  return tileString;
}