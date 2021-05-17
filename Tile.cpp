//---------------------------------------------------------------------------------------------------------------------
// Tile.hpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "Tile.hpp"
#include "Player.hpp"

Tile::Tile(TileType type, Rotation rotation) : type_{type}, rotation_{rotation} {}
Tile::Tile(TileType type) : type_{type}, rotation_{Rotation::DEG0} {}

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

bool Tile::isCorner(size_t row, size_t col)
{
  if((row == TOP_ROW || row == BOTTOM_ROW) && (col <= LEFT_COLUMN || col >= RIGHT_COLUMN))
  {
    return true;
  }
  return false;
}

std::vector<bool> Tile::setWalls(std::vector<Direction> directions)
{
  std::vector<bool> wallsToFill{false,false,false,false};
  for(size_t index = 0; index < directions.size(); index++)
  {
    if(directions[index] == Direction::TOP)
    {
      wallsToFill[static_cast<int>(Direction::TOP)] = true;
    }
    else if(directions[index] == Direction::LEFT)
    {
      wallsToFill[static_cast<int>(Direction::LEFT)] = true;
    }
    else if(directions[index] == Direction::BOTTOM)
    {
      wallsToFill[static_cast<int>(Direction::BOTTOM)] = true;
    }
    else if(directions[index] == Direction::RIGHT)
    {
      wallsToFill[static_cast<int>(Direction::RIGHT)] = true;
    }
  }
  return wallsToFill;
}

void Tile::fillWalls(std::vector<Direction> directions, std::vector<std::string>& tile)
{
  std::vector<std::string> templateTile;
  std::vector<bool> wallsToFill = setWalls(directions);

  for(size_t row = 0; row < TILE_HEIGHT ; row++)
  {
    templateTile.push_back("");
    for(size_t col = 0; col < TILE_WIDTH ; col++)
    {
      if(isCorner(row,col))
      {
        templateTile[row].append(WALL);
      }
      else if(wallsToFill[static_cast<int>(Direction::TOP)] && row == TOP_ROW)
      {
        templateTile[row].append(WALL);
      }
      else if(wallsToFill[static_cast<int>(Direction::LEFT)] && col <= LEFT_COLUMN)
      {
        templateTile[row].append(WALL);
      }
      else if(wallsToFill[static_cast<int>(Direction::BOTTOM)] && row == BOTTOM_ROW)
      {
        templateTile[row].append(WALL);
      }
      else if(wallsToFill[static_cast<int>(Direction::RIGHT)] && col >= RIGHT_COLUMN)
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
  size_t dirValue = static_cast<size_t>(dir);
  size_t rotValue = static_cast<size_t>(rot);
  dirValue += rotValue;
  if(dirValue >= DIRECTION_AMOUNT)
  {
    dirValue -= DIRECTION_AMOUNT;
  }
  return static_cast<Direction>(dirValue);
}

void Tile::generateTile(Rotation rotation, std::vector<Direction> directions, std::vector<std::string>& tile)
{
  for(size_t index = 0; index < directions.size(); index++)
  {
    directions[index] = calcDirection(directions[index],rotation);
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
      player_string += static_cast<char>(player->getPlayerColor());
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
    default:
      break;
  }
}