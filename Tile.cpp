//---------------------------------------------------------------------------------------------------------------------
// Tile.hpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "Tile.hpp"

Tile::Tile(TileType type, Rotation rotation) : type_{type}, rotation_{rotation} {}
Tile::Tile(TileType type) : type_{type} {}

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
        templateTile[row].append(WALL);
      }
      else if(topWall && row == 0)
      {
        templateTile[row].append(WALL);
      }
      else if(leftWall && col <= 1)
      {
        templateTile[row].append(WALL);
      }
      else if(botWall && row == 4)
      {
        templateTile[row].append(WALL);
      }
      else if(rightWall && col >= 7)
      {
        templateTile[row].append(WALL);
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
  std::vector<Direction> directions{};
  switch (type_)
  {
  case TileType::T:
    directions.push_back(Direction::TOP);
    generateTile(rotation_, directions, tileVector);
    break;
  case TileType::L:
    directions.push_back(Direction::LEFT);
    directions.push_back(Direction::BOTTOM);
    generateTile(rotation_, directions, tileVector);
      break;
  case TileType::I:
    directions.push_back(Direction::LEFT);
    directions.push_back(Direction::RIGHT);
    generateTile(rotation_, directions, tileVector);
      break;
  case TileType::O:
    directions.push_back(Direction::LEFT);
    directions.push_back(Direction::RIGHT);
    directions.push_back(Direction::BOTTOM);
    directions.push_back(Direction::TOP);
    generateTile(rotation_, directions, tileVector);
    break;
  case TileType::U:
    directions.push_back(Direction::RIGHT);
    directions.push_back(Direction::LEFT);
    directions.push_back(Direction::BOTTOM);
    generateTile(rotation_, directions, tileVector);
      break;
  case TileType::X:
    generateTile(rotation_, directions, tileVector);
    break;
  }

  addPlayersToTile(tileVector);

  return tileVector;
}

void Tile::addPlayersToTile(std::vector<std::string>& tileVector)
{
  if (!players_.empty())
  {
    int index = 3;
    if (players_.size() == 4)
    {
      index = 2;
    }

    std::string player_string = "P";
    for (Player* player : players_)
    {
      player_string += player->getPlayerColor();
    }

    if (tileVector[3][0] == ' ')
    {
      tileVector[3].replace(index, player_string.size(), player_string);
    }
    else
    {
      tileVector[3].replace(index + 4, player_string.size(), player_string);
    }
  }
}

void Tile::addPlayer(Player *player)
{
  players_.push_back(player);
}

void Tile::print()
{
  std::vector<std::string> tile_string = getRawTileString();
  for (std::string row : tile_string)
  {
    std::cout << row << std::endl;
  }
}

void Tile::rotate(Direction dir)
{
  switch (dir)
  {
    case Direction::LEFT:
      switch (rotation_)
      {
        case Rotation::DEG0:
          rotation_ = Rotation::DEG90;
          break;
        case Rotation::DEG90:
          rotation_ = Rotation::DEG180;
          break;
        case Rotation::DEG180:
          rotation_ = Rotation::DEG270;
          break;
        case Rotation::DEG270:
          rotation_ = Rotation::DEG0;
          break;
      }
      break;
    case Direction::RIGHT:
      switch (rotation_)
      {
        case Rotation::DEG0:
          rotation_ = Rotation::DEG270;
          break;
        case Rotation::DEG90:
          rotation_ = Rotation::DEG0;
          break;
        case Rotation::DEG180:
          rotation_ = Rotation::DEG90;
          break;
        case Rotation::DEG270:
          rotation_ = Rotation::DEG180;
          break;
      }
      break;
  }
}