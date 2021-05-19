//---------------------------------------------------------------------------------------------------------------------
// Tile.hpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "Tile.hpp"
#include "Player.hpp"

Tile::Tile(TileType type, Rotation rotation) : type_{type}, rotation_{rotation} 
{
  setWalls();
}
Tile::Tile(TileType type) : Tile(type, Rotation::DEG0) {}

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
  setWalls();
}

void Tile::setType(TileType type)
{
  type_ = type;
  setWalls();
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

bool Tile::isWallInDirection(Direction direction)
{
  for(size_t index = 0; index < walls_.size(); index++)
  {
    if(walls_[index] == direction)
    {
      return true;
    }
  }
  return false;
}

Direction Tile::calcDirection(Direction dir, Rotation rot)
{
  size_t dir_value = static_cast<size_t>(dir);
  size_t rot_value = static_cast<size_t>(rot);
  dir_value += rot_value;
  if(dir_value >= DIRECTION_AMOUNT)
  {
    dir_value -= DIRECTION_AMOUNT;
  }
  return static_cast<Direction>(dir_value);
}

void Tile::generateTile(Rotation rotation, std::vector<Direction> directions)
{
  for(size_t index = 0; index < directions.size(); index++)
  {
    walls_.push_back(calcDirection(directions[index],rotation));
  }
}

std::vector<std::string> Tile::getRawTileString()
{
  std::vector<std::string> tile_vector;
  setWalls();
  fillTileString(tile_vector);
  addPlayersToTile(tile_vector);

  return tile_vector;
}

void Tile::setWalls()
{
  walls_.clear();
  std::vector<Direction> directions;
  switch (type_)
  {
  case TileType::T:
    directions.push_back(Direction::TOP);
    generateTile(rotation_, directions);
    break;
  case TileType::L:
    directions.push_back(Direction::LEFT);
    directions.push_back(Direction::BOTTOM);
    generateTile(rotation_, directions);
      break;
  case TileType::I:
    directions.push_back(Direction::LEFT);
    directions.push_back(Direction::RIGHT);
    generateTile(rotation_, directions);
      break;
  case TileType::O:
    directions.push_back(Direction::LEFT);
    directions.push_back(Direction::RIGHT);
    directions.push_back(Direction::BOTTOM);
    directions.push_back(Direction::TOP);
    generateTile(rotation_, directions);
    break;
  case TileType::U:
    directions.push_back(Direction::RIGHT);
    directions.push_back(Direction::LEFT);
    directions.push_back(Direction::BOTTOM);
    generateTile(rotation_, directions);
      break;
  case TileType::X:
    generateTile(rotation_, directions);
    break;
  }
}

std::vector<bool> Tile::calcWalls()
{
  std::vector<bool> walls_to_fill{false,false,false,false};
  for(size_t index = 0; index < walls_.size(); index++)
  {
    if(walls_[index] == Direction::TOP)
    {
      walls_to_fill[static_cast<int>(Direction::TOP)] = true;
    }
    else if(walls_[index] == Direction::LEFT)
    {
      walls_to_fill[static_cast<int>(Direction::LEFT)] = true;
    }
    else if(walls_[index] == Direction::BOTTOM)
    {
      walls_to_fill[static_cast<int>(Direction::BOTTOM)] = true;
    }
    else if(walls_[index] == Direction::RIGHT)
    {
      walls_to_fill[static_cast<int>(Direction::RIGHT)] = true;
    }
  }
  return walls_to_fill;
}

void Tile::fillTileString(std::vector<std::string>& tile)
{
  std::vector<std::string> template_tile;
  std::vector<bool> walls_to_fill = calcWalls();

  for(size_t row = 0; row < TILE_HEIGHT ; row++)
  {
    template_tile.push_back("");
    for(size_t col = 0; col < TILE_WIDTH ; col++)
    {
      if(isCorner(row,col))
      {
        template_tile[row].append(WALL);
      }
      else if(walls_to_fill[static_cast<int>(Direction::TOP)] && row == TOP_ROW)
      {
        template_tile[row].append(WALL);
      }
      else if(walls_to_fill[static_cast<int>(Direction::LEFT)] && col <= LEFT_COLUMN)
      {
        template_tile[row].append(WALL);
      }
      else if(walls_to_fill[static_cast<int>(Direction::BOTTOM)] && row == BOTTOM_ROW)
      {
        template_tile[row].append(WALL);
      }
      else if(walls_to_fill[static_cast<int>(Direction::RIGHT)] && col >= RIGHT_COLUMN)
      {
        template_tile[row].append(WALL);
      }
      else
      {
        template_tile[row].append(" ");
      }
    }
  }
  tile = template_tile;
}

void Tile::addPlayersToTile(std::vector<std::string>& tile_vector)
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

    if (tile_vector[3][0] == ' ')
    {
      tile_vector[3].replace(index, player_string.size(), player_string);
    }
    else
    {
      tile_vector[3].replace(index + 4, player_string.size(), player_string);
    }
  }
}

void Tile::addPlayer(Player *player)
{
  players_.push_back(player);
}

void Tile::print()
{
  std::vector<std::string> tile_string = getTileString();
  for (std::string row : tile_string)
  {
    std::cout << row << std::endl;
  }
}

void Tile::removePlayer(std::string player_color)
{
  size_t location = 0;
  for(size_t index = 0; index < players_.size(); index++)
  {
    if(players_[index]->getPlayerColorAsString() == player_color)
    {
      location = index;
    }
  }
  players_.erase(players_.begin() + location);
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