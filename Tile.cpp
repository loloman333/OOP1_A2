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

void Tile::setType(TileType type)
{
  type_ = type;
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

void Tile::fillWalls(std::vector<Direction> directions, std::vector<std::string>& tile)
{
  std::vector<std::string> templateTile;
  bool topWall = false;
  bool leftWall = false;
  bool botWall = false;
  bool rightWall = false;
  for(size_t i = 0; i < directions.size(); i++)
  {
    if(directions[i] == Direction::TOP)
    {
      topWall = true;
    }
    else if(directions[i] == Direction::LEFT)
    {
      leftWall = true;
    }
    else if(directions[i] == Direction::BOTTOM)
    {
      botWall = true;
    }
    else if(directions[i] == Direction::RIGHT)
    {
      rightWall = true;
    }
  }

  for(size_t row = 0; row < 5 ; row++)
  {
    templateTile.push_back("");
    for(size_t col = 0; col < 9 ; col++)
    {
      if((row == 0 || row == 4) && (col <= 1 || col >= 7))
      {
        templateTile[row].append(Wall);
      }
      else if(topWall && row == 0)
      {
        templateTile[row].append(Wall);
      }
      else if(leftWall && col <= 1)
      {
        templateTile[row].append(Wall);
      }
      else if(botWall && row == 4)
      {
        templateTile[row].append(Wall);
      }
      else if(rightWall && col >= 7)
      {
        templateTile[row].append(Wall);
      }
      else
      {
        templateTile[row].append(" ");
      }
    }
  }
  tile = templateTile;
}

Direction Tile::calcDirection(Direction dir, Rotation rot)
{
  int dirValue = (int)dir;
  int rotValue = (int)rot;
  dirValue += rotValue;
  if(dirValue >= 4)
  {
    dirValue -= 4;
  }
  return (Direction)dirValue;
}

void Tile::generateTile(Rotation rotation, std::vector<Direction> directions, std::vector<std::string>& tile)
{
  for(size_t i = 0; i < directions.size(); i++)
  {
    directions[i] = calcDirection(directions[i],rotation);
  }
  fillWalls(directions,tile);
}

std::vector<std::string> Tile::getRawTileString()
{
  std::vector<std::string> tileVector;
  std::vector<Direction> directions;
  switch (type_)
  {
  case TileType::T:
    directions.push_back(Direction::TOP);
    generateTile(rotation_, directions, tileVector);
    return tileVector;
  case TileType::L:
    directions.push_back(Direction::LEFT);
    directions.push_back(Direction::BOTTOM);
    generateTile(rotation_, directions, tileVector);
    return tileVector;
  case TileType::I:
    directions.push_back(Direction::LEFT);
    directions.push_back(Direction::RIGHT);
    generateTile(rotation_, directions, tileVector);
    return tileVector;
  case TileType::O:
    directions.push_back(Direction::LEFT);
    directions.push_back(Direction::RIGHT);
    directions.push_back(Direction::BOTTOM);
    directions.push_back(Direction::TOP);
    generateTile(rotation_, directions, tileVector);
    return tileVector;
  case TileType::U:
    directions.push_back(Direction::RIGHT);
    directions.push_back(Direction::LEFT);
    directions.push_back(Direction::BOTTOM);
    generateTile(rotation_, directions, tileVector);
    return tileVector;
  case TileType::X:
    generateTile(rotation_, directions, tileVector);
    return tileVector;
  default:
    return tileVector;
  }
}